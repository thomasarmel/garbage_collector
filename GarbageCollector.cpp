#include <thread>
#include <cstdint>
#include "GarbageCollector.h"
#include "CurrentResourceUsage.h"

//#include <iostream>

constexpr uint8_t SECRETARY_PHASES_MAX_TICK[] = {7, 13};
constexpr int64_t SECRETARY_TICK_DURATION_MS = 10;

GarbageCollector* GarbageCollector::_instance = nullptr;

GarbageCollector::GarbageCollector()
{
    _thread = std::make_unique<std::thread>(&GarbageCollector::run, this);
    _thread->detach();
}

GarbageCollector *GarbageCollector::getInstance()
{
    if(GarbageCollector::_instance == nullptr)
    {
        GarbageCollector::_instance = new GarbageCollector();
    }
    return GarbageCollector::_instance;
}

void GarbageCollector::add(void* pointer, void (*destructorFunction)(void*))
{
    _garbage.emplace(std::make_pair(pointer, destructorFunction));
}

[[noreturn]] void GarbageCollector::run()
{
    uint8_t phase1Counter = 0, phase2Counter = 0;
    bool phase1 = true;
    float minLoadPhase1 = 1.0f;
    while(true)
    {
        std::optional<float> currentCPUUsageOp = CurrentResourceUsage::getCPUUsage();
        float currentCPUUsage = currentCPUUsageOp.value_or(1.0f);
        if(phase1)
        {
            if(currentCPUUsage < minLoadPhase1)
            {
                minLoadPhase1 = currentCPUUsage;
            }
            phase1Counter++;
            if(phase1Counter > SECRETARY_PHASES_MAX_TICK[0])
            {
                phase1 = false; // switch to phase 2
                phase1Counter = 0;
            }
        }
        else // phase 2
        {
            if(currentCPUUsage <= minLoadPhase1 || phase2Counter > SECRETARY_PHASES_MAX_TICK[1]) // CPU is low enough or phase 2 is over
            {
                //std::cout << (int)phase2Counter << std::endl;
                phase2Counter = 0;
                minLoadPhase1 = 1.0f; // reset min load
                phase1 = true; // switch to phase 1
                cleanMemory(); // Do effective garbage cleaning
            }
            phase2Counter++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(SECRETARY_TICK_DURATION_MS)); // A little more actually
    }
}

void GarbageCollector::cleanMemory()
{
    while(!_garbage.empty())
    {
        const std::pair<void*, void(*)(void *)> &pointerAndDestructorFunction = _garbage.front();
        void (*destructorFunction)(void*) = pointerAndDestructorFunction.second;
        destructorFunction(pointerAndDestructorFunction.first); // Call destructor with raw pointer in parameter
        _garbage.pop();
    }
}

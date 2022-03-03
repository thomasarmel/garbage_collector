#include <thread>
#include "GarbageCollector.h"
#include "CurrentResourceUsage.h"

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
    unsigned char phase1Counter = 0, phase2Counter = 0;
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
            if(phase1Counter > 37)
            {
                phase1 = false;
                phase1Counter = 0;
            }
        }
        else
        {
            if(currentCPUUsage <= minLoadPhase1 || phase2Counter > 63)
            {
                phase2Counter = 0;
                minLoadPhase1 = 1.0f;
                phase1 = true;
                cleanMemory();
            }
            phase2Counter++;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

void GarbageCollector::cleanMemory()
{
    while(!_garbage.empty())
    {
        std::pair<void*, void(*)(void *)> pointerAndDestructorFunction = _garbage.front();
        void (*destructorFunction)(void*) = static_cast<void (*)(void *)>(pointerAndDestructorFunction.second);
        destructorFunction(pointerAndDestructorFunction.first);
        _garbage.pop();
    }
}

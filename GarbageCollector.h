#ifndef GARBAGE_COLLECTOR_GARBAGECOLLECTOR_H
#define GARBAGE_COLLECTOR_GARBAGECOLLECTOR_H

#include <queue>
#include <memory>
#include <thread>
#include <functional>
#include <utility>

class GarbageCollector
{
public:
    static GarbageCollector *getInstance();
    void add(void* pointer, void (*destructorFunction)(void*));
private:
    GarbageCollector();
    ~GarbageCollector() = default;

    [[noreturn]] void run();
    void cleanMemory();

    static GarbageCollector* _instance;
    std::queue<std::pair<void*, void(*)(void *)>> _garbage;
    std::unique_ptr<std::thread> _thread;
};

#endif //GARBAGE_COLLECTOR_GARBAGECOLLECTOR_H

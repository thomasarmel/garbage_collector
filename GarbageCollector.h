#ifndef GARBAGE_COLLECTOR_GARBAGECOLLECTOR_H
#define GARBAGE_COLLECTOR_GARBAGECOLLECTOR_H

#include <queue>
#include <memory>
#include <utility>

class GarbageCollector
{
public:
    static GarbageCollector *getInstance(); // Pattern singleton
    void add(void* pointer, void (*destructorFunction)(void*));
private:
    GarbageCollector();
    ~GarbageCollector() = default;

    [[noreturn]] void run(); // Run continuously on a separate thread
    void cleanMemory();

    static GarbageCollector* _instance;
    std::queue<std::pair<void*, void(*)(void *)>> _garbage; // Use a queue to avoid concurrent access problems
    std::unique_ptr<std::thread> _thread;
};

#endif //GARBAGE_COLLECTOR_GARBAGECOLLECTOR_H

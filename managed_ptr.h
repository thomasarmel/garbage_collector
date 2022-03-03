#ifndef GARBAGE_COLLECTOR_MANAGED_PTR_H
#define GARBAGE_COLLECTOR_MANAGED_PTR_H

#include <functional>
#include "GarbageCollector.h"

template <typename T>
class managed_ptr
{
public:

    explicit managed_ptr(T *object) : _object(object)
    {
    }

    ~managed_ptr()
    {
        GarbageCollector::getInstance()->add(_object, _deleter);
    }

private:
    T *_object;
    static void _deleter(void *object) {
        delete static_cast<T*>(object); // Comment this line and you will see a memory leak.
    };
};


#endif //GARBAGE_COLLECTOR_MANAGED_PTR_H

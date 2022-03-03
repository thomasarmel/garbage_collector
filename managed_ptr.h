#ifndef GARBAGE_COLLECTOR_MANAGED_PTR_H
#define GARBAGE_COLLECTOR_MANAGED_PTR_H

#include <cstddef>
#include <utility>
#include "GarbageCollector.h"

template <typename T>
class managed_ptr
{
public:

    explicit managed_ptr(T *object) : _objectAndReferencesCounter(new std::pair<T*, size_t>(object, 1))
    {
    }

    managed_ptr(const managed_ptr &other) : _objectAndReferencesCounter(other._objectAndReferencesCounter) // Copy constructor, increment references counter
    {
        _objectAndReferencesCounter->second++;
    }

    ~managed_ptr() // Destructor, decrement references counter and add object to garbage collector if there is no reference
    {
        if (_objectAndReferencesCounter->second == 1)
        {
            cleanAndAddToGC();
            return;
        }
        _objectAndReferencesCounter->second--;
    }

    managed_ptr& operator=(const managed_ptr &other)
    {
        if (this != &other)
        {
            if (_objectAndReferencesCounter->second == 1)
            {
                cleanAndAddToGC();
            }
            else
            {
                _objectAndReferencesCounter->second--;
            }
            _objectAndReferencesCounter = other._objectAndReferencesCounter;
            _objectAndReferencesCounter->second++;
        }
        return *this;
    }

    T *operator->() const
    {
        return _objectAndReferencesCounter->first;
    }

    T &operator*() const
    {
        return *(_objectAndReferencesCounter->first);
    }

private:
    void cleanAndAddToGC()
    {
        GarbageCollector::getInstance()->add(_objectAndReferencesCounter->first, _deleter);
        delete _objectAndReferencesCounter;
    }

    static void _deleter(void *object) // Called by the garbage collector, the function is static in a way to avoid duplicating the object
    {
        delete static_cast<T*>(object); // Comment this line, and you will see a memory leak.
    }
    std::pair<T*, size_t> *_objectAndReferencesCounter;
};

template <typename T, class... TTypes>
managed_ptr<T> make_managed(TTypes&&... _Args)
{
    return managed_ptr<T>(new T(_STD forward<TTypes>(_Args)...));
}

#endif //GARBAGE_COLLECTOR_MANAGED_PTR_H

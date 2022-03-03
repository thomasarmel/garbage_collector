#include <iostream>
#include <thread>
#include "managed_ptr.h"
#include "RandomObject.h"

int main()
{
    int i = 0;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while(true)
    {
        managed_ptr<RandomObject> randomObject(new RandomObject(i));
        std::this_thread::sleep_for(std::chrono::microseconds (10000));
        i++;

    }
#pragma clang diagnostic pop
    return 0;
}

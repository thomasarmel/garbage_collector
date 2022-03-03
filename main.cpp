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
        managed_ptr<int> intPtr(new int(i));
        std::this_thread::sleep_for(std::chrono::milliseconds (10));
        i++;

    }
#pragma clang diagnostic pop
    return 0;
}

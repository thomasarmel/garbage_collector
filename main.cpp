#include <iostream>
#include <thread>
#include "managed_ptr.h"
#include "RandomObject.h"

void changeObject(managed_ptr<RandomObject> obj);

int main()
{
    int i = 0;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while(true)
    {
        auto randomObject = make_managed<RandomObject>(i);
        std::cout << randomObject->getValue() << std::endl;
        changeObject(randomObject);
        std::cout << (*randomObject).getValue() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds (10));
        i++;

    }
#pragma clang diagnostic pop
    return 0;
}

void changeObject(managed_ptr<RandomObject> obj)
{
    obj->setValue(obj->getValue() * 2);
}
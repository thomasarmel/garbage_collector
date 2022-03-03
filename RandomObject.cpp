//#include <iostream>
#include "RandomObject.h"

RandomObject::RandomObject(int i) : _i(i)
{
    //std::cout << "RandomObject::RandomObject(" << _i << ")" << std::endl;
}

RandomObject::~RandomObject()
{
    //std::cout << "RandomObject::~RandomObject(" << _i << ")" << std::endl;
}

int RandomObject::getValue() const
{
    return _i;
}

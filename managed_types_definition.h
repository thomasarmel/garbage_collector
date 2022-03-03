#ifndef GARBAGE_COLLECTOR_MANAGED_TYPES_DEFINITION_H
#define GARBAGE_COLLECTOR_MANAGED_TYPES_DEFINITION_H

#include <string>
#include "managed_ptr.h"

typedef managed_ptr<int> Integer;
typedef managed_ptr<float> Float;
typedef managed_ptr<double> Double;
typedef managed_ptr<char> Character;
typedef managed_ptr<std::string> String;

#endif //GARBAGE_COLLECTOR_MANAGED_TYPES_DEFINITION_H

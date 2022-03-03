cmake_minimum_required(VERSION 3.16)
project(garbage_collector)

set(CMAKE_CXX_STANDARD 17)

add_executable(garbage_collector main.cpp GarbageCollector.cpp GarbageCollector.h RandomObject.cpp RandomObject.h managed_ptr.h CurrentResourceUsage.cpp CurrentResourceUsage.h)
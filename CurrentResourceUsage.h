#ifndef GARBAGE_COLLECTOR_CURRENTRESOURCEUSAGE_H
#define GARBAGE_COLLECTOR_CURRENTRESOURCEUSAGE_H

#ifdef _WIN32
#elif _WIN64
#else
#error "Unsupported platform"
#endif

#include <optional>

class CurrentResourceUsage
{
public:
    CurrentResourceUsage() = delete;
    ~CurrentResourceUsage() = delete;
    static std::optional<float> getCPUUsage();
};


#endif //GARBAGE_COLLECTOR_CURRENTRESOURCEUSAGE_H

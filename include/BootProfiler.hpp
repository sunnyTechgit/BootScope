#ifndef BOOT_PROFILER_HPP
#define BOOT_PROFILER_HPP

#include <string>

class BootProfiler {
public:
    std::string getBootTime();
    std::string getCriticalChain();
};

#endif
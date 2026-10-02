#ifndef SYSTEM_INFO_HPP
#define SYSTEM_INFO_HPP

#include <string>

class SystemInfo {
public:
    std::string getHostname();
    std::string getKernelVersion();
    std::string getArchitecture();
    std::string getMemoryInfo();
    std::string getCpuInfo();
    std::string getSystemdVersion();
};

#endif

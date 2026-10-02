#include "SystemInfo.hpp"

#include <unistd.h>
#include <fstream>
#include <sys/utsname.h>
#include <cstdio>

std::string SystemInfo::getHostname() {
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return std::string(hostname);
    }

    return "Unknown";
}
std::string SystemInfo::getKernelVersion() {
    std::ifstream file("/proc/version");

    if (file.is_open()) {
        std::string version;
        std::getline(file, version);
        return version;
    }

    return "Unknown";
}
std::string SystemInfo::getArchitecture() {
    struct utsname systemInfo;

    if (uname(&systemInfo) == 0) {
        return std::string(systemInfo.machine);
    }

    return "Unknown";
}
std::string SystemInfo::getMemoryInfo() {
    std::ifstream file("/proc/meminfo");

    if (!file.is_open()) {
        return "Unknown";
    }

    std::string line;
    std::string memTotal;
    std::string memAvailable;

    while (std::getline(file, line)) {
        if (line.find("MemTotal:") == 0) {
            memTotal = line;
        }

        if (line.find("MemAvailable:") == 0) {
            memAvailable = line;
        }

        if (!memTotal.empty() && !memAvailable.empty()) {
            break;
        }
    }

    return memTotal + " | " + memAvailable;
}
std::string SystemInfo::getCpuInfo() {
    std::ifstream file("/proc/cpuinfo");

    if (!file.is_open()) {
        return "Unknown";
    }

    std::string line;
    std::string model;
    std::string cores;
    std::string threads;

    while (std::getline(file, line)) {

        if (line.find("model name") == 0 && model.empty()) {
            model = line.substr(line.find(":") + 2);
        }

        if (line.find("cpu cores") == 0 && cores.empty()) {
            cores = line.substr(line.find(":") + 2);
        }

        if (line.find("siblings") == 0 && threads.empty()) {
            threads = line.substr(line.find(":") + 2);
        }

        if (!model.empty() && !cores.empty() && !threads.empty()) {
            break;
        }
    }

    return "Model: " + model +
           " | Cores: " + cores +
           " | Threads: " + threads;
}
std::string SystemInfo::getSystemdVersion() {
    FILE* pipe = popen("systemctl --version | head -n 1", "r");

    if (!pipe) {
        return "Unknown";
    }

    char buffer[256];

    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        pclose(pipe);
        return std::string(buffer);
    }

    pclose(pipe);
    return "Unknown";
}
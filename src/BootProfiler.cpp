#include "BootProfiler.hpp"

#include <cstdio>
#include <string>

std::string BootProfiler::getBootTime() {
    FILE* pipe = popen("systemd-analyze", "r");

    if (!pipe) {
        return "Unable to run systemd-analyze";
    }

    char buffer[512];
    std::string result;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);

    return result;
}

std::string BootProfiler::getCriticalChain() {
    FILE* pipe = popen("systemd-analyze critical-chain", "r");

    if (!pipe) {
        return "Unable to run systemd-analyze critical-chain";
    }

    char buffer[512];
    std::string result;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);

    return result;
}
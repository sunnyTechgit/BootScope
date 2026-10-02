#include "ServiceAnalyzer.hpp"

#include <cstdio>
#include <string>

std::string ServiceAnalyzer::getServiceBlame() {
    FILE* pipe = popen("systemd-analyze blame", "r");

    if (!pipe) {
        return "Unable to run systemd-analyze blame";
    }

    char buffer[512];
    std::string result;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);

    return result;
}
#include "BootAnalyzer.hpp"

#include <cstdio>
#include <string>
#include <regex>
#include <sstream>

std::string BootAnalyzer::executeCommand(const std::string& command) {

    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe) {
        return "";
    }

    char buffer[512];
    std::string result;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);

    return result;
}

std::string BootAnalyzer::getBootSummary() {

    std::string output = executeCommand("systemd-analyze");

    if (output.empty()) {
        return "Unable to analyze boot time.\n";
    }

    std::regex bootRegex(
        R"(Startup finished in ([0-9.]+)s \(firmware\) \+ ([0-9.]+)s \(loader\) \+ ([0-9.]+)s \(kernel\) \+ ([0-9.]+)s \(userspace\) = ([0-9.]+)s)"
    );

    std::regex targetRegex(
        R"(graphical\.target reached after ([0-9.]+)s in userspace)"
    );

    std::smatch bootMatch;
    std::smatch targetMatch;

    std::ostringstream result;

    if (std::regex_search(output, bootMatch, bootRegex)) {

        result << "Firmware Time : " << bootMatch[1] << " s\n";
        result << "Loader Time   : " << bootMatch[2] << " s\n";
        result << "Kernel Time   : " << bootMatch[3] << " s\n";
        result << "Userspace     : " << bootMatch[4] << " s\n";
        result << "Total Time    : " << bootMatch[5] << " s\n";
    }
    else {
        return "Unable to parse boot timing information.\n";
    }

    if (std::regex_search(output, targetMatch, targetRegex)) {

        result << "Target        : graphical.target\n";
        result << "Target Time   : " << targetMatch[1] << " s\n";
    }

    return result.str();
}
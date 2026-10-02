#ifndef BOOT_ANALYZER_HPP
#define BOOT_ANALYZER_HPP

#include <string>

class BootAnalyzer {
public:
    std::string getBootSummary();

private:
    std::string executeCommand(const std::string& command);
};

#endif
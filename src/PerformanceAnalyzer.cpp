#include "PerformanceAnalyzer.hpp"

#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

std::string PerformanceAnalyzer::analyzeBootPerformance() {

    FILE* pipe = popen("systemd-analyze", "r");

    if (!pipe) {
        return "Unable to analyze boot performance.";
    }

    char buffer[512];
    std::string output;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }

    pclose(pipe);

    double firmware = 0.0;
    double loader = 0.0;
    double kernel = 0.0;
    double userspace = 0.0;
    double total = 0.0;

    std::size_t pos = output.find("Startup finished in ");

    if (pos != std::string::npos) {

        std::string line = output.substr(pos);

        sscanf(
            line.c_str(),
            "Startup finished in %lfs (firmware) + %lfs (loader) + %lfs (kernel) + %lfs (userspace) = %lfs",
            &firmware,
            &loader,
            &kernel,
            &userspace,
            &total
        );
    }

    if (total <= 0.0) {
        return "Unable to parse boot performance data.";
    }

    double firmwarePercent = (firmware / total) * 100.0;
    double loaderPercent = (loader / total) * 100.0;
    double kernelPercent = (kernel / total) * 100.0;
    double userspacePercent = (userspace / total) * 100.0;

    std::ostringstream result;

    result << "\n[PERFORMANCE ANALYSIS]\n";

    result << std::fixed << std::setprecision(3);

    result << "Firmware  : " << firmware
           << " s (" << firmwarePercent << "%)\n";

    result << "Loader    : " << loader
           << " s (" << loaderPercent << "%)\n";

    result << "Kernel    : " << kernel
           << " s (" << kernelPercent << "%)\n";

    result << "Userspace : " << userspace
           << " s (" << userspacePercent << "%)\n";

    result << "Total     : " << total << " s\n";

    double largest = std::max({
        firmware,
        loader,
        kernel,
        userspace
    });

    result << "\n[DOMINANT BOOT PHASE]\n";

    if (largest == firmware) {
        result << "Firmware initialization\n";
    }
    else if (largest == loader) {
        result << "Boot loader\n";
    }
    else if (largest == kernel) {
        result << "Kernel initialization\n";
    }
    else {
        result << "Userspace initialization\n";
    }

    return result.str();
}
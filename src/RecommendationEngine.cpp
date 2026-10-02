#include "RecommendationEngine.hpp"

#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>

std::string RecommendationEngine::generateRecommendations() {

    FILE* pipe = popen("systemd-analyze", "r");

    if (!pipe) {
        return "Unable to generate recommendations.";
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

    result << "\n[BOOT RECOMMENDATIONS]\n";

    result << std::fixed << std::setprecision(3);

    /*
     * Firmware analysis
     */
    if (firmwarePercent >= 30.0) {

        result << "\n[HIGH] Firmware initialization\n";
        result << "Firmware consumes "
               << firmwarePercent
               << "% of total boot time.\n";

        result << "Recommendation: Check BIOS/UEFI startup settings "
               << "and unnecessary hardware initialization.\n";
    }

    /*
     * Loader analysis
     */
    if (loaderPercent >= 15.0) {

        result << "\n[MEDIUM] Boot loader\n";
        result << "Boot loader consumes "
               << loaderPercent
               << "% of total boot time.\n";

        result << "Recommendation: Review boot-loader configuration "
               << "and unnecessary boot entries.\n";
    }

    /*
     * Kernel analysis
     */
    if (kernelPercent >= 25.0) {

        result << "\n[MEDIUM] Kernel initialization\n";
        result << "Kernel consumes "
               << kernelPercent
               << "% of total boot time.\n";

        result << "Recommendation: Check kernel modules, "
               << "hardware initialization and kernel configuration.\n";
    }

    /*
     * Userspace analysis
     */
    if (userspacePercent >= 30.0) {

        result << "\n[HIGH] Userspace initialization\n";
        result << "Userspace consumes "
               << userspacePercent
               << "% of total boot time.\n";

        result << "Recommendation: Review services that start "
               << "during graphical startup.\n";
    }

    /*
     * Overall result
     */
    result << "\n[SUMMARY]\n";

    if (firmwarePercent >= userspacePercent &&
        firmwarePercent >= kernelPercent &&
        firmwarePercent >= loaderPercent) {

        result << "The largest boot phase is firmware initialization.\n";
        result << "BootScope recommends reviewing BIOS/UEFI startup configuration.\n";
    }
    else if (userspacePercent >= kernelPercent &&
             userspacePercent >= loaderPercent) {

        result << "The largest boot phase is userspace initialization.\n";
        result << "BootScope recommends reviewing startup services.\n";
    }
    else if (kernelPercent >= loaderPercent) {

        result << "The largest boot phase is kernel initialization.\n";
        result << "BootScope recommends reviewing kernel and hardware initialization.\n";
    }
    else {

        result << "The largest boot phase is the boot loader.\n";
        result << "BootScope recommends reviewing boot-loader configuration.\n";
    }

    return result.str();
}
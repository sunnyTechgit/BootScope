#include "ReportGenerator.hpp"

#include <fstream>
#include <string>

bool ReportGenerator::generateReport(
    const std::string& systemInfo,
    const std::string& bootAnalysis,
    const std::string& criticalChain,
    const std::string& serviceAnalysis,
    const std::string& bootSummary,
    const std::string& performanceAnalysis,
    const std::string& recommendations
) {

    std::ofstream report("reports/boot_report.txt");

    if (!report.is_open()) {
        return false;
    }

    report << "========================================\n";
    report << "          BOOTSCOPE REPORT\n";
    report << "========================================\n\n";

    report << "Linux Boot-Time Profiler & Analyzer\n\n";

    report << "========================================\n";
    report << "SYSTEM INFORMATION\n";
    report << "========================================\n";
    report << systemInfo << "\n\n";

    report << "========================================\n";
    report << "BOOT ANALYSIS\n";
    report << "========================================\n";
    report << bootAnalysis << "\n\n";

    report << "========================================\n";
    report << "CRITICAL BOOT CHAIN\n";
    report << "========================================\n";
    report << criticalChain << "\n\n";

    report << "========================================\n";
    report << "SERVICE ANALYSIS\n";
    report << "========================================\n";
    report << serviceAnalysis << "\n\n";

    report << "========================================\n";
    report << "BOOT SUMMARY\n";
    report << "========================================\n";
    report << bootSummary << "\n\n";

    report << "========================================\n";
    report << "PERFORMANCE ANALYSIS\n";
    report << "========================================\n";
    report << performanceAnalysis << "\n\n";

    report << "========================================\n";
    report << "BOOT RECOMMENDATIONS\n";
    report << "========================================\n";
    report << recommendations << "\n\n";

    report << "========================================\n";
    report << "Report generation completed successfully.\n";
    report << "========================================\n";

    report.close();

    return true;
}
#include <iostream>
#include <string>

#include "BootProfiler.hpp"
#include "SystemInfo.hpp"
#include "ServiceAnalyzer.hpp"
#include "BootAnalyzer.hpp"
#include "PerformanceAnalyzer.hpp"
#include "RecommendationEngine.hpp"
#include "ReportGenerator.hpp"

namespace {

void printBanner() {
    std::cout << "========================================\n"
              << "          BOOTSCOPE v1.0\n"
              << " Linux Boot-Time Profiler & Analyzer\n"
              << "========================================\n\n";
}

void printSection(const std::string& title, const std::string& body) {
    std::cout << "\n\n[" << title << "]\n" << body;
}

// Builds the formatted system information block.
// (Ideally this would live in SystemInfo as getSummary().)
std::string buildSystemInfo(SystemInfo& info) {
    return "Hostname: "     + info.getHostname()       + "\n"
         + "Kernel: "       + info.getKernelVersion()  + "\n"
         + "Architecture: " + info.getArchitecture()   + "\n"
         + "Memory: "       + info.getMemoryInfo()     + "\n"
         + "CPU: "          + info.getCpuInfo()        + "\n"
         + "Systemd: "      + info.getSystemdVersion() + "\n";
}

} // namespace

int main() {
    SystemInfo           systemInfo;
    BootProfiler         bootProfiler;
    ServiceAnalyzer      serviceAnalyzer;
    BootAnalyzer         bootAnalyzer;
    PerformanceAnalyzer  performanceAnalyzer;
    RecommendationEngine recommendationEngine;
    ReportGenerator      reportGenerator;

    // Collect all data once; reuse it for both display and the report.
    const std::string systemInfoOutput    = buildSystemInfo(systemInfo);
    const std::string bootTime            = bootProfiler.getBootTime();
    const std::string criticalChain       = bootProfiler.getCriticalChain();
    const std::string serviceAnalysis     = serviceAnalyzer.getServiceBlame();
    const std::string bootSummary         = bootAnalyzer.getBootSummary();
    const std::string performanceAnalysis = performanceAnalyzer.analyzeBootPerformance();
    const std::string recommendations     = recommendationEngine.generateRecommendations();

    // Display
    printBanner();
    std::cout << "[INFO] BootScope started successfully.\n"
              << "[INFO] " << systemInfoOutput;

    printSection("BOOT ANALYSIS",       bootTime);
    printSection("CRITICAL BOOT CHAIN", criticalChain);
    printSection("SERVICE ANALYSIS",    serviceAnalysis);
    printSection("BOOT SUMMARY",        bootSummary);

    // These two are printed without headers, as in the original code.
    // If they don't print their own headers, use printSection() for them too.
    std::cout << performanceAnalysis;
    std::cout << recommendations;

    // Report
    std::cout << "\n\n[REPORT]\n";
    const bool reportOk = reportGenerator.generateReport(
        systemInfoOutput,
        bootTime,
        criticalChain,
        serviceAnalysis,
        bootSummary,
        performanceAnalysis,
        recommendations);

    std::cout << (reportOk ? "[INFO] Report generated successfully.\n"
                           : "[ERROR] Failed to generate report.\n");

    std::cout << "\nBootScope analysis completed.\n";
    return reportOk ? 0 : 1;
}
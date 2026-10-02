#include <iostream>
#include "BootProfiler.hpp"
#include "SystemInfo.hpp"

int main() {

    SystemInfo systemInfo;
    BootProfiler bootProfiler;

    std::cout << "========================================\n";
    std::cout << "          BOOTSCOPE v1.0\n";
    std::cout << " Linux Boot-Time Profiler & Analyzer\n";
    std::cout << "========================================\n\n";

    std::cout << "[INFO] BootScope started successfully.\n";
    std::cout << "[INFO] Hostname: "
              << systemInfo.getHostname() << "\n";
    std::cout << "[INFO] Kernel: "
          << systemInfo.getKernelVersion() << "\n";
    std::cout << "[INFO] Architecture: "
          << systemInfo.getArchitecture() << "\n";
    std::cout << "[INFO] Memory: "
          << systemInfo.getMemoryInfo() << "\n";
    std::cout << "[INFO] CPU: "
          << systemInfo.getCpuInfo() << "\n";
    std::cout << "[INFO] Systemd: "
          << systemInfo.getSystemdVersion();
    std::cout << "\n\n[BOOT ANALYSIS]\n";
    std::cout << bootProfiler.getBootTime();
    
    std::cout << "\n\n[CRITICAL BOOT CHAIN]\n";
    std::cout << bootProfiler.getCriticalChain();

    return 0;
}

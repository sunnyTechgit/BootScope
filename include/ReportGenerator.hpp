#ifndef REPORT_GENERATOR_HPP
#define REPORT_GENERATOR_HPP

#include <string>

class ReportGenerator {
public:
    bool generateReport(
        const std::string& systemInfo,
        const std::string& bootAnalysis,
        const std::string& criticalChain,
        const std::string& serviceAnalysis,
        const std::string& bootSummary,
        const std::string& performanceAnalysis,
        const std::string& recommendations
    );
};

#endif

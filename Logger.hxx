#if !defined BPL_LOGGER_HXX_
#define      BPL_LOGGER_HXX_

#include <iostream>
#include <sstream>
#include <fstream>
#include <array>

namespace Tb
{
    enum class LoggerTypes : int
    {
       TRACE = 0,
       INFO  = 1,
       PERF  = 2,
       DEBUG = 3,
       WARN  = 4,
       ERROR = 5,
       FATAL = 6,
       ARRAY_SIZE
    };

    class Logger
    {
    public:
        Logger();
        ~Logger();
        // static std::ofstream loggerOss; 

        void trace(const std::string& traceLog);
        void trace(std::ostringstream& traceLog);

        void info(const std::string& informationLog);
        void info(std::ostringstream& informationLog);

        void perf(const std::string& performanceLog);
        void perf(std::ostringstream& performanceLog);

        void debug(const std::string& performanceLog);
        void debug(std::ostringstream& performanceLog);

        void warn(const std::string& performanceLog);
        void warn(std::ostringstream& performanceLog);

        void error(const std::string& performanceLog);
        void error(std::ostringstream& performanceLog);

        void fatal(const std::string& fatalLog);
        void fatal(std::ostringstream& fatalLog);

        bool isEnabled(const LoggerTypes type);

        bool isTraceEnabled();
        bool isInfoEnabled();
        bool isPerfEnabled();
        bool isDebugEnabled();

        void logStream(std::ostringstream& logOss, 
                       const LoggerTypes type);
        void logString(const std::string& logString, 
                       const LoggerTypes type);
        static Logger& get(); 
    private:
        std::ofstream& get_filestream();
        // static std::ofstream loggerOss;
        static constexpr int NUMBER_LOGGER_TYPES = (int)LoggerTypes::ARRAY_SIZE;
        using LoggingEnabled = std::array<bool, NUMBER_LOGGER_TYPES>;
        static LoggingEnabled logTypeOn_; 
    }; // class Logger

} // namespace Bpl

#endif    // BPL_LOGGER_HXX_

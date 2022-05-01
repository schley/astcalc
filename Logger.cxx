#include <fstream>
#include <sstream>

#include "Logger.hxx"
        
// std::ofstream Tb::Logger::loggerOss; 
  
Tb::Logger::LoggingEnabled Tb::Logger::logTypeOn_ = 
            {{ 
               false,   // TRACE 
               false,   // INFO
               false,   // PERF
               false,   // DEBUG
               true,    // WARN
               true,    // ERROR
               true     // FATAL
            }};

        
Tb::Logger::Logger()
{
    // loggerOss.open("./calc_debug.log", std::ios::out);
}
        
Tb::Logger::~Logger()
{
    // loggerOss.close();
}
        
void Tb::Logger::trace(const std::string& traceLog)
{
    if (logTypeOn_[(int) LoggerTypes::TRACE])
    {
        get_filestream() << "[TRACE] " << traceLog << "\n";
    }
}
void Tb::Logger::trace(std::ostringstream& traceLog)
{
    if (logTypeOn_[(int) LoggerTypes::TRACE])
    {
        trace(traceLog.str());
        traceLog.str("");
    }
}
        
void Tb::Logger::info(const std::string& informationLog)
{
    if (logTypeOn_[(int) LoggerTypes::INFO])
    {
        get_filestream() << "[INFO ] " << informationLog << "\n";
    }
}
void Tb::Logger::info(std::ostringstream& informationLog)
{
    if (logTypeOn_[(int) LoggerTypes::INFO])
    {
        info(informationLog.str());
        informationLog.str("");
    }
}
        
void Tb::Logger::perf(const std::string& performanceLog)
{
    if (logTypeOn_[(int) LoggerTypes::PERF])
    {
        get_filestream() << "[PERF ] " << performanceLog << "\n";
    }
}
void Tb::Logger::perf(std::ostringstream& performanceLog)
{
    if (logTypeOn_[(int) LoggerTypes::PERF])
    {
        perf(performanceLog.str() );
        performanceLog.str("");
    }
}

void Tb::Logger::debug(const std::string& debugLog)
{
    if (logTypeOn_[(int) LoggerTypes::DEBUG])
    {
        std::cout << "[DEBUG] " << debugLog << "\n";
        get_filestream() << "[DEBUG] " << debugLog << std::endl;
    }
}
void Tb::Logger::debug(std::ostringstream& debugLog)
{
    if (logTypeOn_[(int) LoggerTypes::DEBUG])
    {
        debug(debugLog.str() );
        debugLog.str("");
    }
}
        
void Tb::Logger::warn(const std::string& warningLog)
{
    if (logTypeOn_[(int) LoggerTypes::WARN])
    {
        get_filestream() << "[WARN ]" << warningLog << std::endl;
    }
}
void Tb::Logger::warn(std::ostringstream& warningLog)
{
    if (logTypeOn_[(int) LoggerTypes::WARN])
    {
        warn(warningLog.str() );
        warningLog.str("");
    }
}
        
void Tb::Logger::error(const std::string& errorLog)
{
    if (logTypeOn_[(int) LoggerTypes::ERROR])
    {
        get_filestream() << "[ERROR] " << errorLog << "\n";
    }
	std::cout << "[ERROR] " << errorLog << std::endl;
}
void Tb::Logger::error(std::ostringstream& errorLog)
{
    if (logTypeOn_[(int) LoggerTypes::ERROR])
    {
        error(errorLog.str());
        errorLog.str("");
    }
}

void Tb::Logger::fatal(const std::string& fatalLog)
{
    if (logTypeOn_[(int) LoggerTypes::FATAL])
    {
        get_filestream() << "[FATAL] " << fatalLog << "\n";
    }
}
void Tb::Logger::fatal(std::ostringstream& fatalLog)
{
    if (logTypeOn_[(int) LoggerTypes::FATAL])
    {
        fatal(fatalLog.str() );
        fatalLog.str("");
    }
}

bool Tb::Logger::isEnabled(const Tb::LoggerTypes type)
{
    bool currEnabled = Logger::logTypeOn_[(int) type];
    return currEnabled;
}

bool Tb::Logger::isDebugEnabled()
{
    bool debugEnabled = isEnabled(LoggerTypes::DEBUG);
    return debugEnabled;
}       

bool Tb::Logger::isTraceEnabled()
{
	bool traceEnabled = isEnabled(LoggerTypes::TRACE);
	return traceEnabled;
}

void Tb::Logger::logStream(std::ostringstream& logOss, const LoggerTypes type)
{
    std::string currLog = logOss.str().c_str(); 
    logString(currLog, type);
    logOss.str("");
}

void Tb::Logger::logString(const std::string& logString, 
                            const LoggerTypes type)
{
    if (logTypeOn_[(int) type])
    {
        switch (type)
        {
        case LoggerTypes::TRACE :
            trace(logString);
            break;
        case LoggerTypes::INFO :
            info(logString);
            break;
        case LoggerTypes::PERF :
            perf(logString);
            break;
        case LoggerTypes::DEBUG :
            debug(logString);
            break;
        case LoggerTypes::WARN :
            warn(logString);
            break;
        case LoggerTypes::ERROR :
            error(logString);
            break;
        case LoggerTypes::FATAL :
            fatal(logString);
            break;
        default :
            break;
        };
    }
} 

Tb::Logger& Tb::Logger::get()
{
    static Logger logger;
    return logger;
}    

std::ofstream& Tb::Logger::get_filestream()
{
    static std::ofstream loggingStream;
    static const std::string file_name {"calc_debug.log"};
    if (! loggingStream.is_open() )
    {
        loggingStream.open(file_name.c_str(), std::ios::out);
    }

    return loggingStream;
}
#pragma once
#include "g3log.hpp"

// compatibility macros
#define LOG_FATAL(...) do{ LOGF(FATAL, ##__VA_ARGS__); }while(0)
#define LOG_ERROR(...) do{ LOGF(ERR, ##__VA_ARGS__); }while(0)
#define LOG_WARN(...)  do{ LOGF(WARNING, ##__VA_ARGS__); }while(0)
#define LOG_INFO(...)  do{ LOGF(INFO, ##__VA_ARGS__); }while(0)
#define LOG_DEBUG(...) do{ LOGF(G3LOG_DEBUG, ##__VA_ARGS__); }while(0)
#define LOG_TRACE(...) do{ LOGF(G3LOG_DEBUG, ##__VA_ARGS__); }while(0)

namespace g3
{

void initializeLoggingFramework(const std::string &filenamePrefix, const std::string &path, const bool logToConsole = true);

}

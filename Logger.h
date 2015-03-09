/**
 *     \brief File containing class Logger
 */
#pragma once
#include <iostream>
#include <fstream>

/**
 * \brief Provides configurable output streams to logging macros
 */
class Logger
{
public:
    std::ostream* getInfStream();
    std::ostream* getDbgStream();
    std::ostream* getWrnStream();
    std::ostream* getErrStream();

    static Logger& getInstance();
    void setupOutputStreams(std::ostream* a_infStream, std::ostream* a_dbgStream, std::ostream* a_wrnStream, std::ostream* a_errStream);


private:
    static Logger* m_instance; ///< Keeps logger instance
    std::ostream* m_infStream; ///< Output stream for information
    std::ostream* m_dbgStream; ///< Output stream for  debugging
    std::ostream* m_wrnStream; ///< Output stream for  warning
    std::ostream* m_errStream; ///< Output stream for  errors

    Logger();
    Logger(const Logger& ) = delete;
    Logger& operator=(const Logger& ) = delete;
};


/**
 * \brief Logging macros
 *
 * LOG_INF allows providing information for user about a program
 * LOG_DBG allows providing information for programmer while running a program in debug mode
 * LOG_WRN allows providing warnings for user about a program
 * LOG_ERR allows providing errors for user about the program
 */
#define LOG_INF(...) if (Logger::getInstance().getInfStream() != nullptr) {*Logger::getInstance().getInfStream()  << "INF:" << __VA_ARGS__ << std::endl; }
#define LOG_DBG(...) if (Logger::getInstance().getDbgStream() != nullptr) {*Logger::getInstance().getDbgStream()  << __FILE__ << "(" << __LINE__ << "):" << " // " << "DBG:" << __VA_ARGS__ << std::endl; }
#define LOG_WRN(...) if (Logger::getInstance().getWrnStream() != nullptr) {*Logger::getInstance().getWrnStream()  << __FILE__ << "(" << __LINE__ << "):" << " // " << "WRN:" << __VA_ARGS__ << std::endl; }
#define LOG_ERR(...) if (Logger::getInstance().getErrStream() != nullptr) {*Logger::getInstance().getErrStream()  << __FILE__ << "(" << __LINE__ << "):" << " // " << "ERR:" <<__VA_ARGS__ << std::endl; }

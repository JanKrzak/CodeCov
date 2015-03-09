/**
 *     \brief File containing class LoggerConfigurator
 *     LoggerConfigurator serves class Logger. Sets up output streams for each kinds of log.
 */
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Logger.h"

/**
 * \brief Configures class Logger
 */
class LoggerConfigurator
{

public:
	/**
	 * \brief Enum provides kinds of log
	 */
	enum LogKind
	{
		INF, WRN, ERR, DBG
	};

	/**
	 * \brief Enum provides streams for outputting logs
	 */
	enum SinkConfiguration
	{
		STD_OUT, STD_ERR, LOG_FILE, SUPPRESS
	};

	LoggerConfigurator(Logger& a_loggerToConfigure);
	~LoggerConfigurator();
	bool setLogSink(LogKind a_kind, SinkConfiguration a_sink);
	bool openFileOutput(std::string fileName);
	void setFileOutputName(const std::string& fileOutputName);
	const std::string& getFileOutputName() const;

private:

	std::fstream m_fileOutput;      ///< Output file
	std::string m_fileOutputName;   ///< Name of output file
	Logger& m_logger;               ///< Reference to class Logger
};

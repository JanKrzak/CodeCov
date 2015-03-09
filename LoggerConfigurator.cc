#include "LoggerConfigurator.h"

/**
 * \brief Constructor with reference to class Logger as parameter
 *
 * \param[in] a_loggerToConfigure
 */
LoggerConfigurator::LoggerConfigurator(Logger& a_loggerToConfigure) :
		m_logger(a_loggerToConfigure)
{

}

/**
 * \brief Destructor without parameters
 *
 * Closes output file which is opened
 */
LoggerConfigurator::~LoggerConfigurator()
{
	m_fileOutput.close();
}

/**
 * Opens output file from private field
 *
 * \param[in] fileName
 * \return true if output file was opened otherwise return false
 */
bool LoggerConfigurator::openFileOutput(std::string fileName)
{

	m_fileOutput.open(fileName.c_str(),
			std::fstream::out | std::fstream::trunc);
	if (m_fileOutput)
		return true;

	else
		return false;
}

/**
 * Sets up logs and streams
 *
 * \param[in] a_kind
 * \param[in] a_sink
 * \return true if setting log sink was successful otherwise return false
 */
bool LoggerConfigurator::setLogSink(LogKind a_kind, SinkConfiguration a_sink)
{

	std::stringstream os1, os2, os3, os4;
	std::string s1, s2, s3, s4;

	bool retVal = false;

	switch (a_kind)
	{
	case INF:
		if (a_sink == STD_OUT)
		{
			Logger::getInstance().setupOutputStreams(&std::cout, nullptr,
					nullptr, nullptr);
			LOG_INF("tekst-INF");
			retVal = true;
		}
		else if (a_sink == STD_ERR)
		{
			Logger::getInstance().setupOutputStreams(&std::cerr, nullptr,
					nullptr, nullptr);
			LOG_INF("tekst-INF");
			retVal = true;
		}
		else if (a_sink == LOG_FILE)
		{
			Logger::getInstance().setupOutputStreams(&os1, nullptr, nullptr,
					nullptr);
			LOG_INF("tekst-INF");
			s1 = os1.str();
			m_fileOutput << s1 << std::endl;
			retVal = true;

		}
		else if (a_sink == SUPPRESS)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr,
					nullptr);
			LOG_INF("tekst-INF");
			retVal = true;
		}
		break;

	case DBG:
		if (a_sink == STD_OUT)
		{
			Logger::getInstance().setupOutputStreams(nullptr, &std::cout,
					nullptr, nullptr);
			LOG_DBG("tekst-DBG");
			retVal = true;
		}
		else if (a_sink == STD_ERR)
		{
			Logger::getInstance().setupOutputStreams(nullptr, &std::cerr,
					nullptr, nullptr);
			LOG_DBG("tekst-DBG");
			retVal = true;
		}
		else if (a_sink == LOG_FILE)
		{
			Logger::getInstance().setupOutputStreams(nullptr, &os2, nullptr,
					nullptr);
			LOG_DBG("tekst-DBG");
			s2 = os2.str();
			m_fileOutput << s2 << std::endl;
			retVal = true;

		}
		else if (a_sink == SUPPRESS)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr,
					nullptr);
			LOG_DBG("tekst-DBG");
			retVal = true;
		}
		break;

	case WRN:
		if (a_sink == STD_OUT)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr,
					&std::cout, nullptr);
			LOG_WRN("tekst-WRN");
			retVal = true;
		}
		else if (a_sink == STD_ERR)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr,
					&std::cerr, nullptr);
			LOG_WRN("tekst-WRN");
			retVal = true;
		}
		else if (a_sink == LOG_FILE)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, &os3,
					nullptr);
			LOG_WRN("tekst-WRN");
			s3 = os3.str();
			m_fileOutput << s3 << std::endl;
			retVal = true;

		}
		else if (a_sink == SUPPRESS)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr,
					nullptr);
			LOG_WRN("tekst-WRN");
			retVal = true;
		}

		break;

	case ERR:
		if (a_sink == STD_OUT)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr,
					&std::cout);
			LOG_ERR("tekst-ERR");
			retVal = true;
		}
		else if (a_sink == STD_ERR)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr,
					&std::cerr);
			LOG_ERR("tekst-ERR");
			retVal = true;
		}
		else if (a_sink == LOG_FILE)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr,
					&os4);
			LOG_ERR("tekst-ERR");
			s4 = os4.str();
			m_fileOutput << s4 << std::endl;
			retVal = true;

		}
		else if (a_sink == SUPPRESS)
		{
			Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr,
					nullptr);
			LOG_ERR("tekst-ERR");
			retVal = true;
		}

		break;

	}
	return retVal;
}

/**
 * Sets up name of output file
 */
void LoggerConfigurator::setFileOutputName(const std::string& fileOutputName)
{
	m_fileOutputName = fileOutputName;
}

/**
 * Gets name of output file
 *
 * \return m_fileOutputName
 */
const std::string& LoggerConfigurator::getFileOutputName() const
{
	return m_fileOutputName;
}

#include "Logger.h"

using namespace std;

Logger* Logger::m_instance = nullptr; ///< assigning nullptr to address of m_instance

/**
 * \brief Constructor without parameters
 *
 * Sets up output streams by default (m_infStream, m_dbgStream -> std::cout, m_wrnStream, m_errStream -> std::cerr).
 *
 * \param[out] m_infStream, m_dbgStream, m_wrnStream, m_errStream
 */
Logger::Logger() :
		m_infStream(&cout),
		m_dbgStream(&cout),
		m_wrnStream(&cerr),
		m_errStream(&cerr)
{
}

/**
 * Sets up output streams by settings of user.
 *
 * \param[in] a_infStream Output stream of information
 * \param[in] a_dbgStream Output stream of debugging
 * \param[in] a_wrnStream Output stream of warning
 * \param[in] a_errStream Output stream of errors
 */
void Logger::setupOutputStreams(ostream* a_infStream, ostream* a_dbgStream, ostream* a_wrnStream, ostream* a_errStream)
{
	m_infStream = a_infStream;
	m_dbgStream = a_dbgStream;
	m_wrnStream = a_wrnStream;
	m_errStream = a_errStream;
}

/**
 * Gets instance of class Logger
 *
 * \return m_instance pointer
 */
Logger& Logger::getInstance()
{
	if (m_instance == nullptr) {
		static Logger log;
		m_instance = &log;
	}

	return *m_instance;
}

/**
 * Gets debugging output stream of class Logger
 *
 * \return m_dbgStream Output stream of debugging
 */
ostream* Logger::getDbgStream()
{
	return m_dbgStream;
}

/**
 * Gets errors output stream of class Logger
 *
 * \return m_errStream Output stream of errors
 */
ostream* Logger::getErrStream()
{
	return m_errStream;
}

/**
 * Gets information output stream of class Logger
 *
 * \return m_infStream Output stream of information
 */
ostream* Logger::getInfStream()
{
	return m_infStream;
}

/**
 * Gets warning output stream of class Logger
 *
 * \return m_wrnStream Output stream of warning
 */
ostream* Logger::getWrnStream()
{
	return m_wrnStream;
}

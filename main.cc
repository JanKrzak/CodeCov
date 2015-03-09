/*
 * main.cc

 *
 *  Created on: 29 sty 2015
 *      Author: tuziakar
 */
#include <iostream>
#include "ProgramArguments.h"
#include "LoggerConfigurator.h"

using namespace std;

/*
 * \brief function to configure logs.
 * \param a_progArguments is an object of ProgramArguments class
 */
void configGlobalLogger(const ProgramArguments& a_progArguments)
{
	LoggerConfigurator loger(Logger::getInstance());
	bool isQuiet = a_progArguments.isQuietMode();
	bool isVerbose = a_progArguments.isVerboseMode() ;

	if (a_progArguments.getLogFilename() == "-")
	{
		if (isQuiet == true && isVerbose == false)
		{
			loger.setLogSink(loger.INF, loger.SUPPRESS);
			loger.setLogSink(loger.DBG, loger.SUPPRESS);
			loger.setLogSink(loger.WRN, loger.STD_ERR);
			loger.setLogSink(loger.ERR, loger.STD_ERR);
		}
		else if (isVerbose == true && isQuiet == false)
		{
			loger.setLogSink(loger.INF, loger.STD_OUT);
			loger.setLogSink(loger.DBG, loger.STD_OUT);
			loger.setLogSink(loger.WRN, loger.STD_ERR);
			loger.setLogSink(loger.ERR, loger.STD_ERR);
		}
		else if (isVerbose == true && isQuiet == true)
		{
			loger.setLogSink(loger.INF, loger.SUPPRESS);
			loger.setLogSink(loger.DBG, loger.STD_OUT);
			loger.setLogSink(loger.WRN, loger.STD_ERR);
			loger.setLogSink(loger.ERR, loger.STD_ERR);
		}
		else
		{
		    loger.setLogSink(loger.INF, loger.STD_OUT);
		    loger.setLogSink(loger.DBG, loger.SUPPRESS);
		    loger.setLogSink(loger.WRN, loger.STD_ERR);
		    loger.setLogSink(loger.ERR, loger.STD_ERR);
		}
	}
	else
	{
		loger.setFileOutputName(a_progArguments.getLogFilename());
		loger.openFileOutput(loger.getFileOutputName());
		loger.setLogSink(loger.INF, loger.LOG_FILE);
		loger.setLogSink(loger.DBG, loger.LOG_FILE);
		loger.setLogSink(loger.WRN, loger.LOG_FILE);
		loger.setLogSink(loger.ERR, loger.LOG_FILE);
		loger.setLogSink(loger.ERR, loger.LOG_FILE);
	}
}

int main(int argc, const char* argv[])
{
	ProgramArguments progArgs;

	if (!progArgs.parse(argc, argv))
	{
		cerr << progArgs.getStrError() << endl;
		return -1;
	}

	if (progArgs.isHelpReqested())
	{
		return 0;
	}

	configGlobalLogger(progArgs);

	return 0;
}


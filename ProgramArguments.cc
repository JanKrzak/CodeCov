#include "ProgramArguments.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>
#include <tclap/MultiArg.h>
#include <vector>
#include <cstring>

using namespace TCLAP;
using namespace std;

ProgramArguments::ProgramArguments():
  m_argsToClang(nullptr),
  m_numOfClangArgs(0),
  m_verbose(false),
  m_quiet(false),
  m_isHelpReqested(false)
{
}

bool ProgramArguments::isVerboseMode() const
{
	if(!m_verbose) return false;
	else return true;
}
bool ProgramArguments::isQuietMode() const
{
	if(!m_quiet) return false;
	else return true;
}
bool ProgramArguments::isHelpReqested() const
{
	if(!m_isHelpReqested) return false;
	else return true;
}


/*
 * \brief function gets number of arguments and arguments array and parse all arguments with specified flag
 * \details After parsing clang arguments are saved into vector of string.
 * \return  true if there are needed arguments otherwise it return false
 */
bool ProgramArguments::parse(int argc, const char* argv[])
{
    UnlabeledValueArg<string> fileName("name", "test file name", "Input name", "", "Input file name", true);
    MultiArg<string>          includeArgs("I", "include", "Include is Optional Function", false, "library path");
    MultiArg<string>          debugArgs("D", "debug", "Debug is Optional Function", false, "Debug Path");
    ValueArg<string>          logArg("l", "log", "To show log, for argument enter '-' ", true, "","log");
    SwitchArg            	  verbose("v","verbose","verbosity",false);
    SwitchArg                 quiet("q","quiet","quiet log",false);

    try
    {
        CmdLine cmd("", ' ', "1.0");

        cmd.setExceptionHandling(false);
        cmd.add(fileName);
        cmd.add(includeArgs);
        cmd.add(debugArgs);
        cmd.add(logArg);
        cmd.add(verbose);
        cmd.add(quiet);
        cmd.parse(argc, argv);
    }
    catch(ArgException &e)
    {
        m_strErr = "Error: " + e.error() +  " for arg " + e.argId();
        return false;
    }
    catch(ExitException &e)
    {
    	m_isHelpReqested = true;
    	return true;
    }

    m_argsIncludeList = includeArgs.getValue();
    m_argsDebugList = debugArgs.getValue();
    m_argNameOfFileToInstrument = fileName.getValue();
    m_logFilename = logArg.getValue();

    if ( verbose.isSet() )
    {
    	m_verbose = verbose.getValue();
    }
    if ( quiet.isSet() )
    {
        m_quiet = quiet.getValue();
    }

    prepareClangArgs();

    return true;
}

ProgramArguments::~ProgramArguments()
{
	if (m_argsToClang != nullptr)
	{
		for (unsigned i = 0; i < m_numOfClangArgs; i++)
		{
			if (m_argsToClang[i] != nullptr)
			{
				delete[] m_argsToClang[i];
			}
		}
		delete[] m_argsToClang;
	}
}

/*
 * \brief Function get log name.
 * \return log name
 */
string ProgramArguments::getLogFilename() const
 {
	return m_logFilename;
 }

/*
 * \brief Copy clang arguments from vectors to one string and add flags -I and -D before each argument
 */
void ProgramArguments::prepareClangArgs()
 {
    m_numOfClangArgs =  m_argsIncludeList.size() + m_argsDebugList.size();
    m_argsToClang = new char*[m_numOfClangArgs];

    unsigned argCnt = 0;
    string clangArg;
    // add includes
    for (const string& arg: m_argsIncludeList)
    {
        clangArg = "-I" + arg;
        m_argsToClang[argCnt] = new char[arg.size()];
        strcpy(m_argsToClang[argCnt], clangArg.c_str());

        ++argCnt;
    }
    // add defines
    for (const string& arg: m_argsDebugList)
    {
        clangArg = "-D" + arg;
        m_argsToClang[argCnt] = new char[arg.size()];
        strcpy(m_argsToClang[argCnt], clangArg.c_str());

        ++argCnt;
    }
}

/*
 * \brief This function provides only debug and include arguments to use in clang parser.
 * \param a_numOfArguments an integer argument has a value of number of clang arguments
 * \return character array of clang arguments
 */
char** ProgramArguments::getClangParserParams(int& a_numOfClangArgs)
{
	a_numOfClangArgs = m_numOfClangArgs;
    return m_argsToClang;
}

/*
 * \brief Function provide file name to instrumentalization
 * \return input name
 */
string ProgramArguments::getNameOfFileToInstrument() const
{
    return m_argNameOfFileToInstrument;
}
/**
 *\brief Returns string representation of last occured error
 */
const char* ProgramArguments::getStrError()
{
	cout<<"Type --help for help"<<endl;
    return m_strErr.c_str();
}

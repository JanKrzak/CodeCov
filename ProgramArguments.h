#pragma once

#include <string>
#include <vector>

/**
* \brief Class to Parse program arguments.
*/
class ProgramArguments {
public:
	ProgramArguments();
	~ProgramArguments();

	ProgramArguments(const ProgramArguments& ) = delete;
	ProgramArguments& operator=(const ProgramArguments& ) = delete;

	bool parse(int argc, const char* argv[]);
	char** getClangParserParams(int& a_numOfArguments);
	bool isVerboseMode() const;
	bool isQuietMode() const;
	bool isHelpReqested() const;
	std::string getLogFilename() const;
	std::string getNameOfFileToInstrument() const;
	const char* getStrError();

private:
	void prepareClangArgs();

	std::vector<std::string> m_argsIncludeList;
	std::vector<std::string> m_argsDebugList;
    std::string m_argNameOfFileToInstrument;
    std::string m_logFilename;
	std::string m_strErr;

	char** m_argsToClang;
	unsigned m_numOfClangArgs;
	bool m_verbose, m_quiet;
	bool m_isHelpReqested;
};

#include "../ProgramArguments.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

ProgramArguments testArg;

TEST(ProgramArguments, CheckParseFunction)
{
	const char* argvInclude[] ={
				"test.cpp",
				"-l -",
				"-I path",
				"-D Debug",
				"-v",
				"-q"
		};
	EXPECT_TRUE(testArg.parse(8, argvInclude));
};

TEST(ProgramArguments, CheckVerboseMode)
{
	EXPECT_TRUE(testArg.isVerboseMode());
};

TEST(ProgramArguments, CheckQuieteMode)
{
	EXPECT_TRUE(testArg.isQuietMode());
};

TEST(ProgramArguments, getClangParserParams)
{
	string correctArgs ("-Ipath-DDebug");
	int numberOfParam = 7;
	string clangArg;
    char** clangTabArgs = testArg.getClangParserParams(numberOfParam);

    for (int i = 0; i < numberOfParam; i++)
    {
    	clangArg += clangTabArgs[i];
    }
    EXPECT_EQ(correctArgs,clangArg);
};

TEST(ProgramArguments, MissLoggerArgumentsToParse)
{
	const char* argvMore[] ={
			"test.cpp",
			"-I path"
	};
	EXPECT_FALSE(testArg.parse(3, argvMore));
};

TEST(ProgramArguments, WrongArgumentsToParse)
{
	const char* argvBad[] ={
			"test.cpp",
			"-l -",
			"-I"
	};
	EXPECT_FALSE(testArg.parse(4, argvBad));
};

TEST(ProgramArguments, FailedisHelpReqested)
{
	const char* argvHelp[] ={
				"test.cpp",
				"--help"
	};
	EXPECT_TRUE(testArg.parse(3, argvHelp));
	EXPECT_TRUE(testArg.isHelpReqested());
};

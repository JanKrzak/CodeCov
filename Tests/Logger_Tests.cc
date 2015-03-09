#include "../Logger.h"
#include <sstream>
#include <iostream>
#include <string>
#include "gtest/gtest.h"


TEST(Logger, StreamCheck) {
       std::ostringstream os1;
       std::ostringstream os2;
       std::ostringstream os3;
       std::ostringstream os4;
       Logger::getInstance().setupOutputStreams(&os1, &os2, &os3, &os4);

       EXPECT_EQ(Logger::getInstance().getInfStream(), &os1);
       EXPECT_EQ(Logger::getInstance().getDbgStream(), &os2);
       EXPECT_EQ(Logger::getInstance().getWrnStream(), &os3);
       EXPECT_EQ(Logger::getInstance().getErrStream(), &os4);
}

TEST(Logger, TextCheck) {
       std::ostringstream os1;
       std::ostringstream os2;
       std::ostringstream os3;
       std::ostringstream os4;
       Logger::getInstance().setupOutputStreams(&os1, &os2, &os3, &os4);
       LOG_INF("tekst1");
       LOG_DBG("tekst2");
       LOG_WRN("tekst3");
       LOG_ERR("tekst4");
       std::string osstr1 = os1.str();
       std::string osstr2 = os2.str();
       std::string osstr3 = os3.str();
       std::string osstr4 = os4.str();
       EXPECT_NE(osstr1.find("tekst1"), std::string::npos);
       EXPECT_NE(osstr2.find("tekst2"), std::string::npos);
       EXPECT_NE(osstr3.find("tekst3"), std::string::npos);
       EXPECT_NE(osstr4.find("tekst4"), std::string::npos);
}

TEST(Logger, ModeCheck) {
       std::ostringstream os1;
       std::ostringstream os2;
       std::ostringstream os3;
       std::ostringstream os4;
       Logger::getInstance().setupOutputStreams(&os1, &os2, &os3, &os4);
       LOG_INF("tekst1");
       LOG_DBG("tekst2");
       LOG_WRN("tekst3");
       LOG_ERR("tekst4");
       std::string osstr1 = os1.str();
       std::string osstr2 = os2.str();
       std::string osstr3 = os3.str();
       std::string osstr4 = os4.str();
       EXPECT_NE(osstr1.find("INF"), std::string::npos);
       EXPECT_NE(osstr2.find("DBG"), std::string::npos);
       EXPECT_NE(osstr3.find("WRN"), std::string::npos);
       EXPECT_NE(osstr4.find("ERR"), std::string::npos);
}

TEST(Logger, ModeCheck1) {
       std::ostringstream os1;
       std::ostringstream os2;
       std::ostringstream os3;
       std::ostringstream os4;
       Logger::getInstance().setupOutputStreams(nullptr, nullptr, nullptr, nullptr);
       LOG_INF("tekst1");
       LOG_DBG("tekst2");
       LOG_WRN("tekst3");
       LOG_ERR("tekst4");
       std::string osstr1 = os1.str();
       std::string osstr2 = os2.str();
       std::string osstr3 = os3.str();
       std::string osstr4 = os4.str();
       EXPECT_EQ(osstr1.find("INF"), std::string::npos);
       EXPECT_EQ(osstr2.find("DBG"), std::string::npos);
       EXPECT_EQ(osstr3.find("WRN"), std::string::npos);
       EXPECT_EQ(osstr4.find("ERR"), std::string::npos);
}

#include "Logger.h"

void Logger::basicConfig(string name)
{
    filename = name;
    LoggerFile.open(filename, ios::out);
    LoggerFile.close();
}

void Logger::debug(string LOG_MESSAGE)
{
    LoggerFile.open(filename, ios::app | ios::out | ios::binary);
    time_t proccesTime = time(nullptr);
    string timeline = ctime(&proccesTime);
    timeline.pop_back();
    string format = timeline + " DEBUG " + LOG_MESSAGE;
    LoggerFile << format << endl;
    LoggerFile.close();
}

void Logger::info(string LOG_MESSAGE)
{
    LoggerFile.open(filename, ios::app | ios::out | ios::binary);
    time_t proccesTime = time(nullptr);
    string timeline = ctime(&proccesTime);
    timeline.pop_back();
    string format = timeline + " INFO " + LOG_MESSAGE;
    LoggerFile << format << endl;
    LoggerFile.close();
}

void Logger::warning(string LOG_MESSAGE)
{
    LoggerFile.open(filename, ios::app | ios::out | ios::binary);
    time_t proccesTime = time(nullptr);
    string timeline = ctime(&proccesTime);
    timeline.pop_back();
    string format = timeline + " WARNING " + LOG_MESSAGE;
    LoggerFile << format << endl;
    LoggerFile.close();
}

void Logger::error(string LOG_MESSAGE)
{
    LoggerFile.open(filename, ios::app | ios::out | ios::binary);
    time_t proccesTime = time(nullptr);
    string timeline = ctime(&proccesTime);
    timeline.pop_back();
    string format = timeline + " ERROR " + LOG_MESSAGE;
    LoggerFile << format << endl;
    LoggerFile.close();
}

void Logger::critical(string LOG_MESSAGE)
{
    LoggerFile.open(filename, ios::app | ios::out | ios::binary);
    time_t proccesTime = time(nullptr);
    string timeline = ctime(&proccesTime);
    timeline.pop_back();
    string format = timeline + " CRITICAL " + LOG_MESSAGE;
    LoggerFile << format << endl;
    LoggerFile.close();
}
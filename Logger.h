#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

class Logger
{
    private:
        ofstream LoggerFile;
        string filename;
    public:
        Logger(){}
        void basicConfig(string name);
        void debug(string LOG_MESSAGE);
        void info(string LOG_MESSAGE);
        void warning(string LOG_MESSAGE);
        void error(string LOG_MESSAGE);
        void critical(string LOG_MESSAGE);   
};

#endif




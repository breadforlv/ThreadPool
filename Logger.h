#ifndef LOGGER
#define LOGGER

#include <string>
#include <mutex>
#include <fstream>

class Logger{
    public:
       Logger(const std::string& filename="log.txt");

       void log(const std::string& message);

       ~Logger();

    private:
       std::ofstream logFile;
       std::mutex mutex;
};

#endif
#include "Logger.h"
#include <iostream>


Logger::Logger(const std::string& filename)
        : logFile(filename, std::ios::app) {
        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file.\n";
        }
    }

    // 写日志的线程安全方法
        void Logger::log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex);
        logFile << message << std::endl;
        std::cout << message << std::endl;  // 同时打印到控制台
    }

Logger::~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
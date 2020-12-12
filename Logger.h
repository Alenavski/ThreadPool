//
// Created by Asus on 11.12.2020.
//

#ifndef MAIN_CPP_LOGGER_H
#define MAIN_CPP_LOGGER_H

#include <fstream>

class Logger {
public:
    Logger(std::string filename);
    ~Logger();
    void printInitializeMessage(int count);
    void printCreateThreadMessage(int threadIndex);
    void printAddTaskMessage(int threadIndex);
    void printDeleteTaskMessage(int threadIndex);
    void printErrorAddingTaskMessage();
    void printErrorExecutingMessage(int threadIndex, std::string exception);
private:
    std::ofstream out;
};


#endif //MAIN_CPP_LOGGER_H

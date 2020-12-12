//
// Created by Asus on 11.12.2020.
//

#include "Logger.h"

Logger::Logger(std::string filename) {
    out.open("../" + filename + ".txt");
}

void Logger::printInitializeMessage(int count) {
    out << "INFO : ThreadPool was created with " << count << " threads\n";
}

Logger::~Logger() {
    out.close();
}

void Logger::printAddTaskMessage(int threadIndex) {
    out << "INFO : " << threadIndex << " thread start routine\n";
}

void Logger::printDeleteTaskMessage(int threadIndex) {
    out << "INFO : " << threadIndex << " thread was deleted\n";
}

void Logger::printErrorAddingTaskMessage() {
    out << "ERROR : ThreadPool reached limit of threads\n";
}

void Logger::printErrorExecutingMessage(int threadIndex, std::string exception) {
    out << "ERROR : " << exception << "\n";
}

void Logger::printCreateThreadMessage(int threadIndex) {
    out << "INFO : " << threadIndex << " thread was created\n";
}



//
// Created by Asus on 29.11.2020.
//

#ifndef MAIN_CPP_THREADPOOL_H
#define MAIN_CPP_THREADPOOL_H

#include <queue>
#include <Windows.h>
#include <functional>
#include <set>
#include "Logger.h"
#include <exception>

class ThreadPool {
public:
    inline static ThreadPool *currentThreadPool;
private:
    struct ThreadInfo {
        std::function<void(LPVOID)> function;
        LPVOID parameters;
        LPDWORD threadIndex;
        HANDLE thread;
    } ;
    std::vector<ThreadInfo> threadInfos;

    int threadCount = 2; //N
    static const int maxCount = 10; //K

    std::set<int> availableThreads;

    static void idle(LPVOID lpParams);
    static DWORD WINAPI threadSwitcher(LPVOID lpParams);

    CRITICAL_SECTION csThreadInfo;
    CRITICAL_SECTION csLogger;

    Logger *logger;
public:
    void getNewTask (std::function<void(LPVOID lpParams)> pointer, LPVOID lpParams);
    ThreadPool(int count);
    ~ThreadPool();
};


#endif //MAIN_CPP_THREADPOOL_H

//
// Created by Asus on 29.11.2020.
//

#include "ThreadPool.h"

#include <utility>

void ThreadPool::idle(LPVOID lpParams) { }

DWORD WINAPI ThreadPool::threadSwitcher(LPVOID lpParam) {
    int index = *(int *) lpParam;

    EnterCriticalSection(&ThreadPool::currentThreadPool->csThreadInfo);
    ThreadInfo threadInfo = ThreadPool::currentThreadPool->threadInfos[index];
    LeaveCriticalSection(&ThreadPool::currentThreadPool->csThreadInfo);

    try {
        threadInfo.function(threadInfo.parameters);
    }
    catch (std::exception &e) {

        EnterCriticalSection(&ThreadPool::currentThreadPool->csLogger);
        ThreadPool::currentThreadPool->logger->printErrorExecutingMessage(index, e.what());
        LeaveCriticalSection(&ThreadPool::currentThreadPool->csLogger);

    }
    return 0;
}

ThreadPool::ThreadPool(int count) {
    ThreadPool::currentThreadPool = this;
    logger = new Logger("ThreadPoolLog");

    InitializeCriticalSectionAndSpinCount(&csThreadInfo, 10000);
    InitializeCriticalSectionAndSpinCount(&csLogger, 10000);

    if (count > maxCount) {

        EnterCriticalSection(&ThreadPool::currentThreadPool->csLogger);
        logger->printErrorAddingTaskMessage();
        LeaveCriticalSection(&ThreadPool::currentThreadPool->csLogger);

        threadCount = maxCount;
    }
    else {
        threadCount = count;
    }
    for (int i = 0; i < threadCount; i++) {
        int *index = new int;
        *index = i;
        ThreadInfo idleThread;
        idleThread.parameters = NULL;
        idleThread.function = ThreadPool::idle;
        idleThread.threadIndex = (LPDWORD)index;
        LPVOID lpParams = (LPVOID)index;
        HANDLE thread = CreateThread(NULL, 0, threadSwitcher, lpParams, CREATE_SUSPENDED, NULL);
        idleThread.thread = thread;

        EnterCriticalSection(&this->csThreadInfo);
        threadInfos.push_back(idleThread);
        availableThreads.insert(i);
        LeaveCriticalSection(&this->csThreadInfo);

    }

    EnterCriticalSection(&this->csLogger);
    logger->printInitializeMessage(threadCount);
    LeaveCriticalSection(&this->csLogger);
}

void ThreadPool::getNewTask(std::function<void(LPVOID lpParams)> pointer, LPVOID lpParams) {
    if (availableThreads.empty()) {
        if (threadCount == maxCount) {

            EnterCriticalSection(&ThreadPool::currentThreadPool->csLogger);
            logger->printErrorAddingTaskMessage();
            LeaveCriticalSection(&ThreadPool::currentThreadPool->csLogger);

            return;
        }
        ThreadInfo idleThread;
        int *index = new int;
        *index = threadCount;
        LPVOID lpParams = (LPVOID)index;
        idleThread.parameters = NULL;
        idleThread.function = ThreadPool::idle;
        idleThread.threadIndex = (LPDWORD)index;
        HANDLE thread = CreateThread(NULL, 0, threadSwitcher, lpParams, CREATE_SUSPENDED, NULL);
        idleThread.thread = thread;

        EnterCriticalSection(&ThreadPool::currentThreadPool->csThreadInfo);
        threadInfos.push_back(idleThread);
        availableThreads.insert(threadCount);
        LeaveCriticalSection(&ThreadPool::currentThreadPool->csThreadInfo);

        EnterCriticalSection(&ThreadPool::currentThreadPool->csLogger);
        logger->printCreateThreadMessage(threadCount);
        LeaveCriticalSection(&ThreadPool::currentThreadPool->csLogger);

        threadCount++;
    }

    EnterCriticalSection(&ThreadPool::currentThreadPool->csThreadInfo);
    int availableThread = *availableThreads.begin();
    availableThreads.erase(availableThread);
    threadInfos[availableThread].function = pointer;
    threadInfos[availableThread].parameters = lpParams;
    HANDLE thread = threadInfos[availableThread].thread;
    LeaveCriticalSection(&ThreadPool::currentThreadPool->csThreadInfo);

    ResumeThread(thread);

    EnterCriticalSection(&ThreadPool::currentThreadPool->csLogger);
    logger->printAddTaskMessage(availableThread);
    LeaveCriticalSection(&ThreadPool::currentThreadPool->csLogger);

}

ThreadPool::~ThreadPool() {
    for (int i = 0; i < threadCount; i++) {
        TerminateThread(threadInfos[i].thread, 0);
        CloseHandle(threadInfos[i].thread);

        EnterCriticalSection(&ThreadPool::currentThreadPool->csLogger);
        logger->printDeleteTaskMessage((int)*threadInfos[i].threadIndex);
        LeaveCriticalSection(&ThreadPool::currentThreadPool->csLogger);

    }
    delete logger;
}

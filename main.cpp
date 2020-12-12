#include <iostream>
#include "ThreadPool.h"

void test(LPVOID lpParams){
    printf("hello world\n");
}

void test2(LPVOID lpParams) {
    printf("PASHOL V ZHOPU\n");
}

void test3(LPVOID lpParams) {
    printf("goodbye world\n");
}

void test4(LPVOID lpParams) {
    throw std::exception();
}

int main() {
    printf("please don't be stupid write n\n");
    int n;
    std::cin >> n;
    ThreadPool *threadPool = new ThreadPool(n);
    while (true) {
        printf("1 - add function\n2 - exit v window\n");
        int x;
        std::cin >> x;
        if (x == 1) {
            threadPool->getNewTask(test, nullptr);
            threadPool->getNewTask(test2, nullptr);
            threadPool->getNewTask(test3, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask([](LPVOID lpParam) {
                printf("Please write 2\n");
            }, nullptr);
            threadPool->getNewTask(test4, nullptr);
        }
        if (x == 2) {
            delete threadPool;
            break;
        }
    }
    return 0;
}

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex globalMutex;

void foo() {
    unsigned int sum = 0;
    for (unsigned int i = 1; i < 10000; ++i) {
        unsigned int subSum = 1;
        for (unsigned int j = 1; j < i; ++ j) {
            subSum *= j;
        }
        sum += subSum;
    }
    std::lock_guard<std::mutex> lock(globalMutex);
    std::cout << "Sum : " << sum << '\n';
}

std::chrono::milliseconds getTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

int main() {
    std::cout << "Hello" << '\n';
    auto startTime = getTime();
    std::thread myThread(foo);
    myThread.join();
    auto endTime = getTime();
    auto executionTime = endTime - startTime;
    std::cout << "Execution time : " << executionTime.count() << '\n';
    return 0;
}
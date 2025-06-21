#include <chrono>
#include <iostream>
#include <thread>

void foo() {
    unsigned int sum = 0;
    for (unsigned int i = 1; i < 10000; ++i) {
        unsigned int subSum = 1;
        for (unsigned int j = 1; j < i; ++j) {
            subSum *= j;
        }
        sum += subSum;
    }
    std::cout << "Sum : " << sum << '\n';
}

int main() {
    std::cout << "Hello" << '\n';
    std::chrono::duration startTime = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::high_resolution_clock::now().time_since_epoch());
    std::thread myThread(foo);
    myThread.join();
    std::chrono::duration endTime = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::high_resolution_clock::now().time_since_epoch());
    std::chrono::duration performanceDuration = endTime - startTime;
    std::cout << "Execution time : " << performanceDuration.count() << '\n';
    return 0;
}
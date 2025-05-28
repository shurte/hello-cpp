#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

thread_local int someTreadLocalValue = 0;
std::mutex globalMutex;

void threadFunction(int someValue) {
    someTreadLocalValue = someValue;
    {
        std::lock_guard<std::mutex> lock(globalMutex);
        std::cout << "Thread : " << std::this_thread::get_id() << "; value = " << someTreadLocalValue << '\n';
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    {
        std::lock_guard<std::mutex> lock(globalMutex);
        std::cout << "Thread : " << std::this_thread::get_id() << "; value = " << someTreadLocalValue << '\n';
    }
}

int main() {
    std::cout << "Hello" << '\n';
    std::thread threadOne(threadFunction, 10);
    std::thread threadTwo(threadFunction, 12);
    threadOne.join();
    threadTwo.join();
    return 0;
}
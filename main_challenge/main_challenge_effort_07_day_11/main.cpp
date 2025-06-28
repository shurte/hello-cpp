#include <iostream>
#include <mutex>
#include <thread>

std::recursive_mutex globalRecursiveMutex;

unsigned int calculate(unsigned short limit) {
    std::lock_guard<std::recursive_mutex> lock(globalRecursiveMutex);

    if (limit <= 1) {
        return limit;
    } else {
        return limit * calculate(limit - 1);
    }
}

void foo(unsigned short limit) {
    std::cout << "Foo() : " << limit << '\n';
    unsigned int result = calculate(limit);
    std::cout << "Result : " << result << '\n';
}

int main() {
    std::cout << "Hello" << '\n';
    std::thread myThread(foo, 3);
    myThread.join();
    return 0;
}
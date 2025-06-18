#include <iostream>
#include <thread>
#include <mutex>

std::mutex globalMutexOne;
std::mutex globalMutexTwo;

void fooTwo();

void fooOne() {
    std::lock_guard localGuard(globalMutexOne);
    std::cout << "Foo the first function." << '\n';
    // fooTwo();
}

void fooTwo() {
    std::lock_guard localGuard(globalMutexTwo);
    std::cout << "Foo the second function." << '\n';
    fooOne();
}

int main() {
    std::cout << "Hello" << '\n';

    std::thread myThreadOne(fooOne);
    std::thread myThreadTwo(fooTwo);
    myThreadOne.join();
    myThreadTwo.join();

    return 0;
}
#include <iostream>
#include <mutex>
#include <thread>

std::recursive_mutex globalMutex;

void fooInternal(unsigned int internalValue);

void foo() {
    std::cout << "Foo()" << '\n';
    for (unsigned int i = 0; i < 10; ++i) {
        fooInternal(i);
    }
}

void fooInternal(unsigned int internalValue) {
    std::lock_guard<std::recursive_mutex> lock(globalMutex);
    if (internalValue < 1) {
        std::cout << "We are at the bottom." << '\n';
        return;
    }
    std::cout << "The depth is " << internalValue << '\n';
    fooInternal(internalValue - 1);
}

int main() {
    std::cout << "Hello" << '\n';
    std::thread myThread(foo);
    myThread.join();
    return 0;
}
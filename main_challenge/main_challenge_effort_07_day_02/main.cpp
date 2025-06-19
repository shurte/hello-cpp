#include <iostream>
#include <thread>
#include <mutex>

std::mutex lowLevelMutex;
std::mutex highLevelMutex;
std::mutex otherMutex;

void foo() {
    std::cout << "Hello" << '\n';
}

int doLowLevelStuff() {
    std::cout << "Low level stuff..." << '\n';
    return 42;
}

int fooLowLevel() {
    std::lock_guard<std::mutex> lock(lowLevelMutex);
    return doLowLevelStuff();
}

void doHighLevelStuff(int someParameter) {
    std::cout << "High level stuff..." << '\n';
    std::cout << "Parameter: " << someParameter << '\n';
}

void fooHighLevel() {
    std::lock_guard<std::mutex> lock(highLevelMutex);
    doHighLevelStuff(fooLowLevel());
}

void doOtherStuff() {
    fooHighLevel();
    std::cout << "Other stuff..." << '\n';
}

void fooOther() {
    std::lock_guard<std::mutex> lock(otherMutex);
    doOtherStuff();
}

int main() {
    std::thread myThread(foo);
    myThread.join();

    std::thread lowLevelThread(fooLowLevel);
    lowLevelThread.join();

    std::thread highLevelThread(fooHighLevel);
    highLevelThread.join();

    std::thread otherThread(fooOther);
    otherThread.join();

    return 0;
}
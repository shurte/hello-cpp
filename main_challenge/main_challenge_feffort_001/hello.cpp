#include <hello.hpp>

#include <iostream>
#include <thread>

void printHello() {
    std::cout << "Hello" << '\n';
}

void printBye() {
    std::cout << "Bye" << '\n';
}

Hello::Hello() {
    std::thread helloThread(printHello);
    helloThread.join();
}

Hello::~Hello() {
    std::thread byeThread(printBye);
    byeThread.join();
}
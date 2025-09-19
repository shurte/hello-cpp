#include <hello.hpp>

#include <iostream>
#include <string>
#include <thread>

void print(const std::string& message) {
    std::cout << message.c_str() << '\n';
}

void printHello() {
    print("Hello");
}

void printBye() {
    print("Bye");
}

Hello::Hello() {
    std::thread helloThread(printHello);
    helloThread.join();
}

Hello::~Hello() {
    std::thread byeThread(printBye);
    byeThread.join();
}

void Hello::action() {
    std::thread actionThread(print, "action");
    actionThread.join();
}
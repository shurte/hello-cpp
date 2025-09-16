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

class Hello {
    public:
        Hello() {
            std::thread helloThread(printHello);
            helloThread.join();
        }

        ~Hello() {
            std::thread byeThread(printBye);
            byeThread.join();
        }
};

int main() {
    Hello hello;
    return 0;
}
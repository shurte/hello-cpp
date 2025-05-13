#include <iostream>
#include <thread>

class Hello {
    public: 
        Hello() {
            std::cout << "Hello!" << '\n';
        }

        ~Hello() {
            std::cout << "Bye!" << '\n';
        }

        void operator()() {
            std::cout << "Some activity." << '\n';
        }
};

int main() {
    Hello hello;
    std::thread myThread(std::forward<Hello>(hello));
    myThread.join();
    return 0;
}
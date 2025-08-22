#include <iostream>

class Hello {
    public:
        Hello() {
            std::cout << "Hello" << '\n';
        }

        ~Hello() {
            std::cout << "Bye" << '\n';
        }
};

int main() {
    Hello hello;
    return 0;
}
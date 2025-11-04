#include <iostream>

class Hello {
    public:
        Hello() {
            std::cout << "Hello" << '\n';
        };

        ~Hello() {
            std::cout << "Bye" << '\n';
        }
};

int main(int argc, char** argv) {
    Hello hello;
    return 0;
}
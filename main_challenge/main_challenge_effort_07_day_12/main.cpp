#include <iostream>
#include <thread>

void foo() {
    std::cout << "Foo()" << '\n';
}

int main(int argc, char** argv) {
    std::cout << "Hello" << '\n';
    std::cout << "Arguments: " << '\n';
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }
    std::cout << '\n';
    std::thread myThread(foo);
    myThread.join();
    return 0;
}
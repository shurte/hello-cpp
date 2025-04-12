#include <iostream>
#include <thread>

class my_thread_class {
public:
    my_thread_class() {
        std::cout << "Hello from constructor" << '\n';
    }

    my_thread_class(const my_thread_class& copy) {
        std::cout << "Hello from copy constructor." << '\n';
    }

    ~my_thread_class() {
        std::cout << "Bye from destructor" << '\n';
    }

    void operator()() {
        std::cout << "Hello from the operator." << '\n';
    }
};

int main(int argc, char** argv) {
    std::cout << "Hello from main." << '\n';

    my_thread_class my_var;
    std::thread my_thread(my_var);
    my_thread.detach();

    return 0;
}
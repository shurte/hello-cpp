#include <iostream>
#include <thread>
#include <exception>

struct func;
void do_something_in_the_current_thread();

struct func {
    func(int state) { }

    void operator()() {
        std::cout << "Operator in func." << '\n';
    }
};

void foo() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);

    try {
        do_something_in_the_current_thread();
    } catch (...) {
        my_thread.join();
        std::cout << "An exception caught." << '\n';
        throw;
    }

    my_thread.join();
}

int main(int argc, char** argv) {
    foo();

    return 0;
}

void do_something_in_the_current_thread() {
    for (int i; i < 100000; ++i) {
        if (i > 5000) {
            throw new std::exception();
        }
    }
}
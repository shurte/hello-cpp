#include <iostream>
#include <thread>

class my_thread_class {
public:
    my_thread_class() {
        std::cout << "Hello from my_thread_class constructor." << '\n';
    }

    my_thread_class(const my_thread_class& copy_thread) {
        std::cout << "Hello from my_thread_class copy constructor." << '\n';
    }

    void operator()() {
        std::cout << "Hello from the operator in the my_thread_class." << '\n';

        std::cout << "Is A an alpha? " << (std::isalpha('A') ? "true" : "false") << '\n';
        std::cout << "Is A a control? " << (std::iscntrl('A') ? "true" : "false") << '\n';
        std::cout << "Is A printable? " << (std::isprint('A') ? "true" : "false") << '\n';
        std::cout << "Is A a space? " << (std::isspace('A') ? "true" : "false") << '\n';
        std::cout << "Is A blank? " << (std::isblank('A') ? "true" : "false") << '\n';
        std::cout << "Is A grafical? " << (std::isgraph('A') ? "true" : "false") << '\n';
        std::cout << "Is A an alpha or a number? " << (std::isalnum('A') ? "true" : "false") << '\n';
        std::cout << "Is A in uppercase? " << (std::isupper('A') ? "true" : "false") << '\n';
        std::cout << "Is A in lowercase? " << (std::islower('A') ? "true" : "false") << '\n';
        std::cout << "Is A a digit? " << (std::isdigit('A') ? "true" : "false") << '\n';
        std::cout << "Is A an X digit? " << (std::isxdigit('A') ? "true" : "false") << '\n';
    }

    ~my_thread_class() {
        std::cout << "Bye from my_thread_class destructor." << '\n';
    }
};

int main(int argc, char** argv) {
    std::cout << "Hello from main." << '\n';
    my_thread_class my_var;
    std::thread my_thread(my_var);
    my_thread.join();
    return 0;
}
#include <iostream>
#include <thread>

class my_thread_class {
public: 
    my_thread_class() {
        std::cout << "Hello from my thread constructor." << '\n';
    }

    ~my_thread_class() {
        std::cout << "Bye from my thread destructor." << '\n';
    }

    void operator()() {
        std::cout << "Hello from my thread." << '\n';
        std::cout << "Is an A a letter : " << std::isalpha('A') << '\n'; 
    }
};

int main(int argc, char** argv) {
    std::cout << "Hello from main." << '\n';
    my_thread_class my_var;
    std::thread my_thread(my_var);
    my_thread.join();

    return 0;
}
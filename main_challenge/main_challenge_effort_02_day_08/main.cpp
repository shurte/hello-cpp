#include <iostream>
#include <thread>

class my_thread_class {
public:
    void operator()() {
        try {
            std::cout << "Hello from another thread." << '\n';
            throw std::runtime_error("Runtime error in another thread.");
        } catch (const std::runtime_error& error) {
            std::cout << error.what() << '\n';
            // throw;
        } catch (...) {
            std::cout << "Hello from catch in another thread." << '\n';
            // throw;
        }    
    }
};

int main(int argc, char** argv) {
    std::cout << "Hello from main." << '\n';
    try {
        my_thread_class my_thread_var;
        std::thread my_thread(my_thread_var);
        my_thread.detach();
        throw std::runtime_error("Runtime error in main.");
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << '\n';
        // throw;
    } catch (...) {
        std::cout << "Hello from catch in main. Unexpected error." << '\n';
        // throw;
    }

    return 0;
}
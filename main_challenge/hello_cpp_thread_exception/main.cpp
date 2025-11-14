#include <iostream>
#include <thread>
#include <exception>

class my_thread_class {
public:
    void operator()() {
        // try {
            std::cout << "Hello from the operator in thread." << '\n';
            throw new std::runtime_error("My exception.");
        // } catch (const std::runtime_error& exception) {
        //    std::cout << exception.what() << '\n';
        //    throw exception;
        //} catch (...) {
        //    std::cout << "Something unknown." << '\n';
        //}
    }
};

int main(int argc, char** argv) {
    try {
        std::cout << "Hello from main." << '\n';
        my_thread_class my_thread_var;
        std::thread my_thread(my_thread_var);
        my_thread.join();
    } catch (...) {
        std::cout << "Exception in the main." << '\n';
    }

    return 0;
}
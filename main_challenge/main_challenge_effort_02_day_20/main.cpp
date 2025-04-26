#include <iostream>
#include <string>
#include <thread>

void some_thread_function(int some_int, std::string some_str) {
    std::cout << "Integer parameter: " << some_int << '\n';
    std::cout << "String parameter: " << some_str << '\n';
}

int main() {
    std::cout << "Hello" << '\n';

    std::thread some_thread(some_thread_function, 34, "food");
    some_thread.join();

    return 0;
}
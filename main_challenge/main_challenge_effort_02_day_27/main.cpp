#include <iostream>
#include <thread>

void some_function() {
    std::cout << "some function." << '\n';
}

int main() {
    std::cout << "Hello" << '\n';
    std::thread my_thread(some_function);
    my_thread.join();

    return 0;
}
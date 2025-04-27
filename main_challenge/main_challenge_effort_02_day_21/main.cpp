#include <iostream>
#include <thread>

void some_function() {
    std::cout << "some function." << '\n';
}

void some_other_function() {
    std::cout << "some other function." << '\n';
}

int main() {
    std::cout << "Hello." << '\n';

    std::thread thread_one(some_function);
    std::thread thread_two = std::move(thread_one);
    thread_one = std::thread(some_other_function);
    std::thread thread_three;
    thread_three = std::move(thread_two);
    thread_one = std::move(thread_three);

    thread_one.join();
    thread_two.join();
    thread_three.join();

    return 0;
}
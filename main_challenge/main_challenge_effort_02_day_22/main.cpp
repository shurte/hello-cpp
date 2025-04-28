#include <iostream>
#include <thread>
#include <string>

constexpr char TRUE[] = "true";
constexpr char FALSE[] = "false";

void some_function() {
    std::cout << "some function." << '\n';
}

std::string print_bool(bool some_bool) {
    return (some_bool ? TRUE : FALSE);
}

int main(int argc, char** argv) {
    std::cout << "Arguments: " << '\n';

    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }

    std::cout << '\n';

    std::thread my_thread(some_function);
    std::cout << "Is my thread joinable? " << print_bool(my_thread.joinable()) << '\n';
    std::thread my_thread_two;
    std::cout << "Is my thread two joinable? " << print_bool(my_thread_two.joinable()) << '\n';
    my_thread_two = std::move(my_thread);
    std::cout << "Is my thread joinable? " << print_bool(my_thread.joinable()) << '\n';
    std::cout << "Is my thread two joinable? " << print_bool(my_thread_two.joinable()) << '\n';
    my_thread_two.join();
    std::cout << "Is my thread joinable? " << print_bool(my_thread.joinable()) << '\n';
    std::cout << "Is my thread two joinable? " << print_bool(my_thread_two.joinable()) << '\n';

    return 0;
}
#include <iostream>
#include <thread>

void some_function() {
    std::cout << "some function." << '\n';
    std::cout << "Id : " << std::this_thread::get_id() << '\n';
    std::cout << "Hash : " << std::hash<std::thread::id>()(std::this_thread::get_id()) << '\n'; 
}

int main(int argc, char** argv) {
    std::cout << "Hello." << '\n';
    std::cout << "Arguments: " << '\n';
    for (unsigned int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }
    std::cout << "Main thread id: " << std::this_thread::get_id() << '\n';

    for (unsigned int i = 0; i < 5; ++i) {
        std::thread my_thread(some_function);
        my_thread.join();
    }

    return 0;
}
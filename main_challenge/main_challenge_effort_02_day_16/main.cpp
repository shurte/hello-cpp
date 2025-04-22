#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Hello." << '\n';
    std::cout << "Arguments: " << '\n';

    for (size_t i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }

    return 0;
}
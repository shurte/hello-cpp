#include <iostream>

#include <nlohmann/json.hpp>

int main() {
    std::cout << "Hello" << '\n';
    std::cout << "JSON Library version: " << NLOHMANN_JSON_VERSION_MAJOR << '\n';
    return 0;
}
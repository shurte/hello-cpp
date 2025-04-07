#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv) {
    std::cout << "Hello" << '\n';

    std::regex const some_regular_expression{"\\d{4}"};
    std::cmatch matches;
    std::string some_str = "2342";
    
    bool is_matched = std::regex_match(some_str.c_str(), matches, some_regular_expression);
    std::cout << is_matched << '\n';

    if (is_matched) {
        std::cout << matches[0] << '\n';
    }

    return 0;
}
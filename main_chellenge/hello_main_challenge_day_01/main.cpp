#include <iostream>
#include <sstream>

struct bad_from_string : std::bad_cast {
    const char* what() const noexcept {
        return "bad cast from string";
    }
};

template<class T>
T from_string(const std::string& str) {
    std::istringstream str_stream(str);
    T t;
    if (!(str_stream >> t)) throw bad_from_string();
    return t;
}

int main(int argc, char** argv) {
    std::cout << "Hello" << '\n';

    double d = from_string<double>("1.999");
    std::cout << d << '\n';

    return 0;
}
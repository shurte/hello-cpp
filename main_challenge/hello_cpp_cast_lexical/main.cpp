#include <iostream>
#include <sstream>

struct bad_lexical_cast : std::bad_cast {
    const char* what() const noexcept {
        return "bad cast";
    }
};

template<typename Target, typename Source> 
Target lexical_cast(Source arg) {
    std::stringstream interpreter;
    Target result;

    if (!(interpreter << arg)
        || !(interpreter >> result)
        /*|| !(interpreter >> std::ws).eof()*/) {
            throw bad_lexical_cast();
        }

    return result;
}

int main(int argc, char** argv) {
    std::cout << "Hello" << '\n';

    double d = 1.999;
    int i = lexical_cast<int, double>(d);

    std::cout << i << '\n';

    return 0;
}
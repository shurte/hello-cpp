#include <iostream>
#include <string>

class my_class {
public:
    my_class(std::string str)
        : mStr(str) {
    }

    std::string& getStr() {
        return mStr;
    }
private:
    std::string& mStr;
};

int main(int argc, char** argv) {
    std::cout << "Hello." << '\n';
    my_class my_var("string");
    std::string& my_var_two = my_var.getStr();
    std::cout << my_var_two << '\n';
    my_var_two[0] = 'b';
    std::cout << my_var_two << '\n';
    std::string& my_var_three = my_var.getStr();
    std::cout << my_var_three << '\n';

    return 0;
}
#include <iostream>

class A {
    public:
        explicit A(int i) {
            _i = i;
        }

        int get_i() const {
            return _i;
        }

    private:
        int _i;
};

class B {
    public:
        B(int i) {
            _i = i;
        }

        int get_i() const {
            return _i;
        }

    private:
        int _i;

};

void foo(A a) {
    std::cout << "I : " << a.get_i() << '\n';
}

void foo(B a) {
    std::cout << "I : " << a.get_i() << '\n';
}

int main() {
    std::cout << "Hello." << '\n';
    A a_one(0);
    A a_two(1);
    A a_three{2};

    foo(a_one);
    foo(a_two);
    foo(a_three);

    foo(2);

    return 0;
}
#include <iostream>
#include <mutex>
#include <vector>

class X {
    public:
        X(unsigned number) { 
            for (unsigned i = 0; i < number; ++i) {
                _data.push_back(i);
            }
        }

        unsigned getSize() {
            return _data.size();
        }

        friend void swap(X& lhs, X& rhs);

    private:
        std::vector<int> _data;
        std::mutex _mutex;
};

void swap(X& lhs, X& rhs) {
    if (&lhs == &rhs) return;
    std::scoped_lock guard(lhs._mutex, rhs._mutex);
    std::swap(lhs._data, rhs._data);
}

int main() {
    std::cout << "Hello" << '\n';
    X x(1000);
    std::cout << "Size of x: " << x.getSize() << '\n';
    X y(2000);
    std::cout << "Size of y: " << y.getSize() << '\n';
    swap(x, y);
    std::cout << "Size of x: " << x.getSize() << '\n';
    std::cout << "Size of y: " << y.getSize() << '\n';
    return 0;
}
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
    std::lock(lhs._mutex, rhs._mutex);
    std::lock_guard<std::mutex> lockL(lhs._mutex, std::adopt_lock);
    std::lock_guard<std::mutex> lockR(rhs._mutex, std::adopt_lock);
    swap(lhs._data, rhs._data);
}

int main() {
    std::cout << "Hello." << '\n';

    X myXOne(1000);
    X myXTwo(2000);

    std::cout << "Size one : " << myXOne.getSize() << '\n';
    std::cout << "Size two : " << myXTwo.getSize() << '\n';

    swap(myXOne, myXTwo);

    std::cout << "Size one : " << myXOne.getSize() << '\n';
    std::cout << "Size two : " << myXTwo.getSize() << '\n';

    return 0;
}
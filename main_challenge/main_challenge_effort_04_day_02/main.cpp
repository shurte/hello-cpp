#include <iostream>
#include <mutex>
#include <vector>

class SomeBigObject {
    public:
        SomeBigObject() {
            _data = new std::vector<int>(1000);
            for (int i = 0; i < 1000; ++i) {
                (*_data)[i] = i;
            }
        }

        ~SomeBigObject() {
            if (_data) {
                delete _data;
            }
        }

        int getSize() {
            return _data->size();
        }

        friend void swap(SomeBigObject& lhs, SomeBigObject& rhs) {
            for (int i = 0; i < 1000; ++i) {
                std::swap((*(lhs._data))[i], (*(rhs._data))[i]);
            }
        }

    private:
        std::vector<int>* _data;
};



class X {
    public:
        X(const SomeBigObject& somethingBig)
            : _someDetail(somethingBig) {
            
        }

        friend void swap(X& lhs, X& rhs) {
            if (&lhs == &rhs) return;

            std::lock(lhs._mutex, rhs._mutex);
            std::lock_guard<std::mutex> lockA(lhs._mutex, std::adopt_lock);
            std::lock_guard<std::mutex> lockB(rhs._mutex, std::adopt_lock);
            swap(lhs._someDetail, rhs._someDetail);
        }

    private:
        SomeBigObject _someDetail;
        std::mutex _mutex;
};

int main() {
    std::cout << "Hello." << '\n';
    SomeBigObject someBig;
    std::cout << someBig.getSize() << '\n';
    SomeBigObject otherBig;
    std::cout << otherBig.getSize() << '\n';
    swap(someBig, otherBig);
    return 0;
}
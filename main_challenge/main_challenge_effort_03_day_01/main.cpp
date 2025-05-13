#include <iostream>
#include <thread>
#include <memory>

class IntData {
    public:
        IntData()
            : _i(0) {
            std::cout << "Hello Int." << '\n';
        }

        IntData(int i)
            : _i(i) {
            std::cout << "Hello Int." << '\n';
        }

        ~IntData() {
            std::cout << "Bye Int." << '\n';
        }

        int getData() {
            return _i;
        }

        void setData(int i) {
            _i = i;
        }

    private:
        int _i;
};

class MyData {
    public:
        MyData()
            : _i(new IntData()) {
        }

        std::shared_ptr<IntData> getData() {
            return _i;
        }

        void setData(IntData i) {
            *_i = i;
        }

    private:
        std::shared_ptr<IntData> _i;
};

class Hello {
    public: 
        Hello() {
            std::cout << "Hello!" << '\n';
        }

        ~Hello() {
            std::cout << "Bye!" << '\n';
        }

        void operator()() {
            std::cout << "Some activity." << '\n';
            MyData myData;
            std::cout << myData.getData()->getData() << '\n';
            myData.setData(IntData(10));
            std::cout << myData.getData()->getData() << '\n';
        }
};

int main() {
    Hello hello;
    std::thread myThread(std::forward<Hello>(hello));
    myThread.join();
    return 0;
}
#include <iostream>
#include <mutex>
#include <string>

class SomeData {
    public:
        void doSomething() {
            std::cout << "Doing something." << '\n';
        }

    private:
        int _a;
        std::string _b;        
};

class DataWrapper {
    public:
        template<typename Function>
        void processData(Function function) {
            std::lock_guard<std::mutex> lock(_mutex);
            function(_data);
        }

    private:
        SomeData _data;
        std::mutex _mutex;
};

SomeData* unprotected;

void maliciousFunction(SomeData& protectedData) {
    unprotected = &protectedData;
}

DataWrapper wrapper;

void foo() {
    wrapper.processData(maliciousFunction);
    unprotected->doSomething();
}

int main() {
    std::cout << "Hello." << '\n';
    foo();
    return 0;
}
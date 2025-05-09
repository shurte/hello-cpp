#include <iostream>
#include <mutex>
#include <string>
#include <thread>

constexpr char END = '\n';

class SomeData {
    public:
        SomeData() {
        }

        SomeData(const SomeData& other)
            :_mutex() {
        }

        void doSomething() {
            std::cout << "Some data is doing something." << END;
            std::scoped_lock<std::mutex> lock(_mutex);
            std::cout << "Integer sub-data: " << _a << END;
            std::cout << "String sub-data: " << _b << END;
        }
        
    private:
        int _a;
        std::string _b;
        std::mutex _mutex;
};

class MyThreadFunction {
    public:
        void operator()() {
            std::cout << "My thread function execution." << END;
            _data.doSomething();
        }

    private:
        SomeData _data;
};

int main() {
    std::cout << "Hello." << END;
    MyThreadFunction myFunction;
    std::thread myThread(myFunction);
    myThread.join();
    return 0;
}
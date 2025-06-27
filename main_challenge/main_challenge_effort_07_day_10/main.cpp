#include <iostream>
#include <shared_mutex>
#include <thread>

class MyResource {
    public:
        void updateResource(unsigned long size) {
            std::lock_guard<std::shared_mutex> lock(_sharedMutex);
            unsigned long sum = 0;
            for (unsigned long i = 0; i < size; ++i) {
                unsigned long subSum = 1;
                for (unsigned long j = 1; j < i; ++j) {
                    subSum *= j;
                }
                sum += subSum;
            }
            _sum = sum;
        }

        unsigned long getSum() {
            std::shared_lock<std::shared_mutex> lock(_sharedMutex);
            return _sum;
        }

    private:
        mutable std::shared_mutex _sharedMutex;
        unsigned long _sum = 0;
};

MyResource& getResource() {
    static MyResource resource;
    return resource;
}

void foo() {
    std::cout << "Foo()" << '\n';
    MyResource& resource = getResource();
    std::cout << "Sum : " << resource.getSum() << '\n';
    resource.updateResource(10000);
    std::cout << "Sum : " << resource.getSum() << '\n';
}

int main() {
    std::cout << "Hello." << '\n';
    std::thread myThread(foo);
    myThread.join();
    return 0;
}
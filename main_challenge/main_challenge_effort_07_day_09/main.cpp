#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

class MyResource {
    public:
        MyResource() {
            std::cout << "MyResource()" << '\n';
            updateResourceInternal(2);
        }

        void updateResource(unsigned int size) {
            std::cout << "updateResource() : " << size << '\n';
            updateResourceInternal(size);
        }

        unsigned int getSum() {
            std::cout << "getSum()" << '\n';
            std::shared_lock<std::shared_mutex> lock(_resourceMutex);
            return _sum;
        }
    
    private:
        void updateResourceInternal(unsigned int size) {
            std::cout << "updateResourceInternal() : " << size << '\n';
            std::lock_guard<std::shared_mutex> lock(_resourceMutex);
            unsigned int sum = 0;
            for (unsigned int i = 0; i < size; ++i) {
                unsigned int subSum = 1;
                for (unsigned int j = 1; j < i; ++j) {
                    subSum *= j;
                }
                sum += subSum;
            }
            _sum = sum;
        }

    private:
        mutable unsigned int _sum;
        mutable std::shared_mutex _resourceMutex;
};

MyResource myGlobalResource;

void foo() {
    std::cout << "Foo from another thread." << '\n';
    std::cout << "Sum : " << myGlobalResource.getSum() << '\n';
}
int main() {
    std::cout << "Hello." << '\n';
    foo();
    std::thread myThread(foo);
    myGlobalResource.updateResource(3);
    myThread.join();
    return 0;
}
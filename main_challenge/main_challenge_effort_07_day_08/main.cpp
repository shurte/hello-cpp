#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class SumResource {
    public:
        explicit SumResource(unsigned int size) {
            unsigned int sum = 0;
            for (unsigned int i = 1; i < size; ++i) {
                unsigned int subSum = 1;
                for (unsigned int j = 1; j < i; ++j) {
                    subSum *= j;
                }
                sum += subSum;
            }
            _sum = sum;
        }
        
        unsigned int getSum() const {
            return _sum;
        }

    private:
        unsigned int _sum = 0;
};

std::shared_ptr<SumResource> globalSumResource;

void initResource(unsigned int size) {
    globalSumResource.reset(new SumResource(size));
}

std::once_flag globalResourceInitFlag;

void foo() {
    std::call_once(globalResourceInitFlag, initResource, 10000);
    std::cout << "Sum : " << globalSumResource->getSum() << '\n';
}

int main() {
    std::cout << "Hello" << '\n';
    std::thread myThread(foo);
    myThread.join();
    return 0;
}
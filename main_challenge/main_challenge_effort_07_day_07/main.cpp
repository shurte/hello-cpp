#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

std::mutex globalMutex;
std::once_flag globalFlag;

class SumResource {
    public:
        SumResource() {
            unsigned int sum = 0;
            for (unsigned int i = 0; i < 10000; ++i) {
                unsigned int subSum = 1;
                for (unsigned int j = 1; j < i; ++j) {
                    subSum *= j;
                }
                sum += subSum;
            }
            _sum = sum;
        }

        unsigned long getSum() const {
            return _sum;
        }

    private:
        unsigned long _sum;
};

std::shared_ptr<SumResource> globalResource;

void initResource() {
    {
        std::unique_lock cmdLock(globalMutex);
        std::cout << "Resource initialization." << '\n';
    }
    globalResource.reset(new SumResource); 
}

void foo() {
    std::call_once(globalFlag, initResource);
    {
        std::unique_lock cmdLock(globalMutex);
        std::cout << "Sum : " << globalResource->getSum() << '\n';
    }
}

std::chrono::system_clock::time_point getTimePoint() {
    return std::chrono::high_resolution_clock::now();
}

int main() {
    std::cout << "Hello" << '\n';
    std::chrono::time_point start = getTimePoint();
    std::thread myThread(foo);
    myThread.join();
    std::chrono::time_point end = getTimePoint();
    std::chrono::duration executionDuration = end - start;
    std::chrono::duration<unsigned long, std::milli> executionDurationCasted = std::chrono::duration_cast<std::chrono::milliseconds> (executionDuration);
    std::cout << "Execution time : " << executionDuration.count() << '\n';
    std::cout << "Execution time casted : " << executionDurationCasted.count() << '\n';

    start = getTimePoint();
    std::thread oneMoreThread(foo);
    oneMoreThread.join();
    end = getTimePoint();
    executionDurationCasted = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    std::cout << "One more execution time : " << executionDurationCasted.count() << '\n';

    return 0;
}
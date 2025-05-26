#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class X {
    public:
        X(unsigned number) {
            for (unsigned i = 0; i < number; ++i) {
                _data.push_back(i);
            }
        }

        unsigned getSize() const {
            std::lock_guard<std::mutex> lock(_mutex);
            return _data.size();
        }

        friend void swap(X& lhs, X& rhs) {
            if (&lhs == &rhs) return;
            std::scoped_lock lock(lhs._mutex, rhs._mutex);
            swap(lhs._data, rhs._data);
        }

    private:
        std::vector<int> _data;
        mutable std::mutex _mutex;
};

class HierarchicalJob {
    public:
        int doLowLevelStuff() {
            return 42;
        }

        int lowLevelFunction() {
            std::lock_guard<std::mutex> lock(_lowLevelMutex);
            return doLowLevelStuff();
        }

        void doHighLevelStuff(int param) {
            for (unsigned i = 0; i < param; ++i) {
                {
                    std::lock_guard lock(_lowLevelMutex);
                    std::cout << std::this_thread::get_id() << " : " << i * (i + 1) << '\n';
                }
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(500ms);
            }

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(500ms);
        }
    
        void highLevelFunction() {
            std::lock_guard<std::mutex> lock(_highLevelMutex);
            doHighLevelStuff(doLowLevelStuff());
        }

        void doOtherStuff() {
            for (unsigned i = 0; i < 100; ++i) {
                {
                    std::lock_guard lock(_lowLevelMutex);
                    std::cout << std::this_thread::get_id() << " : " << i << '\n';
                }
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(100ms);
            }
        }

        void otherStuffFunction() {
            highLevelFunction();
            doOtherStuff();
        }

        void threadA() {
            highLevelFunction();
        }

        void threadB() {
            // std::lock_guard<std::mutex> lock(_otherMutex);
            otherStuffFunction();
        }

    private:
        std::mutex _lowLevelMutex;
        std::mutex _highLevelMutex;
        std::mutex _otherMutex;
};

void startThreadOne(HierarchicalJob* job) {
    job->threadA();
}

void startThreadTwo(HierarchicalJob* job) {
    job->threadB();
}

int main() {
    std::cout << "Hello" << '\n';

    HierarchicalJob job;

    std::thread threadOne(startThreadOne, &job);
    std::thread threadTwo(startThreadTwo, &job);

    threadOne.join();
    threadTwo.join();

    return 0;
}
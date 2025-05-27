#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

class HierarchicalMutex {
    public:
        explicit HierarchicalMutex(unsigned long value)
            : _hierarchyValue(value)
            , _previousHierarchyValue(0) 
            { }

        void lock() {
            checkForHierarchyViolation();
            _internalMutex.lock();
            updateHierarchyValue();
        }

        void unlock() {
            if (_thisThreadHierarchyValue != _hierarchyValue) {
                throw std::logic_error("Mutex hierarchy violated.");
            }

            _thisThreadHierarchyValue = _previousHierarchyValue;
            _internalMutex.unlock();
        }

        bool tryLock() {
            checkForHierarchyViolation();

            if (!_internalMutex.try_lock()) {
                return false;
            }
            
            updateHierarchyValue();
            return true;
        }

    private:
        void checkForHierarchyViolation() {
            if (_thisThreadHierarchyValue <= _hierarchyValue) {
                throw std::logic_error("Mutex hierarchy violated.");
            }
        }

        void updateHierarchyValue() {
            _previousHierarchyValue = _thisThreadHierarchyValue;
            _thisThreadHierarchyValue = _hierarchyValue;
        }

    private:
        std::mutex _internalMutex;
        const unsigned long _hierarchyValue;
        unsigned long _previousHierarchyValue;

        static thread_local unsigned long _thisThreadHierarchyValue;
};

thread_local unsigned long HierarchicalMutex::_thisThreadHierarchyValue(ULONG_MAX);

HierarchicalMutex highLevelMutex(10000);
HierarchicalMutex lowLevelMutex(5000);
HierarchicalMutex otherMutex(6000);

int doLowLevelStuff() {
    return 42;
}

int lowLevelFunction() {
    std::lock_guard<HierarchicalMutex> lock(lowLevelMutex);
    return doLowLevelStuff();
}

void doHighLevelStuff(int someParameter) {
    for (unsigned i = 0; i < someParameter; ++i) {
        std::cout << "Thread: " << std::this_thread::get_id() << '\n';
        std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(100)));
    }
}

void highLevelFunction() {
    std::lock_guard<HierarchicalMutex> lock(highLevelMutex);
    doHighLevelStuff(lowLevelFunction());
}

void threadA() {
    highLevelFunction();
}

void doOtherStuff() {
    for (unsigned i = 0; i < 30; ++i) {
        std::cout << "Thread: " << std::this_thread::get_id() << '\n';
        std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(100)));
    }
}

void otherStuffFunction() {
    highLevelFunction();
    doOtherStuff();
}

void threadB() {
    std::lock_guard<HierarchicalMutex> lock(otherMutex);
    otherStuffFunction();
}

int main() {
    std::cout << "Hello" << '\n';
    std::thread threadOne(threadA);
    std::thread threadTwo(threadB);

    threadOne.join();
    threadTwo.join();

    return 0;
}
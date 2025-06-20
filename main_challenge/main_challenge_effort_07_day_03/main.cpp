#include <iostream>
#include <mutex>
#include <thread>

class HierarchicalMutex {
    public:
        explicit HierarchicalMutex(unsigned long value)
            : _hierarchyValue(value) 
            , _previousHierarchyValue(0) {
        }

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
        std::mutex _internalMutex;
        const unsigned long _hierarchyValue;
        unsigned long _previousHierarchyValue;
        static thread_local unsigned long _thisThreadHierarchyValue;

        void checkForHierarchyViolation() {
            if (_thisThreadHierarchyValue <= _hierarchyValue) {
                throw std::logic_error("Mutex hierarchy violated.");
            }
        }

        void updateHierarchyValue() {
            _previousHierarchyValue = _thisThreadHierarchyValue;
            _thisThreadHierarchyValue = _hierarchyValue;
        }
};

thread_local unsigned long HierarchicalMutex::_thisThreadHierarchyValue(ULONG_MAX);

HierarchicalMutex globalMutex(100);

void fooHello() {
    std::lock_guard<HierarchicalMutex> lock(globalMutex);
    std::cout << "Hello" << '\n';
}

int main() {
    std::thread helloThread(fooHello);
    helloThread.join();
    return 0;
}
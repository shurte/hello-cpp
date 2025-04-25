#include <iostream>
#include <thread>

class thread_guard {
    public: 
        explicit thread_guard(std::thread& thread)
            : _thread(thread) {
        }

        thread_guard(const thread_guard& thread) = delete;
        thread_guard& operator=(const thread_guard& thread) = delete;

        ~thread_guard() {
            if (_thread.joinable()) {
                _thread.join();
            }
        }

    private:
        std::thread& _thread;
};

void do_something(int i) {
    std::cout << "I = " << i << '\n';
}

struct func {
    func(int& i)
        : _i(i) {
    }

    void operator()() {
        for (unsigned j = 0; j < 10; ++j) {
            do_something(_i);
        }
    }

    int& _i;
};

void foo() {
    std::cout << "Start of the foo function." << '\n';
    int some_lokal_var = 10;
    func my_func(some_lokal_var);
    std::thread thread(my_func);
    thread_guard my_guard(thread);
    std::cout << "End of the foo function." << '\n';
}

int main() {
    std::cout << "Hello." << '\n';
    foo();
    return 0;
}
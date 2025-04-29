#include <iostream>
#include <thread>

void some_function() {
    std::cout << "some function." << '\n';
}

class scoped_thread {
    public:
        explicit scoped_thread(std::thread thread) 
            : _thread(std::move(thread)) {

            if (!_thread.joinable()) {
                throw std::logic_error("No thread.");
            }
        }

        ~scoped_thread() {
            _thread.join();
        }
    private:
        std::thread _thread;
};

int main() {
    std::cout << "Hello" << '\n';
    std::thread my_thread(some_function);
    my_thread.detach();

    scoped_thread my_scoped{std::thread(some_function)};

    return 0;
}
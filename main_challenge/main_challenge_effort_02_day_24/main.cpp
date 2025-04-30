#include <iostream>
#include <thread>

class joining_thread {
    public:
        joining_thread() noexcept = default;

        template<typename Callable, typename ... Args>
        explicit joining_thread(Callable&& func, Args&& ... args)
            : _thread(std::forward<Callable>(func), std::forward<Args>(args)...) {

        }

        explicit joining_thread(std::thread thread) noexcept
            : _thread(std::move(thread)) {

        }

        joining_thread(joining_thread&& other) noexcept
            : _thread(std::move(other._thread)) {

        }

        joining_thread& operator=(joining_thread&& other) noexcept {
            if (joinable()) {
                join();
            }

            _thread = std::move(other._thread);
            return *this;
        }

        ~joining_thread() {
            if (joinable()) {
                join();
            }
        }

        void swap(joining_thread& other) noexcept {
            _thread.swap(other._thread);
        }

        std::thread::id get_id() const noexcept {
            return _thread.get_id();
        }

        bool joinable() const noexcept {
            return _thread.joinable();
        }

        void join() {
            _thread.join();
        }

        void detach() {
            _thread.detach();
        }

        std::thread& as_thread() noexcept {
            return _thread;
        }

        const std::thread& as_thread() const noexcept {
            return _thread;
        }

    private:
        std::thread _thread;
};

void some_function() {
    std::cout << "some function." << '\n';
}

int main() {
    std::cout << "Hello." << '\n';
    joining_thread j_thread(some_function);
    return 0;
}
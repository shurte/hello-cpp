#include <iostream>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception {
    const char* what() const noexcept {
        return "empty stack";
    }
};

template<typename T>
class threadsafe_stack {
    public:
        threadsafe_stack() { }
        threadsafe_stack(const threadsafe_stack&);
        threadsafe_stack& operator=(const threadsafe_stack&) = delete;
        void push(T new_value);
        std::shared_ptr<T> pop();
        void pop(T& value);
        bool empty() const;
    private:
        std::stack<T> _data;
        mutable std::mutex _mutex;
};

template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other) {
    std::lock_guard<std::mutex> lock(_mutex);
    _data = other._data;
}

template<typename T>
void threadsafe_stack<T>::push(T new_value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _data.push(std::move(new_value));
}

template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_data.empty()) throw empty_stack();
    std::shared_ptr<T> const res(std::make_shared<T>(_data.top()));
    _data.pop();
    return res;
}

template<typename T>
void threadsafe_stack<T>::pop(T& value) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_data.empty()) throw empty_stack();
    value = _data.top();
    _data.pop();
}

template<typename T>
bool threadsafe_stack<T>::empty() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _data.empty();
}

int main() {
    std::cout << "Hello" << '\n';
    threadsafe_stack<int> my_stack;
    my_stack.push(1);
    std::cout << my_stack.empty() << '\n';
    std::cout << *(my_stack.pop()) << '\n';
    return 0;
}
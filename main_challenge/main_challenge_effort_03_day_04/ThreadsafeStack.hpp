#pragma once

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct EmptyStack : std::exception {
    const char* what() const noexcept {
        return "Empty stack exception.";
    }
};

template<typename T>
class ThreadsafeStack {
    public:
        ThreadsafeStack();
        ThreadsafeStack(const ThreadsafeStack&);
        ThreadsafeStack& operator=(const ThreadsafeStack&) = delete;
        void push(T newValue);
        std::shared_ptr<T> pop();
        void pop(T& value);
        bool empty() const;
    private:
        std::stack<T> _data;
        mutable std::mutex _mutex;
};

template<typename T>
ThreadsafeStack<T>::ThreadsafeStack() { }

template<typename T>
ThreadsafeStack<T>::ThreadsafeStack(const ThreadsafeStack& other) {
    std::lock_guard<std::mutex> lock(other._mutex);
    _data = other._data;
}

template<typename T>
void ThreadsafeStack<T>::push(T newValue) {
    std::lock_guard<std::mutex> lock(_mutex);
    _data.push(std::move(newValue));
}

template<typename T>
std::shared_ptr<T> ThreadsafeStack<T>::pop() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_data.empty()) throw EmptyStack();
    const std::shared_ptr<T> result(std::make_shared<T>(_data.top()));
    _data.pop();
    return result;
}

template<typename T>
void ThreadsafeStack<T>::pop(T& value) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_data.empty()) throw EmptyStack();
    value = _data.top();
    _data.pop();
}

template<typename T>
bool ThreadsafeStack<T>::empty() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _data.empty();
}
#pragma once

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct EmptyStack : std::exception {
    const char* what() const throw() {
        return "Empty stack exception.";
    }
};

template<typename T>
class ThreadsafeStack {
    public:
        ThreadsafeStack() { }
        
        ThreadsafeStack(const ThreadsafeStack& other) {
            std::lock_guard<std::mutex> lock(other._mutex);
            _data = other._data;
        }

        ThreadsafeStack& operator=(const ThreadsafeStack&) = delete;

        void push(T newValue) {
            std::lock_guard<std::mutex> lock(_mutex);
            _data.push(std::move(newValue));
        }

        std::shared_ptr<T> pop() {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_data.empty()) throw EmptyStack();
            const std::shared_ptr<T> result(std::make_shared<T>(_data.top()));
            _data.pop();
            return result;
        }

        void pop(T& value) {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_data.empty()) throw EmptyStack();
            value = _data.top();
            _data.pop();
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(_mutex);
            return _data.empty();
        }

    private:
        std::stack<T> _data;
        mutable std::mutex _mutex;
};
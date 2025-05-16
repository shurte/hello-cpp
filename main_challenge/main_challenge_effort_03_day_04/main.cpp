#include "ThreadsafeStack.hpp"

#include <iostream>

int main() {
    std::cout << "Hello" << '\n';
    ThreadsafeStack<int> myStack;
    myStack.push(10);
    return 0;
}
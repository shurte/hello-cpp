#include "ThreadsafeStack.hpp"

#include <iostream>

int main() {
    std::cout << "Hello." << '\n';
    ThreadsafeStack<int> myStack;
    myStack.push(10);
    std::cout << myStack.empty() << '\n';
    return 0;
}
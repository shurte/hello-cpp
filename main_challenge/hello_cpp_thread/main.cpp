#include <iostream>
#include <thread>

void foo_thread() {
    std::cout << "Hello from thread." << '\n';
}

class my_int {
public:
    int i = 0;
};

class my_thread_class {
public:
    void operator()() {
        std::cout << "Hello from thread class." << '\n';
        m_i->i = 10;
        std::cout << get_i() << '\n';
    }

    int get_i() {
        return m_i->i;
    }

private:
    my_int* m_i;
};

int main() {
    std::thread my_thread(foo_thread);
    my_thread.join();

    my_thread_class my_thread_object;
    std::thread my_thread_from_class(my_thread_object);
    my_thread_from_class.join();

    std::cout << my_thread_object.get_i() << '\n';

    return 0;
}
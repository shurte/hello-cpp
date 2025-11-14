#include <iostream>
#include <thread>

struct my_data_struct {
    int m_i;
};

struct my_thread_struct {
    my_thread_struct(my_data_struct my_data) { 
        m_my_data = my_data;
    }

    void operator()() {
        std::cout << "Hello from the my_thread_struct operator()." << '\n';
        std::cout << "My data : " << m_my_data.m_i << '\n';
    }

private:
    my_data_struct m_my_data;
};

void sub_foo() {
    my_data_struct my_data;
    my_thread_struct my_struct_var(my_data);
    std::thread my_thread(my_struct_var);
    my_thread.detach();
}

int main(int argc, char** argv) {
    std::cout << "Hello from the main." << '\n';
    sub_foo();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}
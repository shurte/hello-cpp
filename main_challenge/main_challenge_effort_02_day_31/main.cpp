#include <iostream>
#include <mutex>
#include <list>

class my_list {
    public:
        void add_to_list(int value) {
            std::lock_guard<std::mutex> local_guard(_mutex);
            _list.push_back(value);
        }

        unsigned int get_size() {
            return _list.size();
        }
    private:
        std::list<int> _list;
        std::mutex _mutex;
};

int main() {
    std::cout << "Hello." << '\n';

    std::mutex my_mutex;
    my_mutex.lock();
    my_mutex.unlock();

    std::lock_guard<std::mutex> my_guard(my_mutex);

    my_list some_list;
    std::cout << "Size of list: " << some_list.get_size() << '\n';
    some_list.add_to_list(2);
    std::cout << "Size of list: " << some_list.get_size() << '\n';

    return 0;
}
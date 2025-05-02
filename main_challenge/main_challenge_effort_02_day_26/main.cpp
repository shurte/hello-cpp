#include <iostream>
#include <numeric>

template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

int main() {
    std::cout << "Hello." << '\n';
    int some_int_arr[] = { 2, 5, 23, 7 };
    int result = 0;
    accumulate_block<int*, int> my_block;
    my_block(&(some_int_arr[0]), &(some_int_arr[3]), result);
    std::cout << "Result: " << result << '\n';

    return 0;
}
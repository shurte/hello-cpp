#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    
    std::cout << "Distance: " << length << '\n';
    
    if (!length) return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    std::cout << "Number of threads: " << num_threads << '\n';

    unsigned long const block_size = length / num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;

    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }

    return init;
}

int main(int argc, char** argv) {
    std::cout << "Arguments: " << '\n';
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }
    std::cout << '\n';
    std::cout << "Number of threads: " << std::thread::hardware_concurrency() << '\n';

    int some_array[] = { 3, 5, 67, 2, 1, 7};
    int some_result = parallel_accumulate(&some_array[0], &some_array[5], 0);

    return 0;
}
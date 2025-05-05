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
    const unsigned long length = std::distance(first, last);
    if (!length) return init;

    const unsigned long min_per_thread = 25;
    const unsigned long max_threads = (length + min_per_thread - 1) / min_per_thread;
    const unsigned long hardware_threads = std::thread::hardware_concurrency();
    const unsigned long num_threads = std::min(max_threads, hardware_threads != 0 ? hardware_threads : 2);
    const unsigned long block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;

    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));

        block_start = block_end;
    }

    accumulate_block<Iterator, T>()(block_start, last, std::ref(results[num_threads - 1]));

    for (auto& entry : threads) {
        entry.join();
    }

    return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char** argv) {
    std::cout << "Hello." << '\n';
    std::cout << "Arguments: " << '\n';
    for (unsigned int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }

    std::vector<int> some_data;

    for (unsigned int i = 0; i < 2000; ++i) {
        some_data.push_back(i);
    }

    int result = 1;
    accumulate_block<std::vector<int>::iterator, int> my_block;
    my_block(some_data.begin(), some_data.end(), result);
    std::cout << "Result: " << result << '\n';

    std::cout << "Result: " << parallel_accumulate<std::vector<int>::iterator, int>(some_data.begin(), some_data.end(), 0) << '\n';

    return 0;
}
#include <iostream>
#include <thread>

void fooLong() {
    int sum = 0;

    for (size_t i = 0; i < 10000; ++i) {
        int subSum = 1;
        for (size_t j = 1; j < i; ++j) {
            subSum *= j;
        }
        sum += subSum;
    }

    std::cout << "Sum : " << sum << '\n';
}

int64_t getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int main() {
    std::cout << "Hello" << '\n';

    auto startTimeMs = getCurrentTime();
    std::cout << "Start time: " << startTimeMs << '\n';

    std::thread myThread(fooLong);
    myThread.join();

    auto endTimeMs = getCurrentTime();
    std::cout << "End time : " << endTimeMs << '\n';

    auto duration = endTimeMs - startTimeMs;
    std::cout << "Duration : " << duration << '\n';

    return 0;
}
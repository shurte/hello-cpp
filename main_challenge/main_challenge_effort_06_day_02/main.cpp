#include <iostream>
#include <thread>

int64_t getCurrentTime() {
    auto startTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(startTime).count();
}

void fooLong() {
    int sum = 0;

    for (int i = 0; i < 10000; ++i) {
        int subSum = 1;

        for (int j = 1; j < i; ++j) {
            subSum *= j;
        }

        sum += subSum;
    }

    std::cout << "Sum : " << sum << '\n';
}

int main() {
    std::cout << "Hello" << '\n';

    auto startTimeMs = getCurrentTime();
    std::cout << "Start time in milliseconds: " << startTimeMs << '\n';

    std::thread myThread(fooLong);
    myThread.join();

    auto endTimeMs = getCurrentTime();
    std::cout << "End time in milliseconds: " << endTimeMs << '\n';

    auto duration = endTimeMs - startTimeMs;
    std::cout << "Duration: " << duration << '\n';

    return 0;
}
#include <chrono>
#include <iostream>

void foo() {
    std::chrono::time_point startTimeNow = std::chrono::high_resolution_clock::now();
    // std::cout << "Start time now : " << startTimeNow << '\n'; ERROR
    std::chrono::duration startTimeDuration = startTimeNow.time_since_epoch();
    std::chrono::system_clock::rep startTimeDurationRepresentation = startTimeDuration.count();
    std::cout << "Start time duration : " << startTimeDurationRepresentation << '\n';
    
    {
        std::cout << "Double converion : " << '\n';
        std::chrono::duration<double, std::milli> startTimeDurationCastedDoubleMilli = std::chrono::duration_cast<std::chrono::milliseconds> (startTimeDuration);
        std::cout << "Start tume duration casted to double milli : " << startTimeDurationCastedDoubleMilli.count() << '\n';
        std::chrono::duration<double, std::micro> startTimeDurationCastedDoubleMicro = std::chrono::duration_cast<std::chrono::milliseconds> (startTimeDuration);
        std::cout << "Start tume duration casted to double micro : " << startTimeDurationCastedDoubleMicro.count() << '\n';
        std::chrono::duration<double, std::milli> startTimeDurationCastedDoubleMilliMicro = std::chrono::duration_cast<std::chrono::microseconds> (startTimeDuration);
        std::cout << "Start tume duration casted to double milli from micro: " << startTimeDurationCastedDoubleMilliMicro.count() << '\n';
        std::chrono::duration<double, std::micro> startTimeDurationCastedDoubleMicroMicro = std::chrono::duration_cast<std::chrono::microseconds> (startTimeDuration);
        std::cout << "Start tume duration casted to double micro from micro: " << startTimeDurationCastedDoubleMicroMicro.count() << '\n';
    }

    {
        std::cout << '\n' << "Long convertion : " << '\n';
        std::chrono::duration<unsigned long, std::milli> startTimeDurationCastedDoubleMilli = std::chrono::duration_cast<std::chrono::milliseconds> (startTimeDuration);
        std::cout << "Start tume duration casted to unsigned long milli : " << startTimeDurationCastedDoubleMilli.count() << '\n';
        std::chrono::duration<unsigned long, std::micro> startTimeDurationCastedDoubleMicro = std::chrono::duration_cast<std::chrono::milliseconds> (startTimeDuration);
        std::cout << "Start tume duration casted to unsigned long micro : " << startTimeDurationCastedDoubleMicro.count() << '\n';
        // std::chrono::duration<long, std::milli> startTimeDurationCastedDoubleMilliMicro = std::chrono::duration_cast<std::chrono::microseconds> (startTimeDuration); ERROR
        // std::cout << "Start tume duration casted to unsigned long milli from micro: " << startTimeDurationCastedDoubleMilliMicro.count() << '\n';
        std::chrono::duration<unsigned long, std::micro> startTimeDurationCastedDoubleMicroMicro = std::chrono::duration_cast<std::chrono::microseconds> (startTimeDuration);
        std::cout << "Start tume duration casted to unsigned long micro from micro: " << startTimeDurationCastedDoubleMicroMicro.count() << '\n';
    }

    std::chrono::time_point endTimeNow = std::chrono::high_resolution_clock::now();
    // std::cout << "End time now : " << endTimeNow << '\n'; ERROR
    std::chrono::duration endTimeDuration = endTimeNow.time_since_epoch();
    std::chrono::system_clock::rep endTimeDurationRepresentation = endTimeDuration.count();
    std::cout << "End time duration : " << endTimeDurationRepresentation << '\n';
}

int main() {
    std::cout << "Hello" << '\n';
    foo();
    return 0;
}
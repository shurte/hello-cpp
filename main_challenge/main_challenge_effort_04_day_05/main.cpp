#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

struct Employee {
    Employee(std::string id) : _id(id) { }
    std::string _id;
    std::vector<std::string> _lunchPartners;
    std::mutex _mutex;
    std::string output() const{
        std::string result = "Employee " + _id + " has lunch partners: ";
        for (auto n{_lunchPartners.size()}; const auto& partner : _lunchPartners) {
            result += partner + (--n ? ", " : "");
        }
        return result;
    }
};

void sendMail(Employee&, Employee&) {
    std::this_thread::sleep_for(std::chrono::milliseconds(696));
}

void assignLunchPartner(Employee& leftEmployee, Employee& rightEmployee) {
    static std::mutex ioMutex;
    {
        std::lock_guard<std::mutex> guard(ioMutex);
        std::cout << leftEmployee._id << " and " << rightEmployee._id << " are waiting for locks" << '\n';  
    }

    {
        std::lock(leftEmployee._mutex, rightEmployee._mutex);
        std::lock_guard<std::mutex> leftGuard(leftEmployee._mutex, std::adopt_lock);
        std::lock_guard<std::mutex> rightGuard(rightEmployee._mutex, std::adopt_lock);

        {
            std::lock_guard<std::mutex> guard(ioMutex);
            std::cout << leftEmployee._id << " and " << rightEmployee._id << " got locks" << '\n';
        }

        leftEmployee._lunchPartners.push_back(rightEmployee._id);
        rightEmployee._lunchPartners.push_back(leftEmployee._id);
    }

    sendMail(leftEmployee, rightEmployee);
    sendMail(rightEmployee, leftEmployee);
}

int main() {
    std::cout << "Hello" << '\n';

    Employee alice("Alice"), bob("Bob"), christina("Christina"), dave("Dave");

    std::vector<std::thread> threads;
    threads.emplace_back(assignLunchPartner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assignLunchPartner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assignLunchPartner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assignLunchPartner, std::ref(dave), std::ref(bob));
    
    for (auto& thread : threads) thread.join();

    std::cout << alice.output() << '\n'
        << bob.output() << '\n'
        << christina.output() << '\n'
        << dave.output() << '\n';

    return 0;
}
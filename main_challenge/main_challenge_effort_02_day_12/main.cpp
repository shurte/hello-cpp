#include <iostream>
#include <thread>
#include <string>

const char DEFAULT_CODE = 10;

class my_thread_class {
    public:
        my_thread_class(const std::string& data)
            : mDataToEncrypt(new std::string(data))
            , mEntcryptedResult(new std::string()) {
            std::cout << "my_thread_class::constructor" << '\n';
        }

        my_thread_class(const my_thread_class& my_copy) {
            std::cout << "my_thread_class::copy_constructor" << '\n';
            mDataToEncrypt = my_copy.mDataToEncrypt;
            mEntcryptedResult = my_copy.mEntcryptedResult;
        }

        ~my_thread_class() {
            std::cout << "my_thread_class::destructor" << '\n';
        }

        void operator()() {
            std::cout << "my_thread_class()" << '\n';
            std::cout << "data to encrypt: " << *mDataToEncrypt << '\n';
            mEntcryptedResult->append(encrypt());
        }

        std::string getEncrypted() const {
            return *mEntcryptedResult;
        }

    private:
        std::string* mDataToEncrypt;
        std::string* mEntcryptedResult;

        std::string encrypt() {
            std::string encryptedResult;
            for (int i = 0; i < mDataToEncrypt->length(); ++i) {
                char currentSymbol = mDataToEncrypt->at(i);
                char encrypted = (char) (currentSymbol + DEFAULT_CODE);
                if (std::isupper(currentSymbol) && encrypted > 'Z') {
                    encrypted = (char) ('A' + (encrypted - 'Z' - 1));
                } else if (std::islower(currentSymbol) && encrypted > 'z') {
                    encrypted = (char) ('a' + (encrypted - 'z' - 1));
                }
                encryptedResult += encrypted;
            }
            return encryptedResult;
        }
};

int main(int argc, char** argv) {
    std::cout << "Hello from main." << '\n';
    my_thread_class my_var("abcxyzABCXYZ");
    std::thread my_thread(my_var);
    my_thread.join();
    std::string result = my_var.getEncrypted();
    std::cout << "Encrypted: " << result << '\n';

    char some = 'a';
    char other = some + 10;
    std::cout << other << '\n';
    std::string str;
    std::cout << (str + other) << '\n';
    return 0;
}
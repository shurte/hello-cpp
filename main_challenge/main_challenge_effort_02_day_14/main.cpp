#include <iostream>
#include <thread>
#include <string>

class my_thread_class {
    public:
        my_thread_class(int code, const std::string& toEncrypt, std::string& encrypted)
            : mCode(code)
            , mToEncrypt(toEncrypt)
            , mEncrypted(encrypted) {
        }

        void operator()() {
            mEncrypted.clear();
            mEncrypted.append(mToEncrypt);
        }

    private:
        int mCode;
        const std::string& mToEncrypt;
        std::string& mEncrypted;
};

int main(int argc, char** argv) {
    std::cout << "Hello." << '\n';

    std::string to_encrypt("az");
    std::string encrypted;
    my_thread_class my_var(10, to_encrypt, encrypted);
    std::thread my_thread(my_var);
    my_thread.join();
    std::cout << "Encrypted: " << encrypted << '\n';

    return 0;
}
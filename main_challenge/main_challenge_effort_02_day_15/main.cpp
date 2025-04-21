#include <iostream>

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char encrypt(char toEncrypt, int code) {
    if (!isLetter(toEncrypt)) {
        return toEncrypt;
    }

    char encrypted = toEncrypt;

    if (toEncrypt >= 'A' && toEncrypt <= 'Z') {
        int realCode = code % ('Z' - 'A');
        encrypted = toEncrypt + realCode;

        if (encrypted > 'Z') {
            encrypted = 'A' - 1 + (encrypted - 'Z');
        } else if (encrypted < 'A') {
            encrypted = 'Z' + 1 - ('A' - encrypted);
        }
    } else {
        int realCode = code % ('z' - 'a');
        encrypted = toEncrypt + realCode;

        if (encrypted > 'z') {
            encrypted = 'a' - 1 + (encrypted - 'z');
        } else if (encrypted < 'a') {
            encrypted = 'z' + 1 - ('a' - encrypted);
        }
    }

    return encrypted;
}

int main(int argc, char** argv) {
    std::cout << "Hello." << '\n';

    int code = 1;

    for (char c = 'a'; c <= 'z'; ++c) {
        std::cout << c << " encrypted to " << encrypt(c, code) << '\n';
    }

    code = -1;

    for (char c = 'A'; c <= 'Z'; ++c) {
        std::cout << c << " encrypted to " << encrypt(c, code) << '\n';
    }

    return 0;
}
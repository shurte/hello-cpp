#include <iostream>
#include <thread>

const char first_capital = 'A';
const char last_capital = 'Z';
const char first_small = 'a';
const char last_small = 'z';

bool is_letter(char symbol) {

    if ((symbol >= first_capital && symbol <= last_capital) || (symbol >= first_small && symbol <= last_small)) {
        return true;
    }

    return false;
}

char encrypt_letter(char to_encrypt, int code) {
    if (!is_letter(to_encrypt)) return to_encrypt;

    code = code % ((int) last_capital - (int) first_capital);
    int to_encrypt_int = (int) to_encrypt;
    int encrypted_int = to_encrypt_int + code;

    if (to_encrypt >= first_capital && to_encrypt <= last_capital) {
        if (encrypted_int > ((int) last_capital)) {
            encrypted_int = (int) first_capital - 1 + (encrypted_int - (int) last_capital);
        } else if (encrypted_int < ((int) first_capital)) {
            encrypted_int = (int) last_capital + 1 - ((int) first_capital - encrypted_int);
        }
    }

    char encrypted = (char) encrypted_int;

    return encrypted;
}

int main(int argc, char** argv) {
    std::cout << "Hello from main." << '\n';

    std::cout << "A encrypted with 1 : " << encrypt_letter('A', 1) << '\n'; // B
    std::cout << "B encrypted with -1 : " << encrypt_letter('B', -1) << '\n'; // A
    std::cout << "B encrypted with 1 : " << encrypt_letter('B', 1) << '\n'; // C
    std::cout << "A encrypted with -1 : " << encrypt_letter('A', -1) << '\n'; // Z
    std::cout << "Z encrypted with 1 : " << encrypt_letter('Z', 1) << '\n'; // A
    std::cout << "Z encrypted with -1 : " << encrypt_letter('Z', -1) << '\n'; // Y
    std::cout << "Y encrypted with 1 : " << encrypt_letter('Y', 1) << '\n'; // Z

    return 0;
}
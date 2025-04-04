#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>

int main(int argc, char** argv) {
    std::cout << "Hello" << '\n';

    struct stat buffer;
    stat("my_file.txt", &buffer);
    std::cout << stat("my_file.txt", &buffer) << '\n';

    std::ifstream some_file("my_file.txt");
    std::cout << some_file.eof() << '\n';

    char* line_from_file = new char[1024];
    some_file.getline(line_from_file, 1024);

    while (some_file.good() && !some_file.eof()) {
        std::cout << "End of file: " << some_file.eof() << '\n';
        some_file.getline(line_from_file, 1024);
        std::cout << "Line from file: " << line_from_file << '\n';
        std::cout << "Length of line: " << strlen(line_from_file) << '\n';
    }
    
    std::cout << "End of file: " << some_file.eof() << '\n';
    delete[] line_from_file;

    return 0;
}
#include <iostream>
#include <map>
#include <string>

int main(int argc, char** argv) {
    std::cout << "Hello" << '\n';

    std::multimap<int, std::string> some_multimap;

    some_multimap.insert(std::make_pair(2, "Two"));
    some_multimap.insert(std::make_pair(1, "One"));
    some_multimap.insert(std::make_pair(10, "Ten"));
    some_multimap.insert(std::make_pair(1, "Something"));
    some_multimap.insert(std::make_pair(5, "Bla-Bla"));

    std::cout << some_multimap.size() << '\n';

    typedef std::multimap<int, std::string>::const_iterator my_map_iter;

    for (my_map_iter i = some_multimap.begin(); i != some_multimap.end(); ++i) {
        int int_value = i->first;
        std::string str_value = i->second;

        std::cout << "Something from multimap: " << int_value << " : " << str_value << '\n';
    }

    return 0;
}
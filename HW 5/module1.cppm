#include <iostream>
#include <string>

export module module1;

export std::string getMyName1() {
    std::string name = "John";
    return name;
}

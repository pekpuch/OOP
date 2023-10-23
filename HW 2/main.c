#include <iostream>
#include <string>
#include <regex>

std::string normalizePhoneNumber(const std::string& phoneNumber) {
    std::string normalizedNumber = std::regex_replace(phoneNumber, std::regex("\\D"), "");
    if (normalizedNumber.length() != 11) {
        return "error";
    }
    if (normalizedNumber[0] == '8') {
        normalizedNumber[0] = '7';
    }
    normalizedNumber.insert(0, "+");
    return normalizedNumber;
}

int main() {
    std::string phoneNumber;
    std::cout << "number: ";
    std::getline(std::cin, phoneNumber);
    std::string normalizedNumber = normalizePhoneNumber(phoneNumber);
    std::cout << "normalized number: " << normalizedNumber << std::endl;

    return 0;
}

import module1;
import module2;
#include <iostream>

int main()
{
    std::cout << "Hello world!" << "\n";

    std::cout << getMyName1() << "\n";
    std::cout << getMyName2() << "\n";

    std::cout << getMyName1() << "\n"; // (A)
    std::cout << getMyName2() << "\n";

    std::cout << getMyName2() << "\n"; // (D)

    return 0;
}

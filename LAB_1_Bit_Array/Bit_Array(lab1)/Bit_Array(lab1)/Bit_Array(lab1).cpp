#include"Array.h"

int main()
{
    // Создание и инициализация битового массива
    BitArray bits(8, false);  // Создаем битовый массив из 8 битов
    bits.set(1, true); // Устанавливаем первый бит в значение true
    bits.set(2, true); // Устанавливаем третий бит в значение true
    bits.set(4, true); // Устанавливаем пятый бит в значение true
    std::cout << "BitArray: " << bits.to_string() << std::endl;

    // Использование операторов
    BitArray other(8, false);
    other.set(0, true);
    other.set(3, true);
    other.set(5, true);

    std::cout << "BitArray: " << other.to_string() << std::endl;


    std::cout << "BitArray & other: " << (bits &= other).to_string() << std::endl; // Побитовое И
    std::cout << "BitArray | other: " << (bits |= other).to_string() << std::endl; // Побитовое ИЛИ
    std::cout << "BitArray ^ other: " << (bits ^= other).to_string() << std::endl; // Побитовое исключающее ИЛИ
    std::cout << "~BitArray: " << (~bits).to_string() << std::endl;                 // Побитовое отрицание

    return 0;
}

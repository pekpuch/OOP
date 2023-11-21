#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <algorithm> 

int main() {
    std::ifstream input("input.txt");
    int n;
    input >> n;

    std::unordered_map<int, int> order; // Хранит пары номеров спортсменов
    std::list<int> lineup; // Хранит порядок спортсменов на поле

    // Считываем пары номеров спортсменов из файла
    for (int i = 0; i < n; ++i) {
        int player, before;
        input >> player >> before;
        order[player] = before; // Записываем пары
    }

    // Проходим по всем спортсменам и формируем порядок на поле
    for (auto it = order.begin(); it != order.end(); ++it) {
        auto pos = std::find(lineup.begin(), lineup.end(), it->second); // Ищем позицию спортсмена, перед которым нужно встать
        if (pos != lineup.end()) {
            lineup.insert(pos, it->first); // Если такой спортсмен найден, вставляем текущего спортсмена перед ним
        }
        else {
            lineup.push_back(it->first); // Если не найден, добавляем текущего спортсмена в конец
        }
    }

    // Выводим порядок спортсменов на поле
    for (int player : lineup) {
        std::cout << player << std::endl;
    }

    return 0;
}

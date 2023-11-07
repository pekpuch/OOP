#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <chrono> 
#include <thread> 
#include <regex>
#include <cstring>
#include <random>


struct Cell {
    int x;
    int y;
};

class field {
public:
    field(int val, std::string name) {
        fieldSize = val;
        filename = name;
        if (filename != " ") {
            std::ifstream file(filename);
            std::string line;
            for (int i = 0; i < 2; i++) std::getline(file, line);
            std::getline(file, line);
            int count = 1;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                int x, y;
                if (iss >> x >> y) {
                    if (x >= fieldSize / 2 || y >= fieldSize / 2) {
                        std::cout << "dot number " << count << " is incorrect" << std::endl;
                    }
                    else {
                        auto it = std::find_if(cells.begin(), cells.end(), [&](const Cell& C) {
                            return (C.x == x && C.y == y);
                            });
                        if (it == cells.end()) cells.push_back({ x, y });
                        else std::cout << "dot number " << count << " is incorrect" << std::endl;
                    }
                    count++;
                }
            }
            gameField.resize(fieldSize, std::vector<bool>(fieldSize, false));
            for (int i = 0; i < cells.size(); i++) {
                gameField[cells[i].x + fieldSize / 2][cells[i].y + fieldSize / 2] = true;
            }
            file.close();
        }
        else {
            std::random_device rd;
            std::mt19937 gen(rd());
            int min = 1;
            int max = 100;
            std::uniform_int_distribution<int> dist(min, max);
            int randomDots = dist(gen);

            gameField.resize(fieldSize, std::vector<bool>(fieldSize, false));

            for (int i = 0; i < randomDots; i++) {
                std::random_device rd;
                std::mt19937 gen(rd());
                int min = -fieldSize / 2 + 1;
                int max = fieldSize / 2 - 1;
                std::uniform_int_distribution<int> dist(min, max);
                int randomX = dist(gen);
                int randomY = dist(gen);
                gameField[randomX + fieldSize / 2][randomY + fieldSize / 2] = true;
            }
        }
    }
    ~field() {};
    void printField();
    bool isCellAlive(int row, int col) const;
    void setCellState(int row, int col, bool state);
    int fieldSize;
    std::vector<std::vector<bool>> gameField;
private:
    std::string filename;
    std::vector<Cell> cells;
};


void field::printField() {
    for (int i = 0; i < gameField.size(); ++i) {
        for (int j = 0; j < gameField.size(); ++j) {
            if (!gameField[i][j]) std::cout << "." << " ";
            else std::cout << "o" << " ";
        }
        std::cout << std::endl;

    }
    std::cout << std::endl;
}

bool field::isCellAlive(int row, int col) const {
    if (row < 0 || row >= fieldSize || col < 0 || col >= fieldSize) {
        return false;
    }
    return gameField[row][col];
}

void field::setCellState(int row, int col, bool state) {
    gameField[row][col] = state;
}

class GameOfLife {
private:
    field universe;
    std::string rule;
    std::string UNname;
    int iteration;
    int countLiveNeighbors(int row, int col);
    std::vector <int> B;
    std::vector <int> S;
    void ruleParser();
public:
    GameOfLife(int val, std::string name) : universe(val, name) {
        universe.printField(); 
        if(name !=" "){
            std::ifstream file(name);
            std::string line;
            std::getline(file, line);
            std::getline(file, line);
            if (line[1] == 'N') {
                UNname = line;
                std::getline(file, rule);
            } else std::getline(file, rule);
            ruleParser();
            file.close();
        }
        iteration = 0;
    }
    ~GameOfLife() {};
    void tick(int n);
    void dump(std::string& filename);
};

void GameOfLife::tick(int n) {
    for (int i = 0; i < n; i++) {
        field nextGeneration = universe;
        for (int row = 0; row < universe.fieldSize; row++) {
            for (int col = 0; col < universe.fieldSize; col++) {
                int numAliveNeighbors = countLiveNeighbors(row, col);
                auto it = std::find(B.begin(), B.end(), numAliveNeighbors);
                auto it2 = std::find(S.begin(), S.end(), numAliveNeighbors);

                if (universe.isCellAlive(row, col)) {
                    if (it2 == S.end()) {
                        nextGeneration.setCellState(row, col, false);
                    }
                }
                else {
                    if (it != B.end()) {
                        nextGeneration.setCellState(row, col, true);
                    }
                }
            }
        }
        universe = nextGeneration;
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
        iteration++;
        universe.printField();
        std::cout << "iteration: " << iteration << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int GameOfLife::countLiveNeighbors(int row, int col) {
    int count = 0;
    int numRows = universe.fieldSize;
    int numCols = universe.fieldSize;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int neighborRow = (row + i + numRows) % numRows;
            int neighborCol = (col + j + numCols) % numCols;

            if (universe.isCellAlive(neighborRow, neighborCol)) {
                count++;
            }
        }
    }
    if (universe.isCellAlive(row, col)) {
        count--;
    }
    return count;
}

void GameOfLife::dump(std::string& filename) {
    std::string name = filename;
    std::ofstream NewUniverse(filename);
    NewUniverse << "#Life 1.06" << std::endl;
    if (!name.empty()) NewUniverse << UNname << std::endl;
    NewUniverse << rule << std::endl;

    for (int i = 0; i < universe.gameField.size(); ++i) {
        for (int j = 0; j < universe.gameField.size(); ++j) {
            if (universe.gameField[i][j]) {
                NewUniverse << i - universe.fieldSize / 2 << ' ' << j - universe.fieldSize / 2 << std::endl;
            }
        }
    }
    NewUniverse.close();
}

void GameOfLife::ruleParser() {
    for (int i = 0; i < rule.size(); i++) {
        switch (rule[i]) {
            case ('B'): {
                int j = i + 1;
                while (isdigit(rule[j])) {
                    B.push_back(rule[j] - '0');
                    j++;
                }
                i = j;
                break;
            }
            case ('S'): {
                int j = i + 1;
                while (isdigit(rule[j])) {
                    S.push_back(rule[j] - '0');
                    j++;
                }
                i = j;
                break;
            }
        }
    }
}

bool FileCheck(std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    if (line != "#Life 1.06") {
        std::cout << "error in 1st string" << std::endl;
        return false;
    }

    std::getline(file, line);
    if (line.empty() || line[0] != '#' || line[1] != 'N') {
        std::cout << "error in 2nd string" << std::endl;
        return false;
    }

    std::getline(file, line);
    std::regex pattern("#R B[0-8]+/S[0-8]+");
    if (std::regex_match(line, pattern) == true) return true;
    else {
        std::cout << "error in 3d string" << std::endl;
        return false;
    }
}


int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::random_device rd;
        std::mt19937 gen(rd());

        int min = 5;
        int max = 20;

        std::uniform_int_distribution<int> dist(min, max);

        int randomNum = dist(gen);
        std::string filename = " ";
        int fieldSize = randomNum;
        GameOfLife game(fieldSize, filename);
        std::string command;
        while (true) {
            game.tick(1);
        }
    }
        else {
            if (argc == 2) {
                std::string filename = argv[1];
                int fieldSize = 10;
                if (FileCheck(filename)) {
                    GameOfLife game(fieldSize, filename);
                    std::string command;
                    while (true) {
                        std::cout << "Command (dump <filename>, tick <n=1>, exit, help): ";
                        std::cin >> command;
                        if (command == "dump") {
                            std::string saveName;
                            std::cin >> saveName;
                            game.dump(saveName);
                        }
                        else if (command == "tick" || command == "t") {
                            int n = 1;
                            std::cin >> n;
                            game.tick(n);
                        }
                        else if (command == "tick\n") {
                            game.tick(1);
                        }
                        else if (command == "exit") {
                            break;
                        }
                        else if (command == "help") {
                            std::cout << "Commands:" << std::endl;
                            std::cout << "dump <filename> - save the universe" << std::endl;
                            std::cout << "tick <n=1> (or t <n=1>) - count n of iterations" << std::endl;
                            std::cout << "exit - finish the game" << std::endl;
                            std::cout << "help - list of commands" << std::endl;
                        }
                        else {
                            std::cout << "Unknown command! Type 'help'" << std::endl;
                        }
                    }
                }
            }
            else {
                if (argc == 4) {
                    std::string filename = argv[1];
                    std::string saveFile = argv[2];
                    int iterations = std::stoi(argv[3]);
                    int fieldSize = 10;
                    if (FileCheck(filename)) {
                        GameOfLife game(fieldSize, filename);
                        std::string command;
                        game.tick(iterations);
                        game.dump(saveFile);
                        while (true) {
                            std::cout << "Command (dump <filename>, tick <n=1>, exit, help): ";
                            std::cin >> command;
                            if (command == "dump") {
                                std::string saveName;
                                std::cin >> saveName;
                                game.dump(saveName);
                            }
                            else if (command == "tick" || command == "t") {
                                int n = 1;
                                std::cin >> n;
                                game.tick(n);
                            }
                            else if (command == "tick\n") {
                                game.tick(1);
                            }
                            else if (command == "exit") {
                                break;
                            }
                            else if (command == "help") {
                                std::cout << "Commands:" << std::endl;
                                std::cout << "dump <filename> - save the universe" << std::endl;
                                std::cout << "tick <n=1> (or t <n=1>) - count n of iterations" << std::endl;
                                std::cout << "exit - finish the game" << std::endl;
                                std::cout << "help - list of commands" << std::endl;
                            }
                            else {
                                std::cout << "Unknown command! Type 'help'" << std::endl;
                            }
                        }   
                    }
                }
            }
        }
    }

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <ctime>

//структура для хранения дат и value
struct Transaction { 
    std::tm from;                                     
    std::tm to;
    int value;
};

//перевод std::string в std::tm
std::tm parseDate(const std::string& date) {
    std::tm t = {};
    std::istringstream ss(date);                        
    ss >> std::get_time(&t, "%Y-%m-%d");
    return t;
}

//сравнение дат std::tm 
bool compareDates(const std::tm& date1, const std::tm& date2) {
    if (date1.tm_year < date2.tm_year) return true;
    else if (date1.tm_year > date2.tm_year) return false;
    if (date1.tm_mon < date2.tm_mon) return true;              
    else if (date1.tm_mon > date2.tm_mon) return false;
    if (date1.tm_mday < date2.tm_mday) return true;
    else if (date1.tm_mday > date2.tm_mday) return false;
    return false;
}

//фиксация прибыли
double computeIncome(std::vector<Transaction>& transactions, std::tm from_date, std::tm to_date) {
    double income = 0;

    //количество дней, указаных в запросе
    std::time_t Zdays_from = std::mktime(&from_date) / (24 * 60 * 60);
    std::time_t Zdays_to = std::mktime(&to_date) / (24 * 60 * 60);
    int days_z = std::abs((std::difftime(Zdays_from, Zdays_to)));

    for (int i = 0; i < transactions.size(); i++) {

        //количество дней заработка
        std::time_t Edays_from = std::mktime(&transactions[i].from) / (24 * 60 * 60) ; 
        std::time_t Edays_to = std::mktime(&transactions[i].to) / (24 * 60 * 60); 
        int days_e = std::abs((std::difftime(Edays_from, Edays_to)))+1;

        //подсчет заработка за 1 день
        int dayly_income = transactions[i].value/days_e;

        //если первая дата диапазона в запросе больше первой даты диапазона заработка
        //вычитаем из дней заработка разницу
        if (compareDates(from_date, transactions[i].from) == false) {
            days_e -= std::abs(Zdays_from - Edays_from );
        }

        //если вторая дата диапазона в запросе еньше второй даты диапазона заработка
        //вычитаем из дней заработка разницу
        if (compareDates(to_date, transactions[i].to) == true) {
            days_e -= std::abs(Zdays_to - Edays_to );
        }

        income += days_e * dayly_income;
    }
    return income;
}

int main() {
    std::ifstream inputFile("input.txt");
    int Q;
    inputFile >> Q;
    std::vector<Transaction> transactions;
    for (int i = 0; i < Q; i++) {
        std::string type;
        inputFile >> type;

        if (type == "Earn") {
            std::string from, to;
            int value;
            inputFile >> from >> to >> value;
            transactions.push_back({ parseDate(from), parseDate(to), value });
        }
        else {
            std::string from, to;
            inputFile >> from >> to ;
            double income = computeIncome(transactions, parseDate(from), parseDate(to));
            std::cout << std::fixed << income << std::endl;

        }
    }
}

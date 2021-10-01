#include <iostream>
#include <exception>

using namespace std;

//спецификациии с собственным реализованным исключением.
/**
 * @brief независимый класс с полями - параметрами функции 
 * 
 */
class DivisionByZero_1 {
private:
    /**
     * @brief переменная для вывода значений
     * 
     */
    string message;
public:
    DivisionByZero_1() : message("Division by zero_1") {}
};
    /**
     * @brief DivisionByZero_2 - наследник от стандартного исключения с полями
     * 
     */
class DivisionByZero_2 : public logic_error { 
public:
    DivisionByZero_2() : logic_error("Division by zero_2") {}
};

class DivisionByZero_3 {//собственное исключение как пустой класс

};

/**
 * @brief структура FazzyNumber
 * 
 */
class FuzzyNumber {
    int x;
    int e1;
    int e2;
public:
    /**
     * @brief Construct a new Fuzzy Number object
     * 
     */
    FuzzyNumber() : x(0), e1(0), e2(0) {}
    /**
     * @brief Construct a new Fuzzy Number object
     * 
     * @param a 
     * @param b 
     * @param c 
     */
    FuzzyNumber(const int a, const int b, const int c) : x(a), e1(b), e2(c) {}
    /**
     * @brief спецификация throw
     * 
     * @param other 
     * @return FuzzyNumber 
     */
    FuzzyNumber operator/(const FuzzyNumber& other) {
        FuzzyNumber f3;
        if (other.x == 0) {
            throw DivisionByZero_1();
        }
        f3.x = x / other.x;

        if ((other.x + other.e2) == 0) {
            throw DivisionByZero_2();;
        }
        f3.e1 = f3.x - (this->x - this->e1) / (other.x + other.e2);

        if ((other.x - other.e1) == 0) {
            throw runtime_error("Division by zero (std)");
        }
        f3.e2 = (this->x + this->e2) / (other.x - other.e1) - f3.x;
    }
};

/**
 * @brief Обработкa исключений (обработка всех перехватываемых исключений.)
 * 
 * @return int 
 */
int main() { 
    FuzzyNumber fn1(1, 2, 3);
    FuzzyNumber fn2(0, 1, 2);
    FuzzyNumber fn3(-1, 1, 1);
    FuzzyNumber fn4(2, 2, 4);

    //проверка передаваемых параметров и генерация исключения в случае ошибочных.
    try {
        FuzzyNumber fn = fn1 / fn2;
    }
    catch (const DivisionByZero_1&) {
        cout << "Error: x = 0" << endl;
    }

    try {
        FuzzyNumber fn = fn1 / fn3;
    }
    catch (const DivisionByZero_2&) {
        cout << "Error: x + e2 = 0" << endl;
    }

    try {
        FuzzyNumber fn = fn1 / fn4;
    }
    catch (const DivisionByZero_3&) {
        cout << "STD Error: x - e1 = 0" << endl;
    }

    return 0;
}

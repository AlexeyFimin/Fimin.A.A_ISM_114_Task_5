#include <iostream>
#include <exception>

using namespace std;

//спецификациии с собственным реализованным исключением.
class DivisionByZero_1 {//независимый класс с полями - параметрами функции,
private:
    string message;
public:
    DivisionByZero_1() : message("Division by zero_1") {}
};

class DivisionByZero_2 : public logic_error {  //DivisionByZero_2 - наследник от стандартного исключения с полями.
public:
    DivisionByZero_2() : logic_error("Division by zero_2") {}
};

class DivisionByZero_3 {//собственное исключение как пустой класс

};

//структура FazzyNumber
class FuzzyNumber {
    int x;
    int e1;
    int e2;
public:
    FuzzyNumber() : x(0), e1(0), e2(0) {}

    FuzzyNumber(int a, int b, int c) : x(a), e1(b), e2(c) {}

    FuzzyNumber operator/(const FuzzyNumber& other) {
        FuzzyNumber f3;
        if (other.x == 0) {
            throw DivisionByZero_1();//спецификация throw;
        }
        f3.x = x / other.x;

        if ((other.x + other.e2) == 0) {
            throw DivisionByZero_2();//спецификация throw;
        }
        f3.e1 = f3.x - (this->x - this->e1) / (other.x + other.e2);

        if ((other.x - other.e1) == 0) {
            throw runtime_error("Division by zero (std)");//спецификация throw;
        }
        f3.e2 = (this->x + this->e2) / (other.x - other.e1) - f3.x;
    }
};


int main() { //Обработкa исключений (обработка всех перехватываемых исключений.)
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

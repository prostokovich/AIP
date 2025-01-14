#include <iostream>
#include <cmath>
#include <stdexcept>

class CustomException : public std::exception {
private:
    std::string message;
    double errorValue;
    int errorCode;

public:
    CustomException(const std::string& msg, double value, int code)
        : message(msg), errorValue(value), errorCode(code) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getErrorValue() const {
        return errorValue;
    }

    int getErrorCode() const {
        return errorCode;
    }
};

void calculateZ1(double x, double& z1) {
    try {
      
        if (x == 1) {
            throw CustomException("Деление на ноль при вычислении z1", x, 1);
        }
        if (x * x - 9 < 0) {
            throw CustomException("Квадратный корень из отрицательного числа при вычислении z1", x, 2);
        }

        double numerator = (x + 1) * std::sqrt(x * x - 9) + x * (x + 2) - 3;
        double denominator = (x - 1) * std::sqrt(x * x - 9) + x * x - 2 * x - 3;
        z1 = numerator / denominator;
    }
    catch (const CustomException& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        std::cerr << "Значение: " << e.getErrorValue() << ", Код ошибки: " << e.getErrorCode() << "\n";
        throw;  
    }
}

void calculateZ2(double x, double& z2) {
    try {
       
        if (x == 3) {
            throw CustomException("Деление на ноль при вычислении z2", x, 3);
        }
        if (x + 3 < 0) {
            throw CustomException("Квадратный корень из отрицательного числа при вычислении z2", x, 4);
        }

        z2 = std::sqrt((x + 3) / (x - 3));
    }
    catch (const CustomException& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        std::cerr << "Значение: " << e.getErrorValue() << ", Код ошибки: " << e.getErrorCode() << "\n";
        throw;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    double x, z1, z2;

    std::cout << "Введите значение x: ";
    std::cin >> x;

    try {
        calculateZ1(x, z1);
        calculateZ2(x, z2);

        std::cout << "z1 = " << z1 << "\n";
        std::cout << "z2 = " << z2 << "\n";

        if (std::fabs(z1 - z2) < 1e-5) {
            std::cout << "Значения z1 и z2 приблизительно равны.\n";
        }
        else {
            std::cout << "Значения z1 и z2 различаются.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Обработка исключения: " << e.what() << "\n";
    }

    return 0;
}

#include <iostream>
#include <iomanip>
#include <cmath> 

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << std::fixed << std::setprecision(3);

    for (double t = 0; t <= 3; t += 0.5) {
        double y = std::cos(t);

        std::cout << "t = " << std::setw(10) << t << "  y = " << std::setw(10) << y << std::endl;
    }

    return 0;
}
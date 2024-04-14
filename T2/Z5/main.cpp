// TP 2022/2023: LV 2, Zadatak 5
#include <cmath>
#include <complex>
#include <iostream>

typedef std::complex<double> Kompleksni;

int main() {
    Kompleksni z, suma(0, 0);
    int broj;
    std::cout << "Unesi broj elemenata:";
    std::cin >> broj;
    std::cout << std::endl;

    for (int i = 0; i < broj; i++) {
        double modul, argument;
        std::cout << "Z" << i + 1 << " = ";
        std::cin >> modul;
        std::cout << "fi" << i + 1 << " = ";
        std::cin >> argument;
        argument = argument * ((4 * atan(1))/180);
        std::cout << std::endl;
        z = std::polar(modul, argument);
        suma += 1. / z;
    }
    suma = 1. / suma;

    std::cout << "Paralelna veza ovih elemenata ima Z = " << std::abs(suma)
            << " i fi = " << std::arg(suma) * (180 / (4 * atan(1))) << "."<< std::endl;
    return 0;
}

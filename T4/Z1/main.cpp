// TP 2022/2023: LV 4, Zadatak 1
#include <cmath>
#include <iostream>

int Cifre(long long int broj, int &c_min, int &c_max) {
    c_min=abs(int(broj%10)), c_max=abs(int(broj%10));
    int broj_cifara = 1;
    broj/=10;
    if (broj < 0)   broj = broj * (-1);
    while (broj != 0) {
        if ((broj % 10) > c_max) c_max = (broj % 10);
        if ((broj % 10) < c_min) c_min = (broj % 10);
        broj_cifara++;
        broj=broj/10;
    }
    return broj_cifara;
}

int main() {
    std::cout << "Unesite broj: ";
    long long int n;
    std::cin >> n;
    int c_min, c_max;
    std::cout << "Broj " << n << " ima " << Cifre(n, c_min, c_max) << " cifara, najveca je " << c_max<< " a najmanja " << c_min << "." << std::endl;
    return 0;
}

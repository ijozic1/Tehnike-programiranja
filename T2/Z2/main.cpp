// TP 2022/2023: LV 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <vector>
#define EPSILON 0.0001

bool TestPerioda(std::vector<double> periodican, int period) {
    // bool ispravan_period=true;
    for (int i = 0, j = i + period; j < periodican.size(); i++, j++) {
        if (fabs(periodican[i] - periodican[j]) > EPSILON)
            return false;
    }
    if (periodican.size() == 1 || period >= periodican.size())
        return false;
    return true;
}

int OdrediOsnovniPeriod(std::vector<double> slijed) {
    int period = 1;
    double *pocetak = &slijed[0];
    for (int i = 1; i < slijed.size(); i++) {
        if (fabs(*pocetak - slijed[i]) < EPSILON) {
            // bool ispravan_period=TestPerioda(slijed,period);
            if (TestPerioda(slijed, period))
                break;
        }
        period++;
    }
    if (period == slijed.size() || slijed.size() == 1)
        period = 0;
    return period;
}

int main() {
    std::vector<double> brojevi;
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    double n;
    do {
        std::cin >> n;
        if (n != 0) {
            brojevi.push_back(n);
        }
    } while (n != 0);

    int period = OdrediOsnovniPeriod(brojevi);
    /*int per;
    std::cout << "Unesite period: ";
    std::cin >> per;

    bool period = TestPerioda(brojevi, per);
    std::cout << std::boolalpha << period << std::endl;*/

    if (period)
        std::cout << "Slijed je periodican sa osnovnim periodom " << period << "."<< std::endl;
    else
        std::cout << "Slijed nije periodican!" << std::endl;

    return 0;
}

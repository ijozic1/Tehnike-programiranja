//TP 2022/2023: LV 12, Zadatak 5
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int n;
    std::cout << "Koliko zelite elemenata: ";
    std::cin >> n;

    std::vector<double> vektor(n);
    std::cout << "Unesite elemente: ";
    for (int i = 0; i < n; i++) {
        std::cin >> vektor[i];
    }

    // Zamjena elemenata vektora njihovim recipročnim vrijednostima ali koristena lambda
    //std::transform(vektor.begin(), vektor.end(), vektor.begin(), std::bind1st(std::divides<double>(), 1.0));
    std::transform(vektor.begin(), vektor.end(), vektor.begin(),std::bind(std::divides<double>(), 1.0, std::placeholders::_1));
    //std::transform(vektor.begin(), vektor.end(), vektor.begin(), std::function<double(double)>([](double x) { return 1.0 / x; }));


    std::cout << "Transformirani elementi: ";
    for (const auto& element : vektor) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}

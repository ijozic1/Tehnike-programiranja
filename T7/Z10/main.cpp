//TP 2022/2023: LV 7, Zadatak 10
#include <iostream>
#include <functional> 

int f(int broj){
    return broj+2;
}

std::function<int(int)> IteriranaFunkcija(std::function<int(int)> f, int n) {
    if (n <= 0) return [](int x) { return x; };
    return [f, n](int x) {
        int rezultat = x;
        for (int i = 0; i < n; i++) rezultat = f(rezultat);
        return rezultat;
    };
}

int main() {
    auto g1 = IteriranaFunkcija(f, 0);
    std::cout << g1(5) << std::endl; 

    auto g2 = IteriranaFunkcija(f, 5);
    std::cout << g2(5) << std::endl;
    return 0;
}

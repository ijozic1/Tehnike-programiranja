// TP 2022/2023: Zadaća 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <vector>
bool DaLiJeProst(long int n){
    for(int i=2; i<=std::sqrt(n); i++) 
        if(n%i==0) return false;
    return true;
}
void RastavaBroja(int n, int &p, int &q) {
    int predznak = 1;
    long int broj = n;
    p = 1; q = 1;
    if (broj < 0) {
        predznak = -1;
        broj *=(-1);
    }
    if (broj == 0) {
        p = 0; q = 1;
    }
    else if(DaLiJeProst(broj))p=broj*predznak;
    else {
        std::vector<long int> djelioci;
        for (int i = 2; i <= broj; i++) {
            if (broj % i == 0) {
                djelioci.push_back(i);
                broj /= i; i = 1;
            }  
        }
        int brojac = 1;
        for (int i = 0; i < djelioci.size(); i++) {
            brojac = 1;
            while (i != djelioci.size() - 1 && djelioci.at(i) == djelioci.at(i + 1)) {
                brojac++; i++;
            }
            if (brojac % 2 != 0) {
                p *= djelioci.at(i);
                brojac--;
            }
            q *= std::pow(djelioci.at(i), brojac / 2);
        }
        p = p * predznak;
    }
}

int main() {
    std::cout << "Unesi broj: ";
    int n = 0;
    std::cin >> n;
    int p = 1, q = 1;
    RastavaBroja(n, p, q);
    std::cout << std::endl<<n << " = " << p << "*" << q << "^2" << std::endl;
    return 0;
}
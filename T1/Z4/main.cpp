// TP 2016/2017: LV 1, Zadatak 4
#include <cmath>
#include <cstdio>
#include <iostream>

int main() {
  int n /*,unos=0*/;
  double m;
  do {
    n = -1;
    std::cout << "Unesite prirodan broj ili 0 za kraj: ";
    /*unos=scanf("%d",&n);*/
    /*std::cin>>n;*/
    std::cin >> m;
    if(!std::cin){
        /*Ako je unos neispravan onda m dobije vrijednost 0 - debugger*/
        m=-1;
    }
    if (static_cast<int>(m) == m) {
      n = m;
    }

    if (/*unos*/ std::cin && n > 0) {
      int suma = 0;
      for (int i = 1; i < n; i++) {
        if (n % i == 0) {
          suma += i;
        }
      }
      if (suma < n) {
        std::cout << "Broj " << n << " je manjkav!" << std::endl;
      } else if (suma == n) {
        std::cout << "Broj " << n << " je savrsen!" << std::endl;
      } else {
        std::cout << "Broj " << n << " je obilan!" << std::endl;
      }
    } else if (/*unos==0 !std::cin ||*/ n < 0) {
      std::cout << "Niste unijeli prirodan broj!" << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  } while (n != 0);
  std::cout << "Dovidjenja!";
  return 0;
}
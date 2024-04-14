//TP 2022/2023: LV 5, Zadatak 2
#include <iostream>
#include <cmath>

template <typename IterTip1, typename IterTip2>
IterTip2 RazmijeniBlokove(IterTip1 pocetak, IterTip1 izaKraja, IterTip2 odrediste){
    auto pomocni=*pocetak;
    while(pocetak!=izaKraja){
        pomocni=*pocetak;
        *pocetak=*odrediste;
        *odrediste=pomocni;
        pocetak++;
        odrediste++;
    }
    return odrediste;
}

int main (){
    int a[]{1, 2, 3, 4, 5}, b[]{6, 7, 8, 9, 10};
    RazmijeniBlokove(std::begin(a), std::end(a), std::begin(b));
    std::cout << "Prvi niz: ";
    for(int x : a) std::cout << x << " ";
    std::cout << "\nDrugi niz: ";
    for(int x : b) std::cout << x << " ";

    std::string s1("String1"), s2("String2");
    RazmijeniBlokove(s1.begin(), s1.end(), s2.begin());
    std::cout << "\n\nPrvi string: " << s1 << std::endl;
    std::cout << "Drugi string: " << s2 << std::endl;

	return 0;
}

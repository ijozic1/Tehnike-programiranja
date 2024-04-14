//TP 2022/2023: LV 5, Zadatak 6
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

void UnesiElement(int &clan) { std::cin >> clan; }

int ZbirCifara(int broj){
    broj=abs(broj);
    if(broj==0) return 0;
    return broj%10+ZbirCifara(broj/10);
}

bool Sortiraj(int a, int b){
    if(ZbirCifara(a)==ZbirCifara(b)) return a<b;
    return ZbirCifara(a)<ZbirCifara(b);
}

int main (){
    std::cout<<"Unesite broj elemenata: ";
    int velicina=0;
    std::cin>>velicina;
    std::vector<int> kolekcija (velicina);
    std::cout<<"Unesite elemente: ";
    std::for_each(kolekcija.begin(), kolekcija.end(), UnesiElement);
    std::sort(kolekcija.begin(), kolekcija.end(),Sortiraj);
    std::cout<<"Niz sortiran po sumi cifara glasi: ";
    std::for_each(kolekcija.begin(), kolekcija.end(), [](int x){std::cout<<x<<" ";});
    std::cout<<std::endl;
    std::cout<<"\nUnesite broj koji trazite: ";
    int n;
    std::cin>>n;
    bool sadrzan=std::binary_search(kolekcija.begin(), kolekcija.end(),n,Sortiraj);
    if(sadrzan)
        std::cout<<"Trazeni broj nalazi se na poziciji "<<std::lower_bound(kolekcija.begin(), kolekcija.end(),n,Sortiraj)-kolekcija.begin();
    else std::cout<<"Trazeni broj ne nalazi se u nizu!";
	return 0;
}
//TP 2022/2023: LV 6, Zadatak 2
#include <iostream>
#include <cmath>
#include <exception>
#include <new>
#include <vector>
//lista ne moze sa pokazivacima zato ne prolazi 4.AT

template<typename IterTip>
auto KreirajIzvrnutiNiz(IterTip pocetak, IterTip izaKraja)->decltype(&*pocetak){
    using tipElement = typename std::iterator_traits<IterTip>::value_type;
    tipElement *noviPocetak=nullptr;
    try{
        noviPocetak=new tipElement[izaKraja-pocetak];
        tipElement *noviKraj = noviPocetak;
        for (int i = 0; i < izaKraja - pocetak; i++) {
            *noviKraj = *(izaKraja - i - 1);
            noviKraj++;
        }
        return noviPocetak;
    }
    catch(std::bad_alloc){
        throw std::bad_alloc();    
    }
    return noviPocetak;
}

int main (){
    std::cout<<"Koliko zelite elemenata: ";
    int n;
    std::cin>>n;
    try{
        std::vector<double> v(n);
        std::cout<<"Unesite elemente: ";
        for(double &x : v) std::cin>>x;
        auto pok=KreirajIzvrnutiNiz(v.begin(), v.end());
        std::cout<<"Kreirani niz: ";
        for(int i=0; i<n; i++) std::cout<<pok[i]<<" ";
        delete [] pok;
    }
    catch(std::bad_alloc){
        std::cout<<"Nedovoljno memorije!";
    }
	return 0;
}
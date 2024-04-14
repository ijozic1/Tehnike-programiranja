//TP 2022/2023: LV 6, Zadatak 1
#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>

//test 8 - chat gpt kaze da u long long int moze najvise stati 2^16383 i zbog toga u testu baca izuzetak

template <typename Tip1>
Tip1 *GenerirajStepeneDvojke(int n){
    if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
    Tip1 *niz=nullptr;
    try{
        niz=new Tip1[n];
    }
    catch(...){
        throw std::runtime_error("Alokacija nije uspjela");
    }
    for(int i=0; i<n; i++){
        if(static_cast<long double>((pow(2,i)))>std::numeric_limits<Tip1>::max() || pow(2,i)<0){
            delete [] niz;
            throw std::overflow_error("Prekoracen dozvoljeni opseg");
        }
        niz[i]=pow(2,i);
    }
    return niz;
}


int main (){
    std::cout<<"Koliko zelite elemenata: ";
    int n=0;
    std::cin>>n;
    try{
        unsigned long long int *pok=GenerirajStepeneDvojke<unsigned long long int>(n);
        std::cout<<std::endl;
        for(int i=0; i<n; i++) std::cout<<pok[i]<<" ";
        delete [] pok;
    }
    catch(std::domain_error &izuzetak){
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    catch(std::overflow_error &izuzetak){
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    catch(std::runtime_error &izuzetak){
        std::cout<<"Izuetak: "<<izuzetak.what();
    }
}
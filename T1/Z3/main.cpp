//TP 2016/2017: LV 1, Zadatak 3
#include <iostream>
#include <iomanip>
#include <cmath>
int main ()
{
    int a, b;
    std:: cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;
    if(a>9999 || b>9999 || a>b){
        std::cout<<"Uneseni brojevi ne zadovoljavaju uslove iz postavke zadatka!"<<std::endl;
        return 1;
    }
    std:: cout<<"+---------+----------+----------+-----------+"<<std::endl;
    std:: cout<<"| Brojevi | Kvadrati | Korijeni | Logaritmi |"<<std::endl;
    std:: cout<<"+---------+----------+----------+-----------+"<<std::endl;
    for(int i=a; i<=b; i++){
        std::cout<<"|"<<std::left<<" "<<std::setw(8)<<i<<"|"<<std::right<<std::setw(9)<<i*i<<" |";
        std::cout<<std::right<<std::setw(9)<<std::fixed << std::setprecision(3)<<std::sqrt(i)<<" |";
        std::cout<<std::right<<std::setw(10)<<std::fixed << std::setprecision(5)<<std::log(i)<<" |";
        std::cout<<std::endl;
    }
    std:: cout<<"+---------+----------+----------+-----------+"<<std::endl;
    
	return 0;
}
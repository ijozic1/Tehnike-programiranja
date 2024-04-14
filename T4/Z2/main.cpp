//TP 2022/2023: LV 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>

void IzvrniString(std::string &recenica){
    for(int i=0; i<recenica.length()/2; i++){
        char znak=recenica.at(i);
        recenica.at(i)=recenica.at(recenica.length()-1-i);
        recenica.at(recenica.length()-1-i)=znak;
    }
}

int main (){
    std:: cout<<"Unesi string: ";
    std:: string pocetni;
    std:: getline(std::cin, pocetni);

    IzvrniString(pocetni);
    std::cout<<"Izvrnuti string je: "<<pocetni<<std::endl;
	return 0;
}
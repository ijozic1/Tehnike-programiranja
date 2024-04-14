//TP 2022/2023: LV 3, Zadatak 8
#include <iostream>
#include <cmath>
#include <string>

std:: string IzdvojiRijec(std:: string recenica, int n){
    if(n<1) throw std::range_error("Pogresan redni broj rijeci!");
    std:: string rijec;
    int broj_rijeci=0;
    for(int i=0; i<recenica.length(); i++){
        if(recenica[i]!=' '  && (i==0 || recenica[i-1]==' ')) broj_rijeci++;
        if(broj_rijeci==n){
            while(i<recenica.length() && recenica[i]!=' '){
                rijec.push_back(recenica[i]);
                i++;
            }
        }
    }
    if(rijec.length()==0) throw std::range_error("Pogresan redni broj rijeci!");
    return rijec;
}


int main (){
    int n;
    std::cout<<"Unesite redni broj rijeci: ";
    std::cin>>n;
    std::cin.ignore(1000,'\n');
    std::string s;
    std::cout<<"Unesite recenicu: ";
    std::getline(std::cin, s);

    try{
        auto rijec=IzdvojiRijec(s,n);
        std::cout<<"Rijec na poziciji "<<n<<" je "<<rijec<<std::endl;
    }
    catch(std::range_error izuzetak){
        std::cout<<"IZUZETAK: "<<izuzetak.what()<<std::endl;
    }
    
	return 0;
}

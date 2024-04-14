//TP 2022/2023: LV 10, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>

class StedniRacun{
    mutable double stanjeRacuna;
  public:
    StedniRacun(){stanjeRacuna=0;}
    StedniRacun(double x=0){ 
        if(x<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        stanjeRacuna=x;
    }
    void Ulozi(double x)const;
    void Podigni(double x) const;
    double DajStanje()const {return stanjeRacuna;}
    double ObracunajKamatu(double kamata);

};
void StedniRacun::Ulozi(double x)const{
    if(x+stanjeRacuna<0) throw std::logic_error("Transakcija odbijena");
    stanjeRacuna+=x;
}
void StedniRacun::Podigni (double x) const{
    if(x>stanjeRacuna) throw std::logic_error("Transakcija odbijena");
    stanjeRacuna-=x;
}
double StedniRacun::ObracunajKamatu(double kamata){
    if(kamata<0) throw std::logic_error("Nedozvoljena kamatna stopa");
    this->stanjeRacuna+=kamata*0.01*this->stanjeRacuna;
    return this->stanjeRacuna;
}

int main (){
    StedniRacun racun1(50);
    try{
        racun1.ObracunajKamatu(5);
        std::cout << racun1.DajStanje()<<std::endl;
    }
    catch(std::logic_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}
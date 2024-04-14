//TP 2022/2023: LV 11, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>

class StedniRacun{
    mutable double stanjeRacuna;
    static int brojKreiranihRacuna;
    static int brojAktivnihRacuna;
  public:
    StedniRacun(){stanjeRacuna=0; brojKreiranihRacuna++; brojAktivnihRacuna++;}
    StedniRacun(double x){ 
        if(x<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        stanjeRacuna=x;
        brojKreiranihRacuna++; brojAktivnihRacuna++;
    }
    StedniRacun(const StedniRacun &racun){
        if(racun.stanjeRacuna<0) throw std::logic_error("Nedozvoljeno stanje racuna");
        stanjeRacuna=racun.stanjeRacuna;
        brojKreiranihRacuna++; brojAktivnihRacuna++;
    }
    ~StedniRacun(){
        brojAktivnihRacuna--;
    }
    void Ulozi(double x)const;
    void Podigni(double x) const;
    static int DajBrojKreiranih() {return brojKreiranihRacuna;}
    static int DajBrojAktivnih() {return brojAktivnihRacuna;}
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
int StedniRacun::brojKreiranihRacuna=0;
int StedniRacun::brojAktivnihRacuna=0;

int main (){
    StedniRacun racun1(50);
    try{
        racun1.ObracunajKamatu(5);
        std::cout << racun1.DajStanje()<<std::endl;
        StedniRacun s1, s2(100);
        { StedniRacun s3(50); } // Nakon "}", "s3" više ne postoji...
        std::cout << StedniRacun::DajBrojKreiranih()<< " " << StedniRacun::DajBrojAktivnih(); // Ispisuje "3 2"
    }
    catch(std::logic_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}

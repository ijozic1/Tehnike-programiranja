//TP 2022/2023: LV 10, Zadatak 2
#include <iomanip>
#include <iostream>
#include <cmath>
#include <stdexcept>

class Krug{
    double poluprecnik;
  public:
    explicit Krug(double x){Postavi(x);}
    void Postavi(double x);
    double DajPoluprecnik() const {return poluprecnik;}
    double DajObim() const {return 2*poluprecnik*4*atan(1);}
    double DajPovrsinu() const {return poluprecnik*poluprecnik*4*atan(1);}
    void Skaliraj(double faktor);
    void Ispisi() const{std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();}
};

void Krug::Postavi(double x){
    if(x<=0) throw std::domain_error("Neispravan poluprecnik");
    poluprecnik=x;
}
void Krug::Skaliraj(double faktor){
    if(faktor<=0) throw std::domain_error("Neispravan faktor skaliranja");
    poluprecnik*=faktor;
}

class Valjak{
    double visina;
    Krug baza;
  public:
    explicit Valjak(double r, double h):baza(r){
        if(r<=0) throw std:: domain_error("Neispravan poluprecnik");
        if(h<=0) throw std:: domain_error("Neispravna visina");
        visina=h;}
    void Postavi(double r, double h);
    Krug DajBazu() const{return baza;}
    double DajPoluprecnikBaze() const{return baza.DajPoluprecnik();}
    double DajVisinu() const{return visina;}
    double DajPovrsinu() const{return 2*baza.DajPovrsinu()+baza.DajObim()*visina;}
    double DajZapreminu() const{ return baza.DajPovrsinu()*visina;}
    void Skaliraj(double faktor){
        if(faktor<=0) throw std::domain_error("Neispravan faktor skaliranja");
        visina*=faktor; baza.Postavi(DajPoluprecnikBaze()*faktor);
    }
    void Ispisi() const{
        std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnikBaze()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();
    }
};

void Valjak::Postavi(double r, double h){
    if(r<=0) throw std:: domain_error("Neispravan poluprecnik");
    if(h<=0) throw std:: domain_error("Neispravna visina");
    baza.Postavi(r); visina=h;
}

int main (){
    try{
        Krug k(5);
        k.Ispisi(); std::cout << std::endl;
        Valjak v1(1, 9);
        v1.Ispisi(); std::cout << std::endl;
        v1.DajBazu().Ispisi(); std::cout << std::endl;
        Valjak v2(k.DajPoluprecnik(),8);
        v2.DajBazu().Ispisi(); std::cout << std::endl;
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}

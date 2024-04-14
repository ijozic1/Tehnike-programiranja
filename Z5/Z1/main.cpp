//TP 2022/2023: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>
#include <stdexcept>

class Sinusoida{
    double amplituda, frekvencija, faza_rad;
  public:
    Sinusoida(double a, double frekv, double faza);
    double DajAmplitudu() const {return amplituda;}
    double DajFrekvenciju() const {return frekvencija;}
    double DajFazu() const {return faza_rad;}
    std::tuple<double, double, double> DajParametre() const {return std::tuple<double, double, double>(amplituda,frekvencija, faza_rad);}
    Sinusoida &PostaviAmplitudu(double a);
    Sinusoida &PostaviFrekvenciju(double frekv);
    Sinusoida &PostaviFazu(double faza);
    Sinusoida &PostaviParametre(const std::tuple<double,double,double> &parametri);
    friend Sinusoida operator+(const Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida operator-(const Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida operator*(const Sinusoida &s1, const double &broj);
    friend Sinusoida operator*(const double &broj, const Sinusoida &s1);
    friend Sinusoida operator/(const Sinusoida &s1, const double &broj);
    Sinusoida &operator+=(const Sinusoida &s);
    Sinusoida &operator-=(const Sinusoida &s);
    Sinusoida &operator*=(const double &broj);
    Sinusoida &operator/=(const double &broj);
    friend Sinusoida operator-(const Sinusoida &s);
    double &operator[](const std::string &parametar);
    double operator[](const std::string &parametar)const;
    double operator()(double t)const;
};

Sinusoida::Sinusoida(double a, double frekv, double faza){
    PostaviParametre({a,frekv,faza});
}

Sinusoida & Sinusoida::PostaviAmplitudu(double a){
    if(a<0){
        a*=-1;
        Sinusoida::faza_rad+=(4*atan(1));
    }
    Sinusoida::amplituda=a;
    while (Sinusoida::faza_rad<-(4*atan(1))) Sinusoida::faza_rad+=2*(4*atan(1));
    while (Sinusoida::faza_rad>(4*atan(1))) Sinusoida::faza_rad-=2*(4*atan(1));
    return *this;
}

Sinusoida & Sinusoida::PostaviFrekvenciju(double frekv){
    if(frekv<0){
        frekv*=-1;
        Sinusoida::faza_rad*=-1;
        Sinusoida::faza_rad+=(4*atan(1));
    }
    Sinusoida::frekvencija=frekv;
    while (Sinusoida::faza_rad<-(4*atan(1))) Sinusoida::faza_rad+=2*(4*atan(1));
    while (Sinusoida::faza_rad>(4*atan(1))) Sinusoida::faza_rad-=2*(4*atan(1));
    return *this;
}

Sinusoida & Sinusoida::PostaviFazu(double faza){
    while (faza<-(4*atan(1))) faza+=2*(4*atan(1));
    while (faza>(4*atan(1))) faza-=2*(4*atan(1));
    Sinusoida::faza_rad=faza;
    return *this;
}

Sinusoida & Sinusoida::PostaviParametre(const std::tuple<double, double, double> &parametri){
    double a, frekv, faza;
    std::tie(a,frekv,faza)=parametri;
    PostaviFazu(faza);
    PostaviFrekvenciju(frekv);
    PostaviAmplitudu(a);
    return *this;
}

Sinusoida & Sinusoida::operator+=(const Sinusoida &s){
    if(std::fabs(s.DajFrekvenciju()-this->DajFrekvenciju())>0.0000000001) throw std::domain_error("Razlicite frekvencije");
    double nova_amplituda=std::sqrt(this->DajAmplitudu()*this->DajAmplitudu()+s.DajAmplitudu()*s.DajAmplitudu()+2*this->DajAmplitudu()*s.DajAmplitudu()*std::cos(s.DajFazu()-this->DajFazu()));
    double nova_faza=std::atan2((this->DajAmplitudu()*std::sin(this->DajFazu())+s.DajAmplitudu()*std::sin(s.DajFazu())),(this->DajAmplitudu()*std::cos(this->DajFazu())+s.DajAmplitudu()*std::cos(s.DajFazu())));
    this->PostaviParametre({nova_amplituda, frekvencija, nova_faza});
    return *this;
}

Sinusoida & Sinusoida::operator-=(const Sinusoida &s){
    if(std::fabs(s.DajFrekvenciju()-this->DajFrekvenciju())>0.0000000001) throw std::domain_error("Razlicite frekvencije");
    Sinusoida s1=s;
    s1=-s1;
    *this+=s1;
    return *this;
}

Sinusoida & Sinusoida::operator*=(const double &broj){
    this->PostaviAmplitudu(broj*this->DajAmplitudu());
    return *this;
}

Sinusoida & Sinusoida::operator/=(const double &broj){
    this->PostaviAmplitudu(this->DajAmplitudu()/broj);
    return *this;
}

Sinusoida operator-(const Sinusoida &s){
    Sinusoida s1=s;
    s1.PostaviParametre({-s1.amplituda, s1.frekvencija, s1.faza_rad});
    return s1;
}

Sinusoida operator+(const Sinusoida &s1, const Sinusoida &s2){
    Sinusoida s=s1;
    try{
        s+=s2;
    }
    catch(std::domain_error &izuzetak){
        throw izuzetak;
    }
    return s;
}

Sinusoida operator-(const Sinusoida &s1, const Sinusoida &s2){
    Sinusoida s=s1;
    try{
        s-=s2;
    }
    catch(std::domain_error &izuzetak){
        throw izuzetak;
    }
    return s;
}

Sinusoida operator*(const Sinusoida &s1, const double &broj){
    Sinusoida s=s1;
    //s*=broj;
    s.PostaviAmplitudu(s.DajAmplitudu()*broj);
    return s;
}

Sinusoida operator*(const double &broj, const Sinusoida &s1){
    Sinusoida s=s1;
    //s*=broj;
    s.PostaviAmplitudu(s.DajAmplitudu()*broj);
    return s;
}

Sinusoida operator/(const Sinusoida &s1, const double &broj){
    Sinusoida s=s1;
    //s/=broj;
    s.PostaviAmplitudu(s.DajAmplitudu()/broj);
    return s;
}

double & Sinusoida::operator[](const std::string &parametar){
    if(parametar=="A") return amplituda;
    else if(parametar=="omega" || parametar=="w") return frekvencija;
    else if(parametar=="fi" || parametar=="phi") return faza_rad;
    else throw std::domain_error("Neispravan naziv parametra");
}

double Sinusoida::operator[](const std::string &parametar)const{
    if(parametar=="A") return amplituda;
    else if(parametar=="omega" || parametar=="w") return frekvencija;
    else if(parametar=="fi" || parametar=="phi") return faza_rad;
    else throw std::domain_error("Neispravan naziv parametra");
}

double Sinusoida::operator()(double t)const{
    double rezultat= amplituda*sin(frekvencija*t+faza_rad);
    return rezultat;
}

int main (){
    Sinusoida s1(2,4*atan(1), 0);
    std::cout<<"s1 ima amplitudu "<<s1.DajAmplitudu()<<", frekvenciju "<<s1.DajFrekvenciju()<<" i fazu "<<s1.DajFazu()<<std::endl;
    Sinusoida s2(0,0,0);
    s2.PostaviParametre({4, 4*atan(1), 30});
    auto parametriS2=s2.DajParametre();
    std::cout<<"s2 ima amplitudu "<<std::get<0>(parametriS2)<<", frekvenciju "<<std::get<1>(parametriS2)<<" i fazu "<<std::get<2>(parametriS2)<<std::endl;
    Sinusoida s3=s1;
    s1.PostaviAmplitudu(3).PostaviFrekvenciju(4*atan(1)/60).PostaviFazu(60);
    std::cout<<"s3 ima amplitudu "<<s3.DajAmplitudu()<<", frekvenciju "<<s3.DajFrekvenciju()<<" i fazu "<<s3.DajFazu()<<std::endl;
    std::cout<<"s1 ima amplitudu "<<s1.DajAmplitudu()<<", frekvenciju "<<s1.DajFrekvenciju()<<" i fazu "<<s1.DajFazu()<<std::endl;
    try{
        Sinusoida s4=s1+s2;
        std::cout<<"s4 ima amplitudu "<<s4.DajAmplitudu()<<", frekvenciju "<<s4.DajFrekvenciju()<<" i fazu "<<s4.DajFazu()<<std::endl;
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    Sinusoida s5=s2;
    try{
        Sinusoida s4=s5+s2;
        std::cout<<"s4 ima amplitudu "<<s4.DajAmplitudu()<<", frekvenciju "<<s4.DajFrekvenciju()<<" i fazu "<<s4.DajFazu()<<std::endl;
        s4=s5-s2;
        std::cout<<"s4 ima amplitudu "<<s4.DajAmplitudu()<<", frekvenciju "<<s4.DajFrekvenciju()<<" i fazu "<<s4.DajFazu()<<std::endl;
        s4*=2;
        std::cout<<"s4 ima amplitudu "<<s4.DajAmplitudu()<<", frekvenciju "<<s4.DajFrekvenciju()<<" i fazu "<<s4.DajFazu()<<std::endl;
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    s5=-s3;
    std::cout<<"s5 ima amplitudu "<<s5.DajAmplitudu()<<", frekvenciju "<<s5.DajFrekvenciju()<<" i fazu "<<s5.DajFazu()<<std::endl;
    try{
        double faza=s5["fi"];
        std::cout<<"Faza s5 iznosi "<<faza<<std::endl;
        double frekvencija=s5["a"];
        std::cout<<"Frekvencija s5 iznosi "<<frekvencija<<std::endl;
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    std::cout<<"Vrijednost sinusne funkcije s2 u trenutku 2s je "<<s2(2)<<std::endl;
	return 0;
}
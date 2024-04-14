//TP 2022/2023: LV 10, Zadatak 4
#include <iostream>
#include <cmath>
#include <iomanip>

class Ugao{
    double ugaoRad;
  public:
    Ugao(double radijani = 0);
    Ugao(int stepeni, int minute, int sekunde);
    void Postavi(double radijani);
    void Postavi(int stepeni, int minute, int sekunde);
    double DajRadijane() const;
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)const;
    int DajStepene() const;
    int DajMinute() const;
    int DajSekunde() const;
    void Ispisi() const;
    void IspisiKlasicno() const;
    Ugao &SaberiSa(const Ugao &u);
    Ugao &PomnoziSa(double x);
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};
Ugao::Ugao(double radijani){
    Postavi(radijani);
}
Ugao::Ugao(int stepeni, int minute, int sekunde){
    Postavi(stepeni, minute, sekunde);
}
void Ugao::Postavi(double radijani){
    if(radijani<0) while(radijani<0) radijani+=2*4*atan(1);
    if(radijani>=2*4*atan(1)) while(radijani>=2*4*atan(1)) radijani-=2*4*atan(1);
    ugaoRad=radijani;
}
void Ugao::Postavi(int stepeni, int minute, int sekunde){
    double radijani = (stepeni + minute / 60.0 + sekunde / 3600.0) * 4*atan(1) / 180.0;
    Postavi(radijani);
}
double Ugao::DajRadijane() const{
    return ugaoRad;
}
void Ugao::OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde)const{
    double UgaoUStepenima=ugaoRad*180/(4*atan(1));
    if(UgaoUStepenima<0) while(UgaoUStepenima<0) UgaoUStepenima+=360;
    if(UgaoUStepenima>=360) while(UgaoUStepenima>=360) UgaoUStepenima-=360;
    stepeni=static_cast<int>(UgaoUStepenima);
    UgaoUStepenima-=stepeni; UgaoUStepenima*=60;
    minute=static_cast<int>(UgaoUStepenima);
    UgaoUStepenima-=minute; UgaoUStepenima*=60;
    sekunde=UgaoUStepenima;
}
int Ugao::DajStepene() const{
    int stepeni, minute, sekunde;
    OcitajKlasicneJedinice(stepeni, minute, sekunde);
    return stepeni;
}
int Ugao::DajMinute() const {
    int stepeni, minute, sekunde;
    OcitajKlasicneJedinice(stepeni, minute, sekunde);
    return minute;
}
int Ugao::DajSekunde() const {
    int stepeni, minute, sekunde;
    OcitajKlasicneJedinice(stepeni, minute, sekunde);
    return sekunde;
}
void Ugao::Ispisi() const {
    std::cout <<std::fixed<<std::setprecision(5)<<ugaoRad;
}
void Ugao::IspisiKlasicno() const {
    std::cout << DajStepene() << "deg " << DajMinute() << "min " << DajSekunde() << "sec";
}
Ugao& Ugao::SaberiSa(const Ugao& u) {
    *this=ugaoRad + u.ugaoRad;
    Postavi(this->ugaoRad);
    return *this;
}
Ugao& Ugao::PomnoziSa(double x) {
    this->ugaoRad*=x;
    Postavi(this->ugaoRad);
    return *this;
}

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
    double rezultat=u1.ugaoRad+u2.ugaoRad;
    return Ugao(rezultat);
}
Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
    double rezultat=u.ugaoRad*x;
    return Ugao(rezultat);
}

int main (){
    Ugao u(1, 30, 0);
    std::cout << "Ugao u: ";
    u.IspisiKlasicno();

    Ugao v(0.5);
    std::cout << "\nUgao v: ";
    v.Ispisi();

    Ugao zbir = ZbirUglova(u, v);
    std::cout << "\nZbir uglova u i v: ";
    zbir.Ispisi(); 

    Ugao produkt = ProduktUglaSaBrojem(u, 2);
    std::cout << "\nProdukt ugla u sa brojem 2: ";
    produkt.Ispisi(); 

    return 0;
}
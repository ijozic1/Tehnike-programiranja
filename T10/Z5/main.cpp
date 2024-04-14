//TP 2022/2023: LV 10, Zadatak 5
#include <iostream>
#include <cmath>
#include <iomanip>

class Ugao{
    int deg, min, s;
   public:
    Ugao(double radijani = 0);
    Ugao(int stepeni, int minute, int sekunde);
    void Postavi(double radijani);
    void Postavi(int stepeni, int minute, int sekunde);
    double DajRadijane() const;
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde);
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
Ugao::Ugao(double radijani) {
    Postavi(radijani);
}
Ugao::Ugao(int stepeni, int minute, int sekunde) {
    Postavi(stepeni, minute, sekunde);
}
void Ugao::Postavi(double radijani) {
    double stepeniDecimalno = radijani * 180.0 / (4*atan(1));
    int cjelobrojniStepeni = static_cast<int>(stepeniDecimalno);
    double decimalniDio = stepeniDecimalno - cjelobrojniStepeni;
    int cjelobrojneMinute = static_cast<int>(decimalniDio * 60);
    decimalniDio = (decimalniDio * 60) - cjelobrojneMinute;
    int cjelobrojneSekunde = static_cast<int>(decimalniDio * 60);

    Postavi(cjelobrojniStepeni, cjelobrojneMinute, cjelobrojneSekunde);
}
void Ugao::Postavi(int stepeni, int minute, int sekunde) {
    this->deg = stepeni; this->min = minute; this->s = sekunde;
    if (this->s < 0)
        while(this->s < 0){
            this->s += 60; this->min--;
        }
    if (this->s >= 60)
        while(this->s >= 60){
            this->s %= 60; this->min++;
        }
    if (this->min < 0)
        while(this->min < 0){
            this->min += 60; this->deg--;
        }
    if (this->min >= 60)
        while(this->min >= 60){
            this->min %= 60; this->deg++;
        }
    if (this->deg < 0) while(this->deg < 0) this->deg += 360;
    if (this->deg >= 360) while (this->deg < 0) this->deg %= 360;
}
double Ugao::DajRadijane() const {
    double decimalniStepeni = deg + min / 60.0 + s / 3600.0;
    return decimalniStepeni * (4*atan(1)) / 180.0;
}
void Ugao::OcitajKlasicneJedinice(int& stepeni, int& minute, int& sekunde) {
    stepeni = this->deg;
    minute = this->min;
    sekunde = this->s;
}
int Ugao::DajStepene() const {
    return deg;
}
int Ugao::DajMinute() const {
    return min;
}
int Ugao::DajSekunde() const {
    return s;
}
void Ugao::Ispisi() const {
    std::cout << std::fixed << std::setprecision(5) << DajRadijane();
}
void Ugao::IspisiKlasicno() const {
    std::cout << deg << "deg " << min << "min " << s << "sec";
}
Ugao& Ugao::SaberiSa(const Ugao& u) {
    int sumaSekundi = s + u.s;
    int novaSekunda = sumaSekundi % 60;
    int prenosSekunde = sumaSekundi / 60;

    int sumaMinuta = min + u.min + prenosSekunde;
    int novaMinuta = sumaMinuta % 60;
    int prenosMinute = sumaMinuta / 60;

    int noviStepeni = deg + u.deg + prenosMinute;

    Postavi(noviStepeni, novaMinuta, novaSekunda);
    return *this;
}
Ugao& Ugao::PomnoziSa(double x) {
    double radijani = DajRadijane();
    radijani *= x;
    Postavi(radijani);
    return *this;
}
Ugao ZbirUglova(const Ugao& u1, const Ugao& u2) {
    Ugao rezultat;
    rezultat.SaberiSa(u1);
    rezultat.SaberiSa(u2);
    return rezultat;
}
Ugao ProduktUglaSaBrojem(const Ugao& u, double x) {
    Ugao rezultat;
    rezultat = u;
    rezultat.PomnoziSa(x);
    return rezultat;
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
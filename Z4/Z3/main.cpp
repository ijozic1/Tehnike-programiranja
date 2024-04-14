//TP 2022/2023: Zadaća 4, Zadatak 3
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

//Jedan polazak
class Polazak{
    std::string nazivOdredista, oznakaVoznje;
    int brojPerona, satPolaska, minutePolaska, trajanjeVoznjeMin, kasnjenjeAutobusa;
  public:
    Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje);
    void PostaviKasnjenje(int kasnjenje);
    bool DaLiKasni() const;
    int DajTrajanje() const;
    void OcekivanoVrijemePolaska(int &sati, int &minute) const;
    void OcekivanoVrijemeDolaska(int &sati, int &minute) const;
    void Ispisi() const;
};

//Svi polasci u danu
class Polasci{
    Polazak** polasci{};
    int broj_polazaka;
    const int max_br_polazaka;
  public:
    explicit Polasci(int max_broj_polazaka);
    Polasci(std::initializer_list<Polazak> lista_polazaka);
    ~Polasci();
    Polasci(const Polasci &polasci);
    Polasci(Polasci &&polasci);
    Polasci &operator =(const Polasci &polasci);
    Polasci &operator =(Polasci &&polasci);
    void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje);
    void RegistrirajPolazak(Polazak *polazak);
    int DajBrojPolazaka() const;
    int DajBrojPolazakaKojiKasne() const;
    Polazak &DajPrviPolazak();
    Polazak DajPrviPolazak() const;
    Polazak &DajPosljednjiPolazak();
    Polazak DajPosljednjiPolazak() const;
    void Ispisi() const;
    void IsprazniKolekciju();
};

Polazak::Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
    if(broj_perona<1 || broj_perona>15) throw std::domain_error("Neipsravan broj perona");
    if(sat_polaska<0 || sat_polaska>23) throw std::domain_error("Neispravno vrijeme polaska (h)");
    if(minute_polaska<0 || minute_polaska>59) throw std::domain_error("Neispravno vrijeme polaska (min)");
    if(trajanje_voznje<0) throw std::domain_error("Neipravno trajanje voznje");
    Polazak::brojPerona=broj_perona; Polazak::satPolaska=sat_polaska; Polazak::minutePolaska=minute_polaska;
    Polazak::nazivOdredista=odrediste; Polazak::oznakaVoznje=oznaka_voznje; Polazak::trajanjeVoznjeMin=trajanje_voznje; Polazak::kasnjenjeAutobusa=0;
}

void Polazak::PostaviKasnjenje(int kasnjenje){
    if(kasnjenje<0) throw std::logic_error("Neregularno vrijeme kasnjenja");
    Polazak::kasnjenjeAutobusa=kasnjenje;
}

bool Polazak::DaLiKasni() const{
    if(kasnjenjeAutobusa>0) return true;
    return false;
}

int Polazak::DajTrajanje() const{
    return trajanjeVoznjeMin;
}

void Polazak::OcekivanoVrijemeDolaska(int &sati, int &minute) const{
    if(kasnjenjeAutobusa>0){
        int kasnjenjeUSatima=kasnjenjeAutobusa/60;
        int kasnjenjeUMinutama=kasnjenjeAutobusa%60;
        sati=satPolaska+kasnjenjeUSatima+trajanjeVoznjeMin/60;
        minute=minutePolaska+kasnjenjeUMinutama+trajanjeVoznjeMin%60;
    }
    else{
        sati=satPolaska+trajanjeVoznjeMin/60;
        minute=minutePolaska+trajanjeVoznjeMin%60;
    }
    if(minute>59){
        sati+=(minute/60);
        minute%=60;
    }
    if(sati>23) sati%=24;
}

void Polazak::OcekivanoVrijemePolaska(int &sati, int &minute) const{
    if(kasnjenjeAutobusa>0){
        int kasnjenjeUsatima=kasnjenjeAutobusa/60;
        int kasnjenjeUMinutama=kasnjenjeAutobusa%60;
        sati=satPolaska+kasnjenjeUsatima;
        minute=minutePolaska+kasnjenjeUMinutama;
    }
    else{
        sati=satPolaska; minute=minutePolaska;
    }
    if(minute>59){
        sati+=(minute/60);
        minute%=60;
    }
    if(sati>23) sati%=24;
}

void Polazak::Ispisi() const{
    int hPolaska, minPolaska, hDolazak, minDolazak;
    OcekivanoVrijemePolaska(hPolaska, minPolaska);
    OcekivanoVrijemeDolaska(hDolazak, minDolazak);
    std::string vrijeme_polaska(std::to_string(hPolaska)+":"+std::to_string(minPolaska/10)+std::to_string(minPolaska%10));
    std::string vrijeme_dolaska(std::to_string(hDolazak)+":"+std::to_string(minDolazak/10)+std::to_string(minDolazak%10));
    std::cout<<std::setw(10)<<std::left<<oznakaVoznje<<std::setw(30)<<std::left<<nazivOdredista;
    if(!DaLiKasni())
        std::cout<<std::right<<std::setw(10)<<vrijeme_polaska<<std::setw(10)<<vrijeme_dolaska<<std::setw(8)<<std::setfill(' ')<<brojPerona<<std::endl;
    else{
        std::cout<<std::right<<std::setw(10)<<vrijeme_polaska;
        std::cout<<" (Planirano "<<satPolaska<<":"<<minutePolaska/10<<minutePolaska%10<<", Kasni "<<kasnjenjeAutobusa<<" min)"<<std::endl;
    }
}

Polasci::Polasci(int max_broj_polazaka) : max_br_polazaka(max_broj_polazaka), broj_polazaka(){
    polasci=new Polazak*[max_br_polazaka]{};
}

Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka) : max_br_polazaka(lista_polazaka.size()), broj_polazaka(){
    polasci=new Polazak*[max_br_polazaka]{};
    auto it=lista_polazaka.begin();
    for(int i=0; i!=lista_polazaka.size(); i++){
        try{
            this->polasci[i]=new Polazak(*it);
            it++;
            broj_polazaka++;
        }
        catch(...){
            std::for_each(polasci, polasci+broj_polazaka, [](Polazak *p){delete p;});
            delete[] polasci; polasci=nullptr;
            throw;
        }
    }
}

Polasci::~Polasci(){
    std::for_each(polasci, polasci+broj_polazaka, [](Polazak *p){delete p;});
    delete[] polasci; polasci=nullptr;
}

Polasci::Polasci(const Polasci &p) : max_br_polazaka(p.max_br_polazaka), broj_polazaka(p.broj_polazaka), polasci(new Polazak*[p.max_br_polazaka]){
    try{
        for(int i=0; i<broj_polazaka; i++) polasci[i]=new Polazak(*p.polasci[i]);
    }
    catch(...){
        for(int i=0; i<broj_polazaka; i++) delete polasci[i];
        delete[] polasci;
        throw;
    }
}

Polasci::Polasci(Polasci &&p) : broj_polazaka(p.broj_polazaka), max_br_polazaka(p.max_br_polazaka){
    p.broj_polazaka=0;
    p.polasci=nullptr;
}

Polasci & Polasci::operator=(const Polasci &p){
    if(p.max_br_polazaka!=max_br_polazaka) throw std::range_error("Nesaglasni kapaciteti");
    if(p.broj_polazaka>broj_polazaka){
        try{
            for(int i=broj_polazaka; i<p.broj_polazaka; i++) polasci[i]=new Polazak(*p.polasci[i]);
        }
        catch(...){
            for(int i=broj_polazaka; i<p.broj_polazaka; i++){
                delete polasci[i]; polasci[i]=nullptr;
            }
            throw;
        }
    }
    else{
        for(int i=p.broj_polazaka; i<broj_polazaka; i++){
            delete polasci[i]; polasci[i]=nullptr;
        }
    }
    broj_polazaka=p.broj_polazaka;
    for(int i=0; i<broj_polazaka; i++) *polasci[i]=*p.polasci[i];
    return *this;
}

Polasci & Polasci::operator=(Polasci &&p){
    if(p.max_br_polazaka!=max_br_polazaka) throw std::range_error("Nesaglasni kapaciteti");
    std::swap(broj_polazaka, p.broj_polazaka);
    std::swap(polasci, p.polasci);
    return *this;
}

void Polasci::RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
    if(broj_polazaka>=max_br_polazaka) throw std::range_error("Dostignut maksimalan broj polazaka");
    polasci[broj_polazaka]=new Polazak(odrediste, oznaka_voznje, broj_perona, sat_polaska, minute_polaska, trajanje_voznje);
    broj_polazaka++;
}

void Polasci::RegistrirajPolazak(Polazak *polazak){
    if(broj_polazaka>=max_br_polazaka) throw std::range_error("Dostignut maksimalan broj polazaka");
    polasci[broj_polazaka]=new Polazak(*polazak);
    broj_polazaka++;
    delete polazak;
}

int Polasci::DajBrojPolazaka() const{
    return broj_polazaka;
}
int Polasci::DajBrojPolazakaKojiKasne() const{
    return std::count_if(polasci, polasci+broj_polazaka, [](Polazak *p){
        return p->DaLiKasni();
    });
}

Polazak & Polasci::DajPrviPolazak(){
    auto it=std::min_element(polasci, polasci+broj_polazaka, [](Polazak *p1, Polazak *p2){
        int sat1, sat2, minute1, minute2;
        p1->OcekivanoVrijemePolaska(sat1, minute1);
        p2->OcekivanoVrijemePolaska(sat2, minute2);
        if(sat1!=sat2) return sat1<sat2;
        return minute1<minute2;
    });
    return **it;
}
Polazak Polasci::DajPrviPolazak() const{
    auto it=std::min_element(polasci, polasci+broj_polazaka, [](Polazak *p1, Polazak *p2){
        int sat1, sat2, minute1, minute2;
        p1->OcekivanoVrijemePolaska(sat1, minute1);
        p2->OcekivanoVrijemePolaska(sat2, minute2);
        if(sat1!=sat2) return sat1<sat2;
        return minute1<minute2;
    });
    return **it;
}
Polazak & Polasci::DajPosljednjiPolazak(){
    auto it=std::max_element(polasci, polasci+broj_polazaka, [](Polazak *p1, Polazak *p2){
        int sat1, sat2, minute1, minute2;
        p1->OcekivanoVrijemePolaska(sat1, minute1);
        p2->OcekivanoVrijemePolaska(sat2, minute2);
        if(sat1!=sat2) return sat1<sat2;
        return minute1<minute2;
    });
    return **it;
}
Polazak Polasci::DajPosljednjiPolazak() const{
    auto it=std::max_element(polasci, polasci+broj_polazaka, [](Polazak *p1, Polazak *p2){
        int sat1, sat2, minute1, minute2;
        p1->OcekivanoVrijemePolaska(sat1, minute1);
        p2->OcekivanoVrijemePolaska(sat2, minute2);
        if(sat1!=sat2) return sat1<sat2;
        return minute1<minute2;
    });
    return **it;
}

void Polasci::Ispisi() const{
    std::sort(polasci, polasci+broj_polazaka, [](const Polazak *polazak1, const Polazak *polazak2){
        int sat1, sat2, minute1, minute2;
        polazak1->OcekivanoVrijemePolaska(sat1, minute1);
        polazak2->OcekivanoVrijemePolaska(sat2, minute2);
        if(sat1!=sat2) return sat1<sat2;
        return minute1<minute2;
    });
    std::cout<<"Voznja                     Odrediste   Polazak   Dolazak   Peron"<<std::endl<<"----------------------------------------------------------------------"<<std::endl;
    std::for_each(polasci, polasci+broj_polazaka, [](const Polazak *polazak){polazak->Ispisi();});
}

void Polasci::IsprazniKolekciju(){
    std::for_each(polasci, polasci+broj_polazaka, [](Polazak *p){delete p;});
    delete[] polasci;
    polasci=nullptr;
}

int main (){
    try{
        Polasci p(5);
        p.RegistrirajPolazak("Sarajevo", "ABCD", 3, 12, 20, 30);
        p.RegistrirajPolazak("Mostar", "ADE", 2, 8, 15, 120);
        p.RegistrirajPolazak("Bihać", "BCD", 1, 15, 0, 300);
        p.Ispisi();
        std::cout<<std::endl;
        Polazak &polazak=p.DajPrviPolazak();
        polazak.PostaviKasnjenje(15);
        p.Ispisi();
        std::cout<<std::endl;
        Polazak &p1=p.DajPosljednjiPolazak();
        p1.PostaviKasnjenje(60);
        p.Ispisi();
    }
    catch(...){
        std::cout<<"Doslo je do greske";
    }
	return 0;
}
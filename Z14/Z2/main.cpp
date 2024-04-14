//TP 2022/2023: LV 14, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

class Spremnik{
  public:
    virtual Spremnik *DajKopiju() const=0;
    virtual double DajTezinu() const=0;
    virtual double DajUkupnuTezinu() const =0;
    virtual void Ispisi() const=0;
    virtual ~Spremnik(){}
};

class Sanduk:public Spremnik{
    double vlastitaTezina, tezinaPredmeta;
    std::string nazivPredmeta;
    int brojPredmeta;
  public:
    Sanduk(double vlTezina, const std::string &nazivPred, int brojPred, double tezPred):
        vlastitaTezina(vlTezina), tezinaPredmeta(tezPred), nazivPredmeta(nazivPred), brojPredmeta(brojPred){}
    Spremnik *DajKopiju() const override {return new Sanduk(*this);}
    double DajTezinu() const override {return vlastitaTezina;}
    double DajUkupnuTezinu() const override {return vlastitaTezina+brojPredmeta*tezinaPredmeta;}
    void Ispisi() const override;
};

class Bure : public Spremnik{
    double vlastitaTezina, tezinaTecnosti;
    std::string nazivTecnosti;
  public:
    Bure(double vlTezina, const std::string &nazivTec, double tezTec):
        vlastitaTezina(vlTezina), tezinaTecnosti(tezTec), nazivTecnosti(nazivTec){}
    Spremnik *DajKopiju() const override {return new Bure(*this);}
    double DajTezinu() const override {return vlastitaTezina;}
    double DajUkupnuTezinu() const override {return vlastitaTezina+tezinaTecnosti;}
    void Ispisi() const override;
};

class Skladiste{
    int brojPredmeta, kapacitet;
    Spremnik **spremnici;
  public:
    explicit Skladiste(int kapacitet):brojPredmeta(), kapacitet(kapacitet), spremnici(new Spremnik*[kapacitet]{}){}
    ~Skladiste(){
        for(int i=0; i<brojPredmeta; i++) delete spremnici[i];
        delete[] spremnici;
    }
    Skladiste (const Skladiste &s);
    Skladiste (Skladiste &&s);
    Skladiste &operator=(const Skladiste &s);
    Skladiste &operator=(Skladiste &&s);
    void DodajSpremnik(Spremnik*s);
    void DodajBure(double vlTezina, const std::string &nazivTec, double tezTec){DodajSpremnik(new Bure(vlTezina, nazivTec, tezTec));}
    void DodajSanduk(double vlTezina, const std::string &nazivPred, int brojPred, double tezPred){DodajSpremnik(new Sanduk(vlTezina, nazivPred, brojPred, tezPred));}
    Spremnik &DajNajlaksi();
    Spremnik &DajNajtezi();
    int BrojPreteskih(int iznos) const;
    void IzlistajSkladiste() const;
    void UcitajIzDatoteke(const std::string &imeDatoteke);
};

void Sanduk::Ispisi() const{
    std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
    std::cout<<"Sadrzaj: "<<nazivPredmeta<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}

void Bure::Ispisi() const{
    std::cout<<"Vrsta spremnika: Bure"<<std::endl;
    std::cout<<"Sadrzaj: "<<nazivTecnosti<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}

Skladiste::Skladiste(const Skladiste &s): spremnici(new Spremnik*[s.kapacitet]{}), kapacitet(s.kapacitet), brojPredmeta(s.brojPredmeta){
    try{
        for(int i=0; i<brojPredmeta; i++) spremnici[i]=s.spremnici[i]->DajKopiju();
    }
    catch(...){
        for(int i=0; i<brojPredmeta; i++) delete spremnici[i];
        delete[] spremnici;
        throw;
    }
}

Skladiste:: Skladiste(Skladiste &&s): spremnici(s.spremnici), kapacitet(s.kapacitet), brojPredmeta(s.brojPredmeta){
    s.spremnici=nullptr; s.brojPredmeta=0;
}

Skladiste & Skladiste::operator=(const Skladiste &s){
    Spremnik ** novi=new Spremnik*[s.kapacitet]{};
    try{
        for(int i=0; i<s.brojPredmeta; i++) novi[i]=s.spremnici[i]->DajKopiju();
    }
    catch(...){
        for(int i=0; i<s.brojPredmeta; i++) delete novi[i];
        delete[] novi;
        throw;
    }
    for(int i=0; i<brojPredmeta; i++) delete spremnici[i];
    delete[] spremnici;
    spremnici=novi; kapacitet=s.kapacitet; brojPredmeta=s.brojPredmeta;
    return *this;
}

Skladiste & Skladiste::operator=(Skladiste &&s){
    std::swap(kapacitet, s.kapacitet);
    std::swap(spremnici, s.spremnici);
    std::swap(brojPredmeta, s.brojPredmeta);
    return *this;
}

void Skladiste::DodajSpremnik(Spremnik *s){
    if(brojPredmeta>=kapacitet){ 
        delete s;
        throw std::domain_error("Popunjeno skladiste");
    }
    spremnici[brojPredmeta++]=s;
}

Spremnik & Skladiste::DajNajlaksi(){
    if(spremnici==nullptr) throw std::range_error("Skladiste je prazno"); //ovdje probaj brojPredmeta==0
    auto najlaksi=std::min_element(spremnici, spremnici+brojPredmeta, [](Spremnik *s1, Spremnik *s2){
        return s1->DajTezinu()<s2->DajTezinu();
    });
    return **najlaksi;
}

Spremnik & Skladiste::DajNajtezi(){
    if(spremnici==nullptr) throw std::range_error("Skladiste je prazno"); //ovdje probaj brojPredmeta==0
    auto najtezi=std::max_element(spremnici, spremnici+brojPredmeta, [](Spremnik *s1, Spremnik *s2){
        return s1->DajTezinu()<s2->DajTezinu();
    });
    return **najtezi;
}

int Skladiste::BrojPreteskih(int iznos) const{
    return std::count_if(spremnici, spremnici+brojPredmeta, [&iznos](Spremnik *s){
        return s->DajUkupnuTezinu()>iznos;
    });
}

void Skladiste::IzlistajSkladiste() const{
    if(spremnici==nullptr) return;
    Spremnik **kopija=new Spremnik*[brojPredmeta];
    std::copy(spremnici, spremnici+brojPredmeta,kopija);
    std::sort(kopija, kopija+brojPredmeta,[](Spremnik*s1, Spremnik *s2){
        return s1->DajUkupnuTezinu() > s2->DajUkupnuTezinu();
    });
    for(int i=0; i<brojPredmeta; i++) kopija[i]->Ispisi();
    delete[] kopija;
}

void Skladiste::UcitajIzDatoteke(const std::string &imeDatoteke){
    std::ifstream ulazni_tok(imeDatoteke);
    if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
    for(int i=0; i<brojPredmeta; i++) delete spremnici[i];
    brojPredmeta=0;
    std::string redDatoteke;
    std::string tip;
    while (ulazni_tok >> tip) {
        std::string naziv;
        double tezinaS, tezinaP;
        int brPredmeta;
        if (!(ulazni_tok >> naziv)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
        if (tip == "S") {
            std::getline(ulazni_tok, redDatoteke);
            if (!(ulazni_tok >> tezinaS >> brPredmeta >> tezinaP)) 
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            if (brojPredmeta >= kapacitet)
                throw std::domain_error("Popunjeno skladiste");

            spremnici[brojPredmeta++] = new Sanduk(tezinaS, naziv, brPredmeta, tezinaP);
        } 
        else if (tip == "B") {
            if (!(ulazni_tok >> tezinaS >> tezinaP))
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            if (brojPredmeta >= kapacitet)
                throw std::domain_error("Popunjeno skladiste");
            spremnici[brojPredmeta++] = new Bure(tezinaS, naziv, tezinaP);
        } 
        else throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
    ulazni_tok.close();
}

int main (){
    Skladiste skladiste(10);
    try{
        skladiste.UcitajIzDatoteke("ROBA.TXT");
        skladiste.IzlistajSkladiste();
    }
    catch(std::exception &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}

//TP 2022/2023: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class ApstraktnoVozilo{
    int vlastitaTezinaVozila;
   public:
    ApstraktnoVozilo(int tezina): vlastitaTezinaVozila(tezina){}
    virtual ~ApstraktnoVozilo(){}
    int DajTezinu() const {return vlastitaTezinaVozila;}
    virtual int DajUkupnuTezinu() const=0;
    virtual ApstraktnoVozilo *DajKopiju() const =0;
    virtual void IspisiPodatke() const=0;
};

class Automobil : public ApstraktnoVozilo{
    std::vector<int> tezinaPutnika;
   public:
    Automobil(int tezinaAutomobila, std::vector<int>tezinePutn): ApstraktnoVozilo(tezinaAutomobila), tezinaPutnika(std::move(tezinePutn)){}
    int DajUkupnuTezinu() const override;
    ApstraktnoVozilo *DajKopiju() const override {return new Automobil(*this);}
    void IspisiPodatke() const override;
};

class Kamion : public ApstraktnoVozilo{
    int tezinaTereta;
  public:
    Kamion (int tezinaKamiona, int tezinaTer): ApstraktnoVozilo(tezinaKamiona), tezinaTereta(tezinaTer){}
    int DajUkupnuTezinu() const override;
    ApstraktnoVozilo *DajKopiju() const override {return new Kamion(*this);}
    void IspisiPodatke() const override;
};

class Autobus : public ApstraktnoVozilo{
    int brojPutnika, prosjecnaTezinaPutnika;
  public:
    Autobus(int tezinaAutobusa, int brPutnika, int prosjTezina): ApstraktnoVozilo(tezinaAutobusa), brojPutnika(brPutnika), prosjecnaTezinaPutnika(prosjTezina){}
    int DajUkupnuTezinu() const override;
    ApstraktnoVozilo *DajKopiju() const override {return new Autobus(*this);}
    void IspisiPodatke() const override;
};

class Vozilo{
    ApstraktnoVozilo *vozilo;
  public:
    Vozilo() : vozilo(nullptr){}
    ~Vozilo() {delete vozilo;}
    Vozilo(const ApstraktnoVozilo &v) : vozilo(v.DajKopiju()) {}
    Vozilo (const Vozilo &v);
    Vozilo (Vozilo &&v){ vozilo=v.vozilo; v.vozilo=nullptr;}
    Vozilo &operator=(const Vozilo &v);
    Vozilo &operator=(Vozilo &&v);
    int DajUkupnuTezinu() const;
    void IspisiPodatke() const;
};

int Automobil::DajUkupnuTezinu()const{
    int tezina=0;
    for(int i=0; i<tezinaPutnika.size(); i++) tezina+=tezinaPutnika[i];
    return tezina+DajTezinu();
}

void Automobil::IspisiPodatke()const{
    std::cout<<"Vrsta vozila: Automobil"<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" kg\nTezine putnika: ";
    for(int i=0; i<tezinaPutnika.size(); i++){
        std::cout<<tezinaPutnika[i]<<" kg";
        if(i!=tezinaPutnika.size()-1) std::cout<<", ";
    }
    std::cout<<std::endl<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}

int Kamion::DajUkupnuTezinu()const{
    return tezinaTereta+DajTezinu();
}

void Kamion::IspisiPodatke()const{
    std::cout<<"Vrsta vozila: Kamion"<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" kg\nTezina tereta: "<<tezinaTereta<<" kg\nUkupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}

int Autobus::DajUkupnuTezinu()const{
    return brojPutnika*prosjecnaTezinaPutnika+DajTezinu();
}

void Autobus::IspisiPodatke()const{
    std::cout<<"Vrsta vozila: Autobus"<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" kg\nBroj putnika: "<<brojPutnika<<"\nProsjecna tezina putnika: "<<prosjecnaTezinaPutnika<<" kg\nUkupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}

Vozilo:: Vozilo (const Vozilo &v){
    if(!v.vozilo) vozilo=nullptr;
    else vozilo=v.vozilo->DajKopiju();
}

Vozilo & Vozilo::operator=(const Vozilo &v){
    ApstraktnoVozilo *novi=nullptr;
    if(v.vozilo!=nullptr) novi=v.vozilo->DajKopiju();
    delete v.vozilo;
    vozilo=novi;
    return *this;
}
    
Vozilo & Vozilo::operator=(Vozilo &&v){
    std::swap(vozilo, v.vozilo);
    return *this;
}
    
int Vozilo::DajUkupnuTezinu() const{
    if(!vozilo) throw std::logic_error("Nespecificiran lik");
    return vozilo->DajUkupnuTezinu();
}

void Vozilo::IspisiPodatke() const{
    if(!vozilo) throw std::logic_error("Nespecificiran lik");
    return vozilo->IspisiPodatke();
}

int main (){
    try{
        std::vector<Vozilo/***/> vozila;
        std::ifstream ulazni_tok("VOZILA.TXT");
        if(!ulazni_tok) throw std::logic_error("Otvaranje datoteke nije uspjelo!");
        std::string redDatoteke;
        while(std::getline(ulazni_tok, redDatoteke)){
            if(redDatoteke[0]=='A'){
                redDatoteke=redDatoteke.substr(1);
                int tezina=0, brPut=0;
                std::vector<int> tputnici;
                std::istringstream pomocni(redDatoteke);
                pomocni>>tezina>>brPut;
                for(int i=0; i<brPut; i++){
                    int putnik=0;
                    pomocni>>putnik;
                    tputnici.push_back(putnik);
                }
                /*std::cout<<tezina<<std::endl<<brPut<<std::endl;
                for(int i=0; i<brPut; i++) std::cout<<tputnici[i]<<" ";*/
                vozila.emplace_back(/*new*/Automobil(tezina, tputnici));
            }
            else if(redDatoteke[0]=='K'){
                redDatoteke=redDatoteke.substr(1);
                int tezina=0, teret=0;
                std::istringstream pomocni(redDatoteke);
                pomocni>>tezina>>teret;
                //std::cout<<std::endl<<tezina<<std::endl<<teret<<std::endl;
                vozila.emplace_back(/*new*/Kamion(tezina,teret));
            }
            else if(redDatoteke[0]=='B'){
                redDatoteke=redDatoteke.substr(1);
                int tezina=0, brPut=0, prosjT=0;
                std::istringstream pomocni(redDatoteke);
                pomocni>>tezina>>brPut>>prosjT;
                //std::cout<<std::endl<<tezina<<std::endl<<brPut<<std::endl<<prosjT<<std::endl<<std::endl;
                vozila.emplace_back(/*new*/Autobus(tezina,brPut, prosjT));
            }
            else throw std::logic_error("NEPOSTOJECE VOZILO!");
        }
        ulazni_tok.close();
        std::sort(vozila.begin(), vozila.end(), [](Vozilo /***/v1, Vozilo /***/v2){
            return v1./*->*/DajUkupnuTezinu()<v2./*->*/DajUkupnuTezinu();
        });
        for(Vozilo /***/v : vozila) std::cout<<v./*->*/DajUkupnuTezinu()<<std::endl;
        //for(Vozilo v : vozila) delete v;
    }
    catch(std::exception &izuzetak){
        std::cout<<"Izuzetak: "<<izuzetak.what()<<std::endl;
    }
	return 0;
}

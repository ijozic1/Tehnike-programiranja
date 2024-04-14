//TP 2022/2023: Zadaća 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <vector>
#include <memory>
#include <iomanip>

class NepreklapajuciKrug{
    double poluprecnikKruga;
    std::pair<double, double> koordinateCentra;
    static NepreklapajuciKrug *posljednjiKrug;
    NepreklapajuciKrug *prethodniKrug;
    void DodajKrug();
    void UkloniKrug();
    static bool Priblizno(double x, double y){
        return (std::fabs(x-y)<=10e-10*(std::fabs(x)+std::fabs(y)));
    }
    bool DaLiSePreklapaju(const NepreklapajuciKrug &k, NepreklapajuciKrug *pok) const;

   public:
    explicit NepreklapajuciKrug(double poluprecnik = 0){
        if(poluprecnik <0) throw std::domain_error("Nedozvoljen poluprecnik");
        poluprecnikKruga=poluprecnik;
        koordinateCentra.first=0; koordinateCentra.second=0;
        prethodniKrug=nullptr;
        //if(posljednjiKrug!=nullptr) throw std::logic_error("Nedozvoljeno preklapanje");
        if(DaLiSePreklapaju(*this, this)) throw std::logic_error("Nedozvoljeno preklapanje");
        DodajKrug();
    }
    explicit NepreklapajuciKrug(const std::pair<double, double> &centar, double poluprecnik = 0){
        if(poluprecnik<0) throw std::domain_error("Nedozvoljen poluprecnik");
        poluprecnikKruga=poluprecnik;
        koordinateCentra.first=centar.first;
        koordinateCentra.second=centar.second;
        prethodniKrug=nullptr;
        //if(posljednjiKrug!=nullptr) throw std::logic_error("Nedozvoljeno preklapanje");
        if(DaLiSePreklapaju(*this, this)){ 
            throw std::logic_error("Nedozvoljeno preklapanje");
            this->UkloniKrug();
        }
        DodajKrug();
    }
    ~NepreklapajuciKrug(){UkloniKrug();}
    NepreklapajuciKrug(const NepreklapajuciKrug &)=delete;
    NepreklapajuciKrug &operator=(const NepreklapajuciKrug &)=delete;
    std::pair<double, double> DajCentar() const{return koordinateCentra;}
    double DajPoluprecnik() const{return poluprecnikKruga;}
    double DajObim() const{return 2*poluprecnikKruga*4*atan(1);}
    double DajPovrsinu() const{return poluprecnikKruga*poluprecnikKruga*4*atan(1);}
    NepreklapajuciKrug &PostaviCentar(const std::pair<double, double> &centar);
    NepreklapajuciKrug &PostaviPoluprecnik(double poluprecnik);
    NepreklapajuciKrug &Transliraj(double delta_x, double delta_y);
    NepreklapajuciKrug &Rotiraj(double alpha);
    NepreklapajuciKrug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
    void Ispisi() const;
    static double RastojanjeCentara(const NepreklapajuciKrug &k1, const NepreklapajuciKrug &k2);
};
NepreklapajuciKrug* NepreklapajuciKrug::posljednjiKrug=nullptr;

bool NepreklapajuciKrug::DaLiSePreklapaju(const NepreklapajuciKrug &k, NepreklapajuciKrug *pok) const{
    auto p=posljednjiKrug;
    while(p!=nullptr){
        if(RastojanjeCentara(k, *p)<k.DajPoluprecnik()+p->DajPoluprecnik() && p!=pok) return true;
        if(Priblizno(RastojanjeCentara(k, *p), k.DajPoluprecnik()+(p->DajPoluprecnik())) && p!=pok) return true;
        p=p->prethodniKrug;
    }
    return false;
}

NepreklapajuciKrug & NepreklapajuciKrug::PostaviCentar(const std::pair<double, double> &centar){
    auto temp=this->koordinateCentra;
    this->koordinateCentra=centar;
    if(DaLiSePreklapaju(*this, this)){
        this->koordinateCentra=temp;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
}

NepreklapajuciKrug & NepreklapajuciKrug::PostaviPoluprecnik(double poluprecnik){
    if(poluprecnik<0) throw std::domain_error("Nedozvoljen poluprecnik");
    auto temp=this->poluprecnikKruga;
    this->poluprecnikKruga=poluprecnik;
    if(DaLiSePreklapaju(*this,this)){
        this->poluprecnikKruga=temp;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
}

void NepreklapajuciKrug::DodajKrug(){
    prethodniKrug=posljednjiKrug;
    posljednjiKrug=this;
}

void NepreklapajuciKrug::UkloniKrug(){
    if(prethodniKrug!=nullptr) prethodniKrug->posljednjiKrug=posljednjiKrug;
    else posljednjiKrug=nullptr;
}

void NepreklapajuciKrug::Ispisi() const{
    std::cout<<"{("<<koordinateCentra.first<<","<<koordinateCentra.second<<"),"<<DajPoluprecnik()<<"}";
    std::cout<<std::endl;
}

double NepreklapajuciKrug::RastojanjeCentara(const NepreklapajuciKrug &k1, const NepreklapajuciKrug &k2){
    return std::sqrt((k1.koordinateCentra.first-k2.koordinateCentra.first)*(k1.koordinateCentra.first-k2.koordinateCentra.first)+
            (k1.koordinateCentra.second-k2.koordinateCentra.second)*(k1.koordinateCentra.second-k2.koordinateCentra.second));
}

NepreklapajuciKrug & NepreklapajuciKrug::Transliraj(double delta_x, double delta_y){
    PostaviCentar({koordinateCentra.first+delta_x, koordinateCentra.second+delta_y});
    PostaviPoluprecnik(this->poluprecnikKruga);
    if(DaLiSePreklapaju(*this, this)) UkloniKrug();
    return *this;
}

NepreklapajuciKrug & NepreklapajuciKrug::Rotiraj(double alpha){
    //(xc,yc)=(0,0)
    alpha*=4*atan(1)/180;
    auto c=this->DajCentar();
    this->koordinateCentra.first=c.first*cos(alpha)-c.second*sin(alpha);
    this->koordinateCentra.second=c.first*sin(alpha)+c.second*cos(alpha);
    if(DaLiSePreklapaju(*this, this)){ 
        this->koordinateCentra=c;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
}

NepreklapajuciKrug & NepreklapajuciKrug::Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha){
    alpha*=4*atan(1)/180;
    PostaviCentar({centar_rotacije.first+(koordinateCentra.first-centar_rotacije.first)*cos(alpha)-(koordinateCentra.second-centar_rotacije.second)*sin(alpha), 
                centar_rotacije.second+(koordinateCentra.first-centar_rotacije.first)*sin(alpha)+(koordinateCentra.second - centar_rotacije.second)*cos(alpha)});
    PostaviPoluprecnik(this->poluprecnikKruga);
    if(DaLiSePreklapaju(*this, this)){
        UkloniKrug();
        throw std::logic_error("Nedozvoljeno preklapanje");
    }    
    return *this;
}

bool Jednako(double x, double y){
    return (std::fabs(x-y)<=10e-10*(std::fabs(x)+std::fabs(y)));
}

int main (){
    std::cout<<"Unesite broj krugova: ";
    int br_krugova=0;
    while(true){
        std::cin>>br_krugova;
        if(std::cin.fail()){
            std::cout<<"Neispravan broj krugova, unesite ponovo!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        else if(br_krugova<1) std::cout<<"Neispravan broj krugova, unesite ponovo!"<<std::endl;
        else break;
    }
    try{
        double x=0, y=0, r=0;
        std::vector<std::shared_ptr<NepreklapajuciKrug>>krugovi;
        for(int i=0; i<br_krugova; i++){
            std::cout<<"Unesite centar za "<<i+1<<". krug: ";
            std::cin>>x>>y;
            while(true){
                if(!std::cin){
                    std::cout<<"Neispravan centar!\nUnesite ponovo centar za "<<i+1<<". krug: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cin>>x>>y;
                }
                else break;
            }
            std::cout<<"Unesite poluprecnik: ";
            while(true){
                std::cin>>r;
                if(!std::cin){
                    std::cout<<"Neispravan poluprecnik! Unesite ponovo poluprecnik za "<<i+1<<". krug: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                else if(r<0) std::cout<<"Neispravan poluprecnik! Unesite ponovo poluprecnik za "<<i+1<<". krug: ";
                else break;
            }
            try{
                auto temp=std::make_shared<NepreklapajuciKrug>(std::make_pair(x,y), r);
                krugovi.emplace_back(std::move(temp));
            }
            catch(std::domain_error &izuzetak){
                throw izuzetak;
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Nedozvoljeno preklapanje"<<std::endl;
                i--;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
        std::sort(krugovi.begin(), krugovi.end(), [](std::shared_ptr<NepreklapajuciKrug> k1, std::shared_ptr<NepreklapajuciKrug>k2){
            if(!Jednako(k1->DajPovrsinu(),k2->DajPovrsinu()))
                return k1->DajPovrsinu()>k2->DajPovrsinu();
            else if(!Jednako(k1->DajCentar().first, k2->DajCentar().first)) return k1->DajCentar().first > k2->DajCentar().first;
            return k1->DajCentar().second > k2->DajCentar().second;
        });
        std::cout<<"Krugovi nakon obavljenog sortiranja:"<<std::endl;
        std::for_each(krugovi.begin(), krugovi.end(), [](std::shared_ptr<NepreklapajuciKrug>k){k->Ispisi();});
    }
    catch(...){
        return 1;
    }
	return 0;
}
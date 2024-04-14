//TP 2022/2023: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <algorithm>

class Krug{
    double poluprecnikKruga;
    std::pair<double, double> koordinateCentra;
    static bool Priblizno(double x, double y){
        return (std::fabs(x-y)<=10e-10*(std::fabs(x)+std::fabs(y)));
    }
   public:
    explicit Krug(double poluprecnik = 0){
        if(poluprecnik <0) throw std::domain_error("Nedozvoljen poluprecnik");
        poluprecnikKruga=poluprecnik;
        koordinateCentra.first=0; koordinateCentra.second=0;
    }
    explicit Krug(const std::pair<double, double> &centar, double poluprecnik = 0){
        if(poluprecnik<0) throw std::domain_error("Nedozvoljen poluprecnik");
        poluprecnikKruga=poluprecnik;
        koordinateCentra.first=centar.first;
        koordinateCentra.second=centar.second;
    }
    std::pair<double, double> DajCentar() const{return koordinateCentra;}
    double DajPoluprecnik() const{return poluprecnikKruga;}
    double DajObim() const{return 2*poluprecnikKruga*4*atan(1);}
    double DajPovrsinu() const{return poluprecnikKruga*poluprecnikKruga*4*atan(1);}
    Krug &PostaviCentar(const std::pair<double, double> &centar);
    Krug &PostaviPoluprecnik(double poluprecnik);
    void Ispisi() const;
    Krug &Transliraj(double delta_x, double delta_y);
    Krug &Rotiraj(double alpha);
    Krug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
    static double RastojanjeCentara(const Krug &k1, const Krug &k2);
    static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2);
    static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2);
    static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2);
    static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2);
    static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2);
    static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2);
    static bool DaLiSeSijeku(const Krug &k1, const Krug &k2);
    bool DaLiSadrzi(const Krug &k) const;
    friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y);
    friend Krug RotiraniKrug(const Krug &k, double alpha);
    friend Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rotacije, double alpha);
};

Krug & Krug::PostaviCentar(const std::pair<double, double> &centar){
    this->koordinateCentra=centar;
    return *this;
}

Krug & Krug::PostaviPoluprecnik(double poluprecnik){
    if(poluprecnik<0) throw std::domain_error("Nedozvoljen poluprecnik");
    this->poluprecnikKruga=poluprecnik;
    return *this;
}

void Krug::Ispisi() const{
    std::cout<<"{("<<koordinateCentra.first<<","<<koordinateCentra.second<<"),"<<DajPoluprecnik()<<"}";
    //std::cout<<std::endl;
}

Krug & Krug::Transliraj(double delta_x, double delta_y){
    PostaviCentar({koordinateCentra.first+delta_x, koordinateCentra.second+delta_y});
    PostaviPoluprecnik(this->poluprecnikKruga);
    return *this;
}

Krug & Krug::Rotiraj(double alpha){
    //(xc,yc)=(0,0)
    PostaviCentar({koordinateCentra.first*cos(alpha)-koordinateCentra.second*sin(alpha), koordinateCentra.first*sin(alpha)+koordinateCentra.second*cos(alpha)});
    PostaviPoluprecnik(this->poluprecnikKruga);
    return *this;
}

Krug & Krug::Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha){
    PostaviCentar({centar_rotacije.first+(koordinateCentra.first-centar_rotacije.first)*cos(alpha)-(koordinateCentra.second-centar_rotacije.second)*sin(alpha), 
                centar_rotacije.second+(koordinateCentra.first-centar_rotacije.first)*sin(alpha)+(koordinateCentra.second - centar_rotacije.second)*cos(alpha)});
    PostaviPoluprecnik(this->poluprecnikKruga);
    return *this;
}

double Krug::RastojanjeCentara(const Krug &k1, const Krug &k2){
    return std::sqrt((k1.koordinateCentra.first-k2.koordinateCentra.first)*(k1.koordinateCentra.first-k2.koordinateCentra.first)+
            (k1.koordinateCentra.second-k2.koordinateCentra.second)*(k1.koordinateCentra.second-k2.koordinateCentra.second));
}

bool Krug::DaLiSuIdenticni(const Krug &k1, const Krug &k2){
    if(Priblizno(RastojanjeCentara(k1, k2), 0) && Priblizno(k1.DajPoluprecnik(), k2.DajPoluprecnik())) return true;
    return false;
}

bool Krug::DaLiSuPodudarni(const Krug &k1, const Krug &k2){
    if(Priblizno(k1.DajPoluprecnik(),k2.DajPoluprecnik())) return true;
    return false;
}

bool Krug::DaLiSuKoncentricni(const Krug &k1, const Krug &k2){
    if(Priblizno(RastojanjeCentara(k1, k2), 0))return true;
    return false;
}

bool Krug::DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2){
    if(Priblizno(RastojanjeCentara(k1, k2), k1.DajPoluprecnik()+k2.DajPoluprecnik())) return true;
    return false;
}

bool Krug::DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2){
    if(Priblizno(RastojanjeCentara(k1,k2), k1.DajPoluprecnik()-k2.DajPoluprecnik()) && !DaLiSuIdenticni(k1,k2)) return true;
    return false;
}

bool Krug::DaLiSePreklapaju(const Krug &k1, const Krug &k2){
    if(RastojanjeCentara(k1,k2)< (k1.DajPoluprecnik()+k2.DajPoluprecnik())) return true;
    return false;
}

bool Krug::DaLiSeSijeku(const Krug &k1, const Krug &k2){
    return RastojanjeCentara(k1, k2) > std::fabs(k1.DajPoluprecnik() - k2.DajPoluprecnik()) && k1.DajPoluprecnik() + k2.DajPoluprecnik() > RastojanjeCentara(k1, k2);
}

bool Krug::DaLiSadrzi(const Krug &k) const{
    if(!DaLiSeSijeku(k, *this) && DaLiSePreklapaju(k, *this)) return true;
    return false;
}

Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y){
    auto pomocni=k;
    pomocni.Transliraj(delta_x, delta_y);
    return pomocni;
}

Krug RotiraniKrug(const Krug &k, double alpha){
    auto pomocni=k;
    pomocni.Rotiraj(alpha);
    return pomocni;
}

Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rotacije, double alpha){
    auto pomocni=k;
    pomocni.Rotiraj(centar_rotacije, alpha);
    return pomocni;
}

int main (){
    try{
        std::cout<<"Unesite broj krugova: ";
        int br_krugova=0;
        std::cin>>br_krugova;
        if(br_krugova<1){
            std::cout<<"Uneseni broj nije prirodan!"<<std::endl;
            return 0;
        }
        Krug ** krugovi=new Krug*[br_krugova]{};
        try{
            double x=0, y=0, r=0;
            for(int i=0; i<br_krugova; i++){
                std::cout<<"Unesite centar "<<i+1<<". kruga: ";
                std::cin>>x>>y;
                if(!std::cin){ //ovdje je bilo std::cin.fail()
                    std::cout<<"Neispravne koordinate centra! Pokusajte ponovo: "<<std::endl;
                    i--;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    continue;
                }
                std::cout<<"Unesite poluprecnik "<<i+1<<". kruga: ";
                std::cin>>r;
                try{
                    krugovi[i]=new Krug(std::make_pair(x,y), r);
                }
                catch(std::domain_error &izuzetak){
                    std::cout<<"Neispravan poluprecnik! Pokusajte ponovo: "<<std::endl;
                    i--;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }
            std::cout<<"Unesite parametre translacije (delta_x,delta_y): ";
            std::cin>>x>>y;
            std::transform(krugovi, krugovi+br_krugova, krugovi, [x,y](Krug *k){
                *k=TransliraniKrug(*k, x, y);
                return k;
            });
            std::cout<<"Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
            std::cin>>x;
            std::transform(krugovi, krugovi+br_krugova, krugovi, [x](Krug *k){
                *k=RotiraniKrug(*k,x*(4*atan(1)/180));
                return k;
            });
            std::sort(krugovi, krugovi+br_krugova, [](Krug *k1, Krug *k2){
                return k1->DajPovrsinu()<k2->DajPovrsinu();
            });
            std::cout<<"Parametri krugova nakon obavljene transformacije su: ";
            std::for_each(krugovi, krugovi+br_krugova, [](Krug*k){
                k->Ispisi();
                std::cout<<std::endl;
            });
            auto maxObim= std::max_element(krugovi, krugovi+br_krugova, [](Krug *k1, Krug *k2){
                return k1->DajObim()<k2->DajObim();
            });
            if(maxObim != krugovi+br_krugova){
                std::cout<<"Krug sa najvecim obimom je: ";
                (*maxObim)->Ispisi();
                std::cout<<std::endl;
            }
            int br_presjeka=0;
            std::for_each(krugovi, krugovi+br_krugova, [&](const Krug *k1){
                bool isti=false;
                std::for_each(krugovi, krugovi+br_krugova, [&](const Krug *k2){
                    if(isti){
                        if(Krug::DaLiSeSijeku(*k1, *k2)){
                            std::cout<<"Presjecaju se krugovi: "<<std::endl;
                            (*k1).Ispisi(); 
                            std::cout<<" i ";
                            (*k2).Ispisi();
                            std::cout<<std::endl;
                            br_presjeka++;
                        }
                    }
                    else if(k1==k2) isti=true;
                });
            });
            if(br_presjeka==0) std::cout<<"Ne postoje krugovi koji se presjecaju!"<<std::endl;

            std::for_each(krugovi, krugovi+br_krugova, [](Krug *k){delete k;});
            delete[] krugovi;
        }
        catch(...){
            std::for_each(krugovi, krugovi+br_krugova, [](Krug *k){delete k;});
            delete[] krugovi;
        }
    }
    catch(...){
        std::cout<<std::endl<<"Problemi sa alokacijom memorije!"<<std::endl;
    }
	return 0;
}
//TP 2022/2023: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>

bool ekstrapolacija=false;
void DaLiJeEkstrapolacija(const std::vector<std::pair<double, double>> &uredjeniParovi, double x){
    if(uredjeniParovi.size()==0) ekstrapolacija=false;
    double xmin=uredjeniParovi[0].first, xmax=uredjeniParovi[0].first;
    for(int i=0; i<uredjeniParovi.size(); i++){
        if(uredjeniParovi[i].first<xmin) xmin=uredjeniParovi[i].first;
        if(uredjeniParovi[i].first>xmax) xmax=uredjeniParovi[i].first;
    }
    if(x<xmin || x>xmax) ekstrapolacija=true;
    else ekstrapolacija=false;
}

std::function<double(double)> LagrangeovaInterpolacija(const std::vector<std::pair<double,double>> &uredjeniParovi){
    for(int i=0; i<uredjeniParovi.size(); i++){
        for(int j=0; j<uredjeniParovi.size(); j++){
            if(i!=j){
                if(std::fabs(uredjeniParovi[i].first-uredjeniParovi[j].first)<0.0001) throw std::domain_error("Neispravni cvorovi");
            }
        }
    }
    return[uredjeniParovi](double x){
        DaLiJeEkstrapolacija(uredjeniParovi, x);
        double suma=0.0;
        for(int i=0; i<uredjeniParovi.size(); i++){
            double proizvod=1.0;
            for(int j=0; j<uredjeniParovi.size(); j++)
                if(i!=j)proizvod*=(x-uredjeniParovi[j].first)/(uredjeniParovi[i].first-uredjeniParovi[j].first);
            suma+=(proizvod*uredjeniParovi[i].second);
        }
        return suma;
    };
}

double ZadanaFunkcija(double x){
    return x*x+std::sin(x)+log(x+1);
}

std::function<double(double)> LagrangeovaInterpolacija(std::function<double(double)>funkcija, double xmin, double xmax, double dx){
    if(xmin>xmax || dx<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double, double>>uredjeniParovi;
    for(double i=xmin; i<=xmax; i+=dx) uredjeniParovi.push_back({i,funkcija(i)});
    return LagrangeovaInterpolacija(uredjeniParovi);
}

int main (){
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    int opcija=0;
    std::cin>>opcija;
    try{
        if(opcija==1){
            std::cout<<"Unesite broj cvorova: ";
            int brojParova=0;
            std::cin>>brojParova;
            std::cout<<"Unesite cvorove kao parove x y: ";
            std::vector<std::pair<double, double>> uredjeniParovi(brojParova);
            for(int i=0; i<brojParova; i++) std::cin>>uredjeniParovi[i].first>>uredjeniParovi[i].second;
            auto Interpolacija=LagrangeovaInterpolacija(uredjeniParovi);
            while(true){
                std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                double argument=0.0;
                if(std::cin>>argument){
                    std::cout<<"f("<<argument<<") = "<<Interpolacija(argument);
                    if(ekstrapolacija) std::cout<<" [ekstrapolacija]";
                    std::cout<<std::endl;
                }
                else break;
            }
        }
        else{
            std::cout<<"Unesite krajeve intervala i korak: ";
            double xmin=0, xmax=0, dx=0;
            std::cin>>xmin>>xmax>>dx;
            auto Interpolacija=LagrangeovaInterpolacija(ZadanaFunkcija, xmin, xmax, dx);
            while(true){
                std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                double argument=0.0;
                if(std::cin>>argument){
                    std::cout<<"f("<<argument<<") = "<<ZadanaFunkcija(argument)<<" P("<<argument<<") = "<<Interpolacija(argument);
                    if(ekstrapolacija) std::cout<<" [ekstrapolacija]";
                    std::cout<<std::endl;
                }
                else break;
            }
        }
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}
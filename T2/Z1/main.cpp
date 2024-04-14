//TP 2022/2023: LV 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

bool DaLiJeProst(int n){
    bool prost=true;
    if(n<2){
        return false;
    }
    for(int i=2; i<=std::sqrt(n); i++){
        if(n%i==0){
            prost=false;
            break;
        }
    }
    return prost;
}

std::vector<int> ProstiBrojeviUOpsegu(int a, int b){
    std::vector<int>Prosti;
    for(long int i=a; i<=b; i++){
        if(DaLiJeProst(i)){
            Prosti.push_back(i);
        }
    }
    return Prosti;
}

int main (){
    int a, b;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;
    std::vector<int>Prosti=ProstiBrojeviUOpsegu(a, b);
    //int velicina=Prosti.size();
    if(Prosti.size()){
        std:: cout<<"Prosti brojevi u rasponu od "<<a<<" do "<<b<<" su: ";
        for(int i=0; i<Prosti.size(); i++){
            std:: cout<<Prosti[i];
            if(i<Prosti.size()-1) std::cout<<", ";
        }
        std::cout<<std::endl;
    }
    else
        std::cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!"<<std::endl;

	return 0;
}

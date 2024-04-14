//TP 2022/2023: Zadaća 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

template<typename Tip>
auto ProizvodReda(const std::vector<Tip> &red){
    Tip proizvod=red.at(0);
    for(int i=1; i<red.size(); i++) proizvod*=red.at(i);
    return proizvod;
}

template<typename Tip>
bool Kriterij(const std::vector<Tip> &red1, const std::vector<Tip> &red2){
    if(red1.size()==0 || red2.size()==0) return false;
    if(ProizvodReda(red1)==ProizvodReda(red2)) return red1<red2;
    return ProizvodReda(red1)<=ProizvodReda(red2);
}

template<typename Tip>
void SortirajPoProizvoduRedova(std::vector<std::vector<Tip>> &matrica){
    std::sort(matrica.begin(), matrica.end(), Kriterij<Tip>);
}

int main (){
    std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa):\n";
    std::vector<std::vector<int>>matrica;
    std::vector<int>red;
    int element=0;
    while(std::cin>>element){
        red.push_back(element);
        while(std::cin>>element) red.push_back(element);
        matrica.push_back(red);
        std::cin.clear();
        std::cin.ignore(100, '\n');
        red.resize(0);
    }
    SortirajPoProizvoduRedova(matrica);
    std::cout<<"\nMatrica nakon sortiranja:\n";
    for(int i=0; i<matrica.size(); i++){
        for(int j=0; j<matrica.at(i).size(); j++)
            std::cout<<matrica.at(i).at(j)<<" ";
        std::cout<<std::endl;
    }
    std::cout<<"\nUnesite elemente sekvence koja se trazi (* za kraj reda): \n";
    red.resize(0);
    std::cin.clear();
    std::cin.ignore(100,'\n');
    while(std::cin>>element) red.push_back(element);
    auto ptr=std::lower_bound(matrica.begin(), matrica.end(), red, Kriterij<int>);
    if(ptr==matrica.end() || *ptr!=red) std::cout<<"Trazena sekvenca se ne nalazi u matrici";
    else std::cout<<"Trazena sekvenca se nalazi u "<<ptr-matrica.begin()+1<<". redu (nakon sortiranja)";
	return 0;
}
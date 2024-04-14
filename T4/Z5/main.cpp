//TP 2022/2023: LV 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

template <typename NekiTip>
void Prepisi(std::vector<NekiTip> &rezultat, int &j) {
    for (int k = j; k < rezultat.size() - 1; k++)
        rezultat.at(k) = rezultat.at(k + 1);
    rezultat.resize(rezultat.size() - 1);
    j--;
}

template <typename NekiTip>
std::vector<NekiTip> Presjek(std::vector<NekiTip> &v1, std::vector<NekiTip> &v2){
    std::vector<NekiTip> rezultat;
    for(int i=0; i<v1.size(); i++)
        for(int j=0; j<v2.size(); j++)
            if(v2.at(j)==v1.at(i)) rezultat.push_back(v1.at(i));

    for (int i = 0; i < rezultat.size(); i++)
        for (int j = i + 1; j < rezultat.size(); j++) 
            if (rezultat.at(i) == rezultat.at(j)) {
                Prepisi(rezultat, j);
            }
    return rezultat;
}


int main (){
    std::cout<<"Test za realne brojeve..."<<std::endl;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    int vel1;
    std::cin>>vel1;
    std::cout<<"Unesite elemente prvog vektora: ";
    std::vector<double> v1(vel1);
    for(int i=0; i<vel1; i++){
        std::cin>>v1.at(i);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    int vel2;
    std::cin>>vel2;
    std::cout<<"Unesite elemente drugog vektora: ";
    std::vector<double> v2(vel2);
    for(int i=0; i<vel2; i++){
        std::cin>>v2.at(i);
    }
    std::cout<<"Zajednicki elementi su: ";
    auto v3 = Presjek(v1, v2);
    for(auto x : v3) std::cout << x << " ";
    
    std::cout<<"Test za stringove..."<<std::endl;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    int velS1;
    std::cin>>velS1;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    std::vector<std::string> s1(velS1);
    std::cin.ignore(10000, '\n');
    for(int i=0; i<velS1; i++){
        getline(std::cin, s1.at(i));
    }
    std::cout<<std::endl<<"Unesite broj elemenata drugog vektora: ";
    int velS2;
    std::cin>>velS2;
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    std::vector<std::string> s2(velS2);
    std::cin.ignore(10000, '\n');
    for(int i=0; i<velS2; i++){
        getline(std::cin, s2.at(i));
    }
    auto rezultirajuci=Presjek(s1,s2);
    std::cout<<"Zajednicki elementi su: ";
    for(int i=0; i<rezultirajuci.size(); i++)
        std::cout<<rezultirajuci.at(i)<<std::endl;
	return 0;
}
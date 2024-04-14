//TP 2022/2023: Zadaća 1, Zadatak 2
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <vector>

typedef std::vector<std::vector<double>> Matrica;

void UnesiMatricu(Matrica &mat){
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat.at(i).size(); j++)
            std::cin>>mat.at(i).at(j);
    }
}

Matrica UsrednjavajuciFilter(const Matrica &pocetna, int filter){
    if(filter<0) throw std::domain_error("Neispravan red filtriranja");
    Matrica filtrirana;
    filtrirana.resize(pocetna.size());
    for(int i=0; i<pocetna.size(); i++){
        filtrirana.at(i).resize(pocetna.at(i).size());
        for(int j=0; j<pocetna.at(i).size(); j++){
            double suma=0;
            int broj_el=0;
            for(int k=i-filter; k<=i+filter; k++){
                for(int m=j-filter; m<=j+filter; m++){
                    if(k>=0 && k<pocetna.size() && m>=0 && m<pocetna.at(k).size()){
                        suma+=pocetna.at(k).at(m);
                        broj_el++;
                    }
                }
            }
            //filtrirana.at(i).at(j)=round((suma/broj_el)*100)/100;
            filtrirana.at(i).at(j)=suma/broj_el;
        }
    }
    return filtrirana;
}


int main (){
    std::cout<<"Unesite broj redova i kolona matrice: ";
    int redovi=0, kolone=0;
    std::cin>>redovi>>kolone;
    std::cin.ignore(1000, '\n');
    std::cout<<"Unesite elemente matrice: ";
    Matrica m(redovi, std::vector<double>(kolone));
    UnesiMatricu(m);
    int redFiltriranja=0;
    std::cout<<"Unesite red filtriranja: ";
    std::cin>>redFiltriranja;

    try{
        Matrica filtrirana=UsrednjavajuciFilter(m, redFiltriranja);
        std::cout<<std::endl<<"Matrica nakon filtriranja: "<<std::endl;
        for(int i=0; i<filtrirana.size(); i++){
            for(int j=0; j<filtrirana.at(i).size(); j++)
                std::cout<<std::setw(7)<<std::fixed<<std::setprecision(2)<<filtrirana.at(i).at(j);
            std::cout<<std::endl;
        }
    }
    catch(std::domain_error &izuzetak){
        std::cout<<std::endl<<"GRESKA: "<<izuzetak.what()<<"!";
    }
	return 0;
}
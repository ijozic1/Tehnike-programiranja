//TP 2022/2023: LV 7, Zadatak 3
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

auto KreirajMatricu(const int &brRecenica){
    std::string *matrica = new std::string[brRecenica];
    try{
        for(int i=0; i<brRecenica; i++){
            std::string recenica;
            std::getline(std::cin, recenica);
            matrica[i] = recenica;
        }
        std::sort(matrica, matrica+brRecenica,[](std::string a, std::string b){return a<b;});
        return matrica;
    }
    catch(...){
        delete[] matrica;
        throw;
    }
}

void IspisiRecenicu(const std::string& recenica){
    std::cout<<recenica<<std::endl;
}

int main (){
    std::cout<<"Koliko zelite recenica: ";
    int brRecenica=0;
    std::cin>>brRecenica;
    std::cin.ignore();
    std::cout<<"Unesite recenice:\n";
    try{
        std::string *matrica=KreirajMatricu(brRecenica);
        std::cout<<"Sortirane recenice:\n";
        for(int i=0; i<brRecenica; i++) IspisiRecenicu(matrica[i]);
        delete[] matrica;
    }
    catch(...){
        std::cout<<"Problemi s memorijom!\n";
    }
    return 0;
}
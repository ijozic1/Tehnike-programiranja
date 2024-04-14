//TP 2022/2023: LV 7, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <memory>

using SharedStringPtr = std::shared_ptr<std::string>;
using UniqueStringNiz = std::unique_ptr<SharedStringPtr[]>;

UniqueStringNiz KreirajMatricu(const int& brRecenica) {
    UniqueStringNiz matrica(new SharedStringPtr[brRecenica]);
    try {
        std::cin.ignore(100, '\n');
        for (int i = 0; i < brRecenica; i++) {
            /*std::string recenica=std::string();
            std::getline(std::cin, recenica);
            matrica[i] = std::make_shared<std::string>(recenica);*/
            matrica[i] = std::make_shared<std::string>();
            std::getline(std::cin, *matrica[i]);
        }
        std::sort(matrica.get(), matrica.get() + brRecenica, [](SharedStringPtr a, SharedStringPtr b) { return *a < *b; });
        return matrica;
    }
    catch (...) {
        throw;
    }
}

int main (){
    std::cout<<"Koliko zelite recenica: ";
    int brRecenica=0;
    std::cin>>brRecenica;
    std::cout<<"Unesite recenice:\n";
    try{
        auto matrica = KreirajMatricu(brRecenica);
        std::cout<<"Sortirane recenice:\n";
        for(int i=0; i<brRecenica; i++) std::cout<<*matrica.get()[i]<<std::endl;
    }
    catch(...){
        std::cout<<"Problemi s memorijom!\n";
    }
    return 0;
}
//TP 2022/2023: LV 7, Zadatak 5
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <memory>

using SharedStringPtr = std::shared_ptr<std::string>;
using SharedStringNiz = std::shared_ptr<SharedStringPtr[]>;

SharedStringNiz KreirajMatricu(const int& brRecenica) {
    SharedStringNiz matrica(new SharedStringPtr[brRecenica], [](std::shared_ptr<std::string> *pok){delete[] pok;});
    try {
        for (int i = 0; i < brRecenica; i++) {
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
    std::cin.ignore();
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

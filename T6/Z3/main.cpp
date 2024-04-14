//TP 2022/2023: LV 6, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>

int** KreirajTrougao(int n) {
    if (n <= 0) throw std::domain_error("Broj redova mora biti pozitivan");
    int** matrica=new int*[n]{};
    try {
        for (int i = 0; i < n; i++) {
            matrica[i]=new int[2*i+1];
            for (int j = 0; j < 2*i+1; j++){
                if(j<i) matrica[i][j]=i-j+1;
                else if(i==j) matrica[i][j]=1;
                else matrica[i][j]=j-i+1;
            }
        }
    } 
    catch (std::bad_alloc) {
        for (int i = 0; i < n; i++) delete[] matrica[i];
        delete[] matrica;
        throw std::bad_alloc();
    }
    return matrica;
}

int main (){
    std::cout<<"Koliko zelite redova: ";
    int n;
    std::cin>>n;
    try {
        int** matrica = KreirajTrougao(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2*i+1; j++) std::cout << matrica[i][j] << " ";
            std::cout << std::endl;
        }
        // oslobodi memoriju
        for (int i = 0; i < n; i++) delete[] matrica[i];
        delete[] matrica;
    } 
    catch (const std::domain_error& e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    } 
    catch (const std::bad_alloc) {
        std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
    }
    return 0;
}
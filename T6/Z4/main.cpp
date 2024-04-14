//TP 2022/2023: LV 6, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
//pokusati ispisivati i i j pa vidjeti da li negdje izadje
//svako kreiranje vektora ili deka staviti u try blok

int** KreirajTrougao(int n) {
    if (n <= 0) throw std::domain_error("Broj redova mora biti pozitivan");
    //ukupna velicina niza
    int velicina = 0;
    for (int i = 0; i < n; i++) {
        velicina += (2*i+1);
    }
    try {
        int **matrica=new int*[n];
        try{
            matrica[0]=new int[velicina];
            for(int i=1; i<n; i++) matrica[i]=matrica[i-1]+(2*i);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 2*i+1; j++){
                    if(j<i) matrica[i][j]=i-j+1;
                    else if(i==j) matrica[i][j]=1;
                    else matrica[i][j]=j-i+1;
                }
            }
            return matrica;
        }
        catch(std::bad_alloc){
            delete [] matrica;
            throw std::bad_alloc();
        }
    } 
    catch (std::bad_alloc) {
        throw std::bad_alloc();
    }

    return nullptr;
}

int main (){
    std::cout<<"Koliko zelite redova: ";
    int n;
    std::cin>>n;
    try {
        int** matrica = nullptr;
        matrica=KreirajTrougao(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2*i+1; j++) std::cout << matrica[i][j] << " ";
            std::cout << std::endl;
        }
        delete[] matrica[0];
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
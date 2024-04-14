//TP 2022/2023: LV 6, Zadatak 6
#include <iostream>
#include <vector>
#include <deque>
#include <exception>

template <typename Tip>
auto KreirajDinamickuKopiju2D(const Tip &struktura)->decltype(struktura[0][0]+struktura[0][0])**{
    int ukupnaVelicina=0;
    for(int i=0; i<struktura.size(); i++) ukupnaVelicina+=struktura[i].size();
    try {
        decltype(struktura[0][0]+struktura[0][0])** matrica = new decltype(struktura[0][0]+struktura[0][0])*[struktura.size()]{};
        try{
            matrica[0]=new decltype(struktura[0][0]+struktura[0][0])[ukupnaVelicina];
            for(int i=1; i<struktura.size(); i++) matrica[i]=matrica[i-1]+struktura[i].size();
            // kopiramo elemente strukture u matricu
            for (int i = 0; i < struktura.size(); i++) {
                for (int j = 0; j < struktura[i].size(); j++) {
                    matrica[i][j] =struktura[i][j];
                }
            }
            return matrica;       
        }
        catch(std::bad_alloc){
            delete[] matrica;
            throw std::bad_alloc();
        }
    } 
    catch (std::bad_alloc) {
        throw std::bad_alloc();
    }
    return nullptr;
}

int main() {
    int n;
    std::cout << "Unesite broj redova kvadratne matrice: ";
    std::cin >> n;
    try {
        std::vector<std::deque<int>> struktura(n);
        std::cout << "Unesite elemente matrice: ";
        for (int i = 0; i < n; i++) {
            struktura[i].resize(n);
            for (int j = 0; j < n; j++) std::cin >> struktura[i][j];
        }
        auto matrica = KreirajDinamickuKopiju2D(struktura);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <n; j++) std::cout<<matrica[i][j] << " ";
            std::cout << std::endl;
        }
        // oslobađanje memorije
        delete[] matrica[0]; delete[] matrica;
    } 
    catch (std::bad_alloc) {
        std::cout << "Nedovoljno memorije" << std::endl;
    }
    return 0;
}
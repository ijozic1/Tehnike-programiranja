// TP 2022/2023: Zadaća 2, Zadatak 5
#include <cmath>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <array>

template <typename IterTip1, typename IterTip2>
auto KreirajTablicuSabiranja(const IterTip1 pocetakA, const IterTip1 izaKrajaA, const IterTip2 pocetakB)-> decltype(*pocetakA + *pocetakB) ** {
    int velicinaSekvence = 0;
    IterTip1 pomocniPocetakA = pocetakA;
    while (pomocniPocetakA++ != izaKrajaA) velicinaSekvence++;
    int velicina=(velicinaSekvence*(velicinaSekvence+1))/2;
    using Tip = decltype(*pocetakA + *pocetakB);
    try {
       Tip** matrica = new Tip *[velicinaSekvence] {};
        try { matrica[0] = new Tip[velicina];}
        catch(...){
            delete[] matrica; matrica=nullptr;
            throw;
        }
        for (int i = 1; i < velicinaSekvence; i++) matrica[i] = matrica[i - 1] + i;
        pomocniPocetakA = pocetakA;
        IterTip2 pomocniPocetakB = pocetakB, izaKrajaB = pocetakB;
        for (int i = 0; i < velicinaSekvence; i++) izaKrajaB++;
        for (int i = 0; i < velicinaSekvence; i++) {
            pomocniPocetakB = pocetakB;
            try{
                for (int j = 0; j < i + 1; j++) {
                    if (*pomocniPocetakA + *pomocniPocetakB != *pomocniPocetakB + *pomocniPocetakA){
                        //delete[] matrica[0]; delete[] matrica;
                        throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
                    }
                    matrica[i][j] = *pomocniPocetakA + *pomocniPocetakB;
                    if (pomocniPocetakB != izaKrajaB) pomocniPocetakB++;
                }
            } 
            catch (std::logic_error &izuzetak) {
                std::cout<<"Dolazim do brisanja";
                delete[] matrica[0]; delete[] matrica;
                std::cout<<std::endl<<"Brisanje je uspjesno\n";
                throw izuzetak;
            }
            if (pomocniPocetakA != izaKrajaA) pomocniPocetakA++;
        }
        return matrica;
    }
    catch (std::logic_error &izuzetak) {
        throw izuzetak;
    } 
    catch (...) {
        throw std::range_error("Nema dovoljno memorije!");
    }
}

int main() {
  try {
    std::vector<std::string> A{"p","q"};
    std::vector<std::string> B{"r","s"};
    KreirajTablicuSabiranja(A.begin(), A.end(), B.begin());
  }
  catch (std::logic_error &izuzetak) {
    std::cout << izuzetak.what() <<"!"<< std::endl;
  }
  catch (...) {
    std::cout << "Nema dovoljno memorije" << std::endl;
  }
  return 0;
}
// TP 2022/2023: Zadaća 3, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>

int Poglavica(int N, int M, bool ispisi = false) {
    if (N <= 0 || M <= 0) return 0;
    std::list<int> redniBrojevi;
    int i = 1;
    while (i <= N) redniBrojevi.push_back(i++);
    auto pocetak = redniBrojevi.begin();
    while (redniBrojevi.size() != 1) {
        int korak = M;
        while (korak != 0) {
            if (pocetak == redniBrojevi.end()) pocetak = redniBrojevi.begin();
            korak--;
            if (korak != 0) pocetak++;
        }
        if (ispisi) std::cout<< *pocetak << ", ";
        pocetak = redniBrojevi.erase(pocetak);
    }
    return *redniBrojevi.begin();
}

int SigurnoMjesto(int M, int N1, int N2) {
    if(M<=0 || N1<=0 || N2<=0 || N2<N1) return 0;
    std::list<int> sigurnaMjesta;
    int i = N1;
    while (i <= N2) sigurnaMjesta.push_back(i++);
    while (N1 <= N2) {
        auto izbacivanje =std::find(sigurnaMjesta.begin(), sigurnaMjesta.end(), Poglavica(N1, M));
        if(izbacivanje!=sigurnaMjesta.end())izbacivanje = sigurnaMjesta.erase(izbacivanje);
        N1++;
    }
    if (sigurnaMjesta.begin() == sigurnaMjesta.end()) return 0;
    return *sigurnaMjesta.begin();
}

int main() {
    std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena Wabambe: ";
    int brojClanova = 0, N1 = 0, N2 = 0, M = 0;
    std::cin >> brojClanova;
    std::cout << "Unesite korak razbrajanja: ";
    std::cin >> M;
    std::cout << "Unesite raspon za odabir (N1 i N2): ";
    std::cin >> N1 >> N2;
    std::cout << "Redni broj osobe koja postaje poglavica: "<< Poglavica(brojClanova, M) << std::endl;
    int sigurno = SigurnoMjesto(M, N1, N2);
    if (sigurno) std::cout << "Mbebe Mgogo, stani na sigurno mjesto " << sigurno<< " da ne bi bio poglavica!";
    else std::cout << "Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta."<< std::endl;
    return 0;
}

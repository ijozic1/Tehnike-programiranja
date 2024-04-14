//TP 2022/2023: LV 8, Zadatak 6
#include <iostream>
#include <cmath>

template <typename TipElemenata>
struct Cvor {
    TipElemenata element;
    Cvor<TipElemenata> *veza;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni) {
    Cvor<TipElemenata> *pocetak = nullptr, *prethodni = nullptr;
    TipElemenata x;
    do {
        std::cin >> x;
        if (x == zavrsni) break;
        Cvor<TipElemenata> *novi = new Cvor<TipElemenata>{x, nullptr};
        if (pocetak == nullptr) pocetak = novi;
        else prethodni->veza = novi;
        prethodni = novi;
    } while (true);
    return pocetak;
}

template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak) {
    int broj = 0;
    for (Cvor<TipElemenata> *p = pocetak; p != nullptr; p = p->veza) broj++;
    return broj;
}

template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak) {
    TipElemenata suma = 0;
    for (Cvor<TipElemenata> *p = pocetak; p != nullptr; p = p->veza) suma += p->element;
    return suma;
}

template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag) {
    int broj = 0;
    for (Cvor<TipElemenata> *p = pocetak; p != nullptr; p = p->veza)
        if (p->element > prag) broj++;
    return broj;
}

template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak) {
    while (pocetak != nullptr) {
        Cvor<TipElemenata> *p = pocetak;
        pocetak = pocetak->veza;
        delete p;
    }
}

int main() {
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    Cvor<double> *pocetak = KreirajPovezanuListu(0.0);
    double suma = SumaElemenata(pocetak);
    int broj = BrojElemenata(pocetak);
    double aritSredina = broj > 0 ? suma / broj : 0.0;
    int brojVecih = BrojVecihOd(pocetak, aritSredina);
    std::cout << "U slijedu ima "<<brojVecih<<" brojeva vecih od njihove aritmeticke sredine" <<std::endl;
    UnistiListu(pocetak);
    return 0;
}

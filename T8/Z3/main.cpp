//TP 2022/2023: LV 8, Zadatak 3
#include <iostream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
const int BrojPredmeta = 8;

struct Datum {
    int dan, mjesec, godina;
};

struct Ucenik {
    std::string ime, prezime;
    Datum datum_rodjenja;
    int ocjene[BrojPredmeta];
    double prosjek;
    bool prolaz;
};

int main() {
    void UnesiUcenike(Ucenik **p_ucenici, int brojUcenika);
    void ObradiUcenike(Ucenik **p_ucenici, int brojUcenika);
    void IspisiIzvjestaj(Ucenik **p_ucenici, int brojUcenika);
    void OslobodiMemoriju(Ucenik **p_ucenici, int brojUcenika);
    int broj_ucenika;
    std::cout << "Koliko ima ucenika: ";
    std::cin >> broj_ucenika;
    try {
        Ucenik *ucenici=nullptr;
        ucenici=new Ucenik[broj_ucenika];
        Ucenik **p_ucenici;
        try {
            p_ucenici=new Ucenik*[broj_ucenika]{};
            UnesiUcenike(p_ucenici, broj_ucenika);
        }
        catch(...) {
            OslobodiMemoriju(p_ucenici, broj_ucenika);
            delete[] ucenici;
            throw; 
        }
        ObradiUcenike(p_ucenici, broj_ucenika);
        IspisiIzvjestaj(p_ucenici, broj_ucenika);
        OslobodiMemoriju(p_ucenici, broj_ucenika);
        delete[] ucenici;
    }
    catch(...) {
        std::cout << "Problemi sa memorijom...\n"; 
    }
    return 0;
}

void UnesiUcenike(Ucenik **p_ucenici, int brojUcenika) {
    void UnesiJednogUcenika(Ucenik *p_ucenik);
    for(int i = 0; i < brojUcenika; i++) {
        std::cout << "Unesite podatke za " << i + 1 << ". ucenika:\n";
        p_ucenici[i] = new Ucenik;
        UnesiJednogUcenika(p_ucenici[i]);
    }
}

void UnesiJednogUcenika(Ucenik **p_ucenik, int brojUcenika) {
    void UnesiDatum(Datum &datum);
    void UnesiOcjene(int ocjene[], int broj_predmeta);
    std::cout << " Ime: "; std::cin >> (**p_ucenik).ime;
    std::cout << " Prezime: "; std::cin >> (**p_ucenik).prezime;
    std::cout << " Datum rodjenja (D/M/G): ";
    UnesiDatum((**p_ucenik).datum_rodjenja);
    UnesiOcjene((**p_ucenik).ocjene, BrojPredmeta);
}

void UnesiDatum(Datum &datum) {
    char znak;
    std::cin >> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}

void UnesiOcjene(int ocjene[], int broj_predmeta) {
    void UnesiOcjenu(int &ocjena);
    for(int i = 0; i < broj_predmeta; i++) {
        std::cout << " Ocjena iz " << i + 1 << ". predmeta: ";
    UnesiOcjenu(ocjene[i]);
    }
}

void UnesiOcjenu(int &ocjena) {
    std::cin >> ocjena;
}

void ObradiUcenike(Ucenik **p_ucenici, int brojUcenika) {
    void ObradiJednogUcenika(Ucenik *p_ucenik);
    for(auto i=p_ucenici; i<p_ucenici+brojUcenika; i++) ObradiJednogUcenika(*i);
    std::sort(p_ucenici, p_ucenici+brojUcenika,
        [](const Ucenik *p_u1, const Ucenik *p_u2) {
        return p_u1->prosjek > p_u2->prosjek;});
}

void ObradiJednogUcenika(Ucenik **p_ucenik) {
    double suma_ocjena = 0;
    (**p_ucenik).prosjek = 1; (**p_ucenik).prolaz = false;
    for(int ocjena : (**p_ucenik).ocjene) {
        if(ocjena == 1) return;
        suma_ocjena += ocjena;
    }
    (**p_ucenik).prolaz = true; 
    (**p_ucenik).prosjek = suma_ocjena / BrojPredmeta;
}

void IspisiIzvjestaj(Ucenik **p_ucenici, int brojUcenika) {
    void IspisiJednogUcenika(const Ucenik *p_ucenik);
    std::cout << std::endl;
    for(auto i=p_ucenici; i<p_ucenici+brojUcenika; i++) IspisiJednogUcenika(*i);
}

void IspisiJednogUcenika(const Ucenik **p_ucenik) {
    void IspisiDatum(const Datum &datum);
    std::cout << "Ucenik " << (**p_ucenik).ime << " " << (**p_ucenik).prezime<< " rodjen ";
    IspisiDatum((**p_ucenik).datum_rodjenja);
    if((**p_ucenik).prolaz) std::cout << " ima prosjek " << std::setprecision(3) << (**p_ucenik).prosjek;
    else std::cout << " mora ponavljati razred";
    std::cout << std::endl;
}

void IspisiDatum(const Datum &datum) {
    std::cout << datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}

void OslobodiMemoriju(Ucenik **p_ucenici, int brojUcenika) {
    for(auto i=p_ucenici; i<p_ucenici+brojUcenika; i++) delete[] i; 
}
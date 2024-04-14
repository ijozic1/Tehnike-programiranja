// TP 2022/2023: LV 11, Zadatak 5
#include <algorithm>
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class Tim {
    char ime_tima[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;
  public:
    Tim(const char ime[]): broj_odigranih(), broj_pobjeda(), broj_nerijesenih(), broj_poraza(),broj_datih(), broj_primljenih(), broj_poena() {
        if (strlen(ime) > 20) throw std::range_error("Predugacko ime tima");
        strcpy(ime_tima, ime);
    }
    //~Tim(){std::cout<<"Pozvan je destruktor"<<std::endl;};
    void ObradiUtakmicu(int broj_datih, int broj_primljenih);
    const char *DajImeTima() const { return ime_tima; }
    int DajBrojPoena() const { return broj_poena; }
    int DajGolRazliku() const { return broj_datih - broj_primljenih; }
    void IspisiPodatke() const;
};

class Liga {
    std::vector<std::shared_ptr<Tim>> timovi;
  public:
    explicit Liga(int velicina_lige);
    explicit Liga(std::initializer_list<Tim> lista_timova);
    ~Liga();
    Liga(const Liga &l);
    Liga(Liga &&l);
    Liga &operator=(const Liga &l);
    Liga &operator=(Liga &&l) = default;
    void DodajNoviTim(const char ime_tima[]);
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2);
    void IspisiTabelu();
    static bool PoredakLige(std::shared_ptr<Tim> t1, std::shared_ptr<Tim> t2);
};

void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih) {
    if (broj_datih < 0 || broj_primljenih < 0) throw std::range_error("Neispravan broj golova");
    Tim::broj_odigranih++;
    Tim::broj_datih += broj_datih;
    Tim::broj_primljenih += broj_primljenih;
    if (broj_datih > broj_primljenih) {
        Tim::broj_pobjeda++;
        Tim::broj_poena += 3;
    } 
    else if (broj_datih == broj_primljenih) {
        Tim::broj_nerijesenih++;
        Tim::broj_poena += 1;
    } 
    else {
        Tim::broj_poraza++;
    }
}
void Tim::IspisiPodatke() const {
    std::cout << std::left<<std::setw(20)<< Tim::DajImeTima();
    std::cout << std::fixed << std::setw(4) << Tim::broj_odigranih << std::fixed<< std::setw(4) << Tim::broj_pobjeda << std::fixed << std::setw(4)
        << Tim::broj_nerijesenih << std::fixed << std::setw(4)<< Tim::broj_poraza << std::fixed << std::setw(4) << Tim::broj_datih
        << std::fixed << std::setw(4) << Tim::broj_primljenih << std::fixed<< std::setw(4) << Tim::DajBrojPoena() << std::endl;
}

Liga::Liga(int velicina_lige) { timovi.resize(velicina_lige); }
Liga::Liga(std::initializer_list<Tim> lista_timova) {
    timovi.resize(lista_timova.size());
    try {
        int i = 0;
        for (const auto &tim : lista_timova) {
            // DodajNoviTim(tim.DajImeTima());
            timovi[i] = std::make_shared<Tim>(lista_timova.begin()[i]);
            i++;
        }
    } 
    catch (...) {
        throw;
    }
}
Liga::~Liga() {}
Liga::Liga(const Liga &l) {
    timovi.resize(l.timovi.size());
    try {
        for (int i = 0; i < l.timovi.size(); i++) timovi[i] = std::make_shared<Tim>(*l.timovi[i]);
    } 
    catch (...) {
        throw;
    }
}
Liga::Liga(Liga &&l) {
    timovi.resize(l.timovi.size());
    l.timovi.resize(0);
}
Liga &Liga::operator=(const Liga &l) {
    // if(l.max_br_timova!=max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    if (l.timovi.size() > timovi.size()) {
        try {
            for (int i = timovi.size(); i < l.timovi.size(); i++) timovi.emplace_back(std::make_shared<Tim>(*l.timovi[i]));
        } 
        catch (...) {
            throw;
        }
    } 
    else {
        timovi.resize(l.timovi.size());
    }
    for (int i = 0; i < timovi.size(); i++) *timovi[i] = *l.timovi[i];
    return *this;
}
/*Liga &Liga::operator=(Liga &&l) {
    if(&l==this) return *this;
  *this = std::move(l);
  return *this;
}*/
void Liga::DodajNoviTim(const char ime_tima[]) {
  // if (broj_timova >= max_br_timova) throw std::range_error("Liga popunjena");
    for (int i = 0; i < timovi.size(); i++) {
        if (strcmp(timovi[i]->DajImeTima(), ime_tima) == 0) throw std::logic_error("Tim vec postoji");
    }
    timovi.emplace_back(std::make_shared<Tim>(ime_tima));
}
void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2) {
    int indeks_tim1 = -1, indeks_tim2 = -1;
    for (int i = 0; i < timovi.size(); i++) {
        if (strcmp(timovi[i]->DajImeTima(), tim1) == 0) indeks_tim1 = i;
        if (strcmp(timovi[i]->DajImeTima(), tim2) == 0) indeks_tim2 = i;
    }
    if (indeks_tim1 == -1 || indeks_tim2 == -1) throw std::logic_error("Tim nije nadjen");

    try {
        timovi[indeks_tim1]->ObradiUtakmicu(rezultat_1, rezultat_2);
        timovi[indeks_tim2]->ObradiUtakmicu(rezultat_2, rezultat_1);
    } 
    catch (std::range_error &e) {
        throw e;
    }
}
bool Liga::PoredakLige(std::shared_ptr<Tim> t1, std::shared_ptr<Tim> t2) {
    if (t1->DajBrojPoena() == t2->DajBrojPoena()) {
        if (t1->DajGolRazliku() == t2->DajGolRazliku()) {
            return strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0;
        }
        return t1->DajGolRazliku() > t2->DajGolRazliku();
    }
    return t1->DajBrojPoena() > t2->DajBrojPoena();
}
void Liga::IspisiTabelu() {
    std::sort(timovi.begin(), timovi.end(), PoredakLige);
    for (int i = 0; i < timovi.size(); i++) timovi[i]->IspisiPodatke();
}

int main() {
    try {
        Liga liga{"Borac", "Celik", "Jedinstvo", "Sarajevo", "Zeljeznicar", "Zrinjski"};
        /*Liga liga(6);
        liga.DodajNoviTim("Borac");
        liga.DodajNoviTim("Celik");
        liga.DodajNoviTim("Jedinstvo");
        liga.DodajNoviTim("Sarajevo");
        liga.DodajNoviTim("Zeljeznicar");
        liga.DodajNoviTim("Zrinjski");*/
        // liga.DodajNoviTim("Tim 7"); // Izaziva izuzetak jer je liga popunjena
        liga.IspisiTabelu();
        std::cout << std::endl;
        while (true) {
            std::cout << "Unesite ime prvog tima (ENTER za kraj): ";
            char ime_tim1[20];
            char ime_tim2[20];
            std::cin.getline(ime_tim1, 20);
            if (strlen(ime_tim1) == 0) break;
            std::cout << "Unesite ime drugog tima: ";
            std::cin.getline(ime_tim2, 20);
            std::cout << "Unesite broj postignutih golova za oba tima: ";
            int broj_golova1 = 0, broj_golova2 = 0;
            std::cin >> broj_golova1 >> broj_golova2;
            try {
                liga.RegistrirajUtakmicu(ime_tim1, ime_tim2, broj_golova1, broj_golova2);
                std::cout << std::endl;
                liga.IspisiTabelu();
                std::cout << std::endl;
            }
            catch (std::logic_error &e) {
                std::cout << e.what() << std::endl << std::endl;
            } 
            catch (std::range_error &e) {
                std::cout << e.what() << std::endl << std::endl;
            } 
            catch (...) {
                std::cout << "Doslo je do greske!" << std::endl << std::endl;
            }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    } 
    catch (...) {
        std::cout << "Doslo je do greske!" << std::endl;
    }
    return 0;
}
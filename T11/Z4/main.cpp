//TP 2022/2023: LV 11, Zadatak 4
#include <iostream>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <initializer_list>

class Tim{
    char ime_tima[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;
   public:
    Tim(const char ime[]) : broj_odigranih(), broj_pobjeda(), broj_nerijesenih(), broj_poraza(), broj_datih(), broj_primljenih(), broj_poena(){
        if(strlen(ime)>20) throw std::range_error("Predugacko ime tima");
        strcpy(ime_tima, ime);
    }
    //~Tim(){std::cout<<"Pozvan je destruktor"<<std::endl;};
    void ObradiUtakmicu(int broj_datih, int broj_primljenih);
    const char *DajImeTima() const {return ime_tima;}
    int DajBrojPoena() const {return broj_poena;}
    int DajGolRazliku() const {return broj_datih-broj_primljenih;}
    void IspisiPodatke() const;
};

class Liga{
    int broj_timova;
    const int max_br_timova;
    Tim **timovi;
  public:
    explicit Liga(int velicina_lige);
    explicit Liga(std::initializer_list<Tim> lista_timova);
    ~Liga();
    Liga(const Liga &l);
    Liga(Liga &&l);
    Liga &operator =(const Liga &l);
    Liga &operator =(Liga &&l);
    void DodajNoviTim(const char ime_tima[]);
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2);
    void IspisiTabelu();
    static bool PoredakLige(Tim *t1, Tim *t2);
};

void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih){
    if(broj_datih<0 || broj_primljenih<0) throw std::range_error("Neispravan broj golova");
    Tim::broj_odigranih++;
    Tim::broj_datih+=broj_datih; 
    Tim::broj_primljenih+=broj_primljenih;
    if(broj_datih>broj_primljenih){
        Tim::broj_pobjeda++;
        Tim::broj_poena+=3;
    }
    else if(broj_datih==broj_primljenih){
        Tim::broj_nerijesenih++;
        Tim::broj_poena+=1;
    }
    else{
        Tim::broj_poraza++;
    }
}
void Tim::IspisiPodatke() const{
    std::cout<<std::setw(20)<<std::left<<Tim::DajImeTima();
    std::cout<<std::fixed<<std::setw(4)<<Tim::broj_odigranih<<std::fixed<<std::setw(4)<<Tim::broj_pobjeda<<
        std::fixed<<std::setw(4)<<Tim::broj_nerijesenih<<std::fixed<<std::setw(4)<<Tim::broj_poraza<<
        std::fixed<<std::setw(4)<<Tim::broj_datih<<std::fixed<<std::setw(4)<<Tim::broj_primljenih<<std::fixed<<std::setw(4)<<Tim::DajBrojPoena()<<std::endl;
}


Liga::Liga(int velicina_lige):max_br_timova(velicina_lige), broj_timova(){
    timovi=new Tim*[max_br_timova]{};
}
Liga::Liga(std::initializer_list<Tim> lista_timova):max_br_timova(lista_timova.size()), broj_timova(){
    timovi=new Tim*[max_br_timova]{};
    try{ 
        for(const auto &tim : lista_timova){ 
            DodajNoviTim(tim.DajImeTima());
        }
    }
    catch(...){
        for(int i=0; i<broj_timova; i++) delete timovi[i];
        delete[] timovi;
        throw;
    }
}
Liga::~Liga(){
    for(int i=0; i<broj_timova; i++) delete timovi[i]; //timovi[i] su individualni objekti strukturnog tipa, zato ih brisem sa delete a ne sa delete[] kao da su nizovi
    delete[] timovi;
}
Liga::Liga(const Liga &l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova), timovi(new Tim*[l.max_br_timova]{}) {
    try{
        for (int i = 0; i < broj_timova; i++) timovi[i] = new Tim(*l.timovi[i]);
    }
    catch(...){
        for (int i = 0; i < broj_timova; i++) delete timovi[i];
        delete[] timovi;
        throw;
    }
}
Liga::Liga(Liga &&l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova) {
    l.broj_timova = 0;
    l.timovi = nullptr;
}
Liga& Liga::operator=(const Liga &l){
    if(l.max_br_timova!=max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    if(l.broj_timova>broj_timova){
        try{
            for(int i=broj_timova; i<l.broj_timova; i++) timovi[i]=new Tim(*l.timovi[i]);
        }
        catch(...){
            for(int i=broj_timova; i<l.broj_timova; i++){
                delete timovi[i]; timovi[i]=nullptr;
            }
            throw;
        }
    }
    else{
        for(int i=l.broj_timova; i<broj_timova; i++){
            delete timovi[i]; timovi[i]=nullptr;
        }
    }
    broj_timova=l.broj_timova;
    for(int i=0; i<broj_timova; i++) *timovi[i]=*l.timovi[i];
    return *this;
}
Liga& Liga::operator=(Liga &&l){
    if(l.max_br_timova!=max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    std::swap(broj_timova, l.broj_timova);
    std::swap(timovi, l.timovi);
    return *this;
}
void Liga::DodajNoviTim(const char ime_tima[]) {
    if (broj_timova >= max_br_timova) throw std::range_error("Liga popunjena");
    for (int i = 0; i < broj_timova; i++) {
        if (strcmp(timovi[i]->DajImeTima(), ime_tima) == 0) throw std::logic_error("Tim vec postoji");
    }
    timovi[broj_timova] = new Tim(ime_tima);
    broj_timova++;
}
void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2) {
    int indeks_tim1 = -1, indeks_tim2 = -1;
    for (int i = 0; i < broj_timova; i++) {
        if (strcmp(timovi[i]->DajImeTima(), tim1) == 0) indeks_tim1 = i;
        if (strcmp(timovi[i]->DajImeTima(), tim2) == 0) indeks_tim2 = i;
    }
    if (indeks_tim1 == -1 || indeks_tim2 == -1) throw std::logic_error("Tim nije nadjen");
        
    try {
        timovi[indeks_tim1]->ObradiUtakmicu(rezultat_1, rezultat_2);
        timovi[indeks_tim2]->ObradiUtakmicu(rezultat_2, rezultat_1);
    } 
    catch (std::range_error& e) {
        throw e;
    }
}
bool Liga::PoredakLige(Tim *t1, Tim *t2){
    if (t1->DajBrojPoena() == t2->DajBrojPoena()) {
        if (t1->DajGolRazliku() == t2->DajGolRazliku()) {
                return strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0;
        }
        return t1->DajGolRazliku() > t2->DajGolRazliku();
    }
    return t1->DajBrojPoena() > t2->DajBrojPoena();
}
void Liga::IspisiTabelu() {
    std::sort(timovi, timovi + broj_timova, PoredakLige);
    for (int i = 0; i < broj_timova; i++) timovi[i]->IspisiPodatke();
}

int main (){
    try{
        Liga liga{"Borac", "Celik", "Jedinstvo", "Sarajevo", "Zeljeznicar", "Zrinjski"};
        /*liga.DodajNoviTim("Borac");
        liga.DodajNoviTim("Celik");
        liga.DodajNoviTim("Jedinstvo");
        liga.DodajNoviTim("Sarajevo");
        liga.DodajNoviTim("Zeljeznicar");
        liga.DodajNoviTim("Zrinjski");*/
        // liga.DodajNoviTim("Tim 7"); // Izaziva izuzetak jer je liga popunjena
        liga.IspisiTabelu();
        std::cout<<std::endl;
        while(true){
            std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
            char ime_tim1[20];
            char ime_tim2[20];
            std::cin.getline(ime_tim1, 20);
            //std::cout<<ime_tim1<<std::endl;
            if(strlen(ime_tim1)==0) break;
            std::cout<<"Unesite ime drugog tima: ";
            std::cin.getline(ime_tim2, 20);
            //std::cout<<ime_tim2<<std::endl;
            //if(strcmp(ime_tim1, "\n")==0) break;
            std::cout<<"Unesite broj postignutih golova za oba tima: ";
            int broj_golova1=0, broj_golova2=0;
            std::cin>>broj_golova1>>broj_golova2;
            try{
                liga.RegistrirajUtakmicu(ime_tim1, ime_tim2, broj_golova1, broj_golova2);
                std::cout<<std::endl;
                liga.IspisiTabelu();
                std::cout<<std::endl;
            }
            // liga.RegistrirajUtakmicu("Tim 1", "Tim 7", 3, 0); // Izaziva izuzetak jer tim "Tim 7" ne postoji
            catch (std::logic_error& e) {
                std::cout << e.what() << std::endl<<std::endl;
            } 
            catch (std::range_error& e) {
                std::cout << e.what() << std::endl<<std::endl;
            }
            catch (...){
                std::cout<<"Doslo je do greske!"<<std::endl<<std::endl;
            }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    catch(...){
        std::cout<<"Doslo je do greske!"<<std::endl;
    }
    return 0;
}
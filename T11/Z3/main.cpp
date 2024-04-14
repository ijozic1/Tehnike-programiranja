//TP 2022/2023: LV 11, Zadatak 3
#include <iostream>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <iomanip>

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
    auto s=std::setw(4);
    //I sad mogu umjesto svaki put std::setw(4) samo staviti s
    std::cout<<std::setw(20)<<std::left<<Tim::DajImeTima();
    std::cout<<std::fixed<<std::setw(4)<<Tim::broj_odigranih<<std::fixed<<std::setw(4)<<Tim::broj_pobjeda<<
        std::fixed<<std::setw(4)<<Tim::broj_nerijesenih<<std::fixed<<std::setw(4)<<Tim::broj_poraza<<
        std::fixed<<std::setw(4)<<Tim::broj_datih<<std::fixed<<std::setw(4)<<Tim::broj_primljenih<<std::fixed<<std::setw(4)<<Tim::DajBrojPoena()<<std::endl;

}

int main (){
    try{
        Tim t1("NK Zeljeznicar");
        Tim t2("FK Sarajevo");
        Tim t3("HSK Zrinjski");
  
        t1.ObradiUtakmicu(1, 0);
        t1.ObradiUtakmicu(3, 0);
        t1.ObradiUtakmicu(2, 1);
        t2.ObradiUtakmicu(1, 1);
        t2.ObradiUtakmicu(1, 0);
        t2.ObradiUtakmicu(0, 5);
        t3.ObradiUtakmicu(0, 1);
        t3.ObradiUtakmicu(0, 2);
        t3.ObradiUtakmicu(1, 1);
   
        t1.IspisiPodatke();
        t2.IspisiPodatke();
        t3.IspisiPodatke();
        std::cout<<std::endl;
    }
    catch(std::range_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}

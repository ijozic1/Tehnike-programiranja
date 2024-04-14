//TP 2022/2023: LV 8, Zadatak 1
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

struct Vrijeme{
    int sati, minute, sekunde;
};

void UnesiVrijeme(Vrijeme &zaUnos){
    std::cin>>zaUnos.sati>>zaUnos.minute>>zaUnos.sekunde;
}

void TestirajVrijeme(const Vrijeme &upitno){
    auto izuzetak=std::domain_error("Neispravno vrijeme");
    if(upitno.sekunde<0 || upitno.sekunde>59) throw izuzetak;
    if(upitno.minute<0 || upitno.minute>59) throw izuzetak;
    if(upitno.sati<0 || upitno.sati>23) throw izuzetak;
}

void IspisiVrijeme(const Vrijeme &trenutno){
    TestirajVrijeme(trenutno);
    std::cout<<std::setfill('0')<<std::setw(2)<<trenutno.sati<<":";
    std::cout<<std::setfill('0')<<std::setw(2)<<trenutno.minute<<":";
    std::cout<<std::setfill('0')<<std::setw(2)<<trenutno.sekunde<<std::endl;
}

Vrijeme SaberiVrijeme(const Vrijeme &prvo, const Vrijeme &drugo){
    TestirajVrijeme(prvo); TestirajVrijeme(drugo);
    Vrijeme zbir;
    zbir.sati=prvo.sati+drugo.sati; zbir.minute=prvo.minute+drugo.minute; zbir.sekunde=prvo.sekunde+drugo.sekunde;
    if(zbir.sekunde>=60){
        zbir.minute+=zbir.sekunde/60; 
        zbir.sekunde%=60;
    }
    if(zbir.minute>=60){
        zbir.sati+=zbir.minute/60; 
        zbir.minute%=60;
    }
    if(zbir.sati>=23) zbir.sati%=24; 
    return zbir;
}

int main (){
    try{
        std::cout<<"Unesite prvo vrijeme (h m s): ";
        Vrijeme prvo, drugo;
        UnesiVrijeme(prvo); TestirajVrijeme(prvo); 
        std::cout<<"Unesite drugo vrijeme (h m s): ";
        UnesiVrijeme(drugo); TestirajVrijeme(drugo);
        std::cout<<"Prvo vrijeme: ";IspisiVrijeme(prvo);
        std::cout<<"Drugo vrijeme: ";IspisiVrijeme(drugo);
        std::cout<<"Zbir vremena: ";IspisiVrijeme(SaberiVrijeme(prvo, drugo));
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}
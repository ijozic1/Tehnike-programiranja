//TP 2022/2023: LV 14, Zadatak 4
#include <iostream>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <vector>

void IzvrniDatoteku(const std::string &nazivDatoteke){
    std::ifstream ulaznaDatoteka(nazivDatoteke, std::ios::binary);
    if(!ulaznaDatoteka) throw std::logic_error("Datoteka ne postoji");

    std::ofstream pomocna("pomocna.dat", std::ios::binary);
    if(!pomocna) throw std::logic_error("Greska pri otvaranju pomocne datoteke");

    ulaznaDatoteka.seekg(0, std::ios::end);
    int velicina=ulaznaDatoteka.tellg();
    ulaznaDatoteka.seekg(0, std::ios::beg);

    if(velicina%sizeof(double)!=0) throw std::logic_error("Neispravna velicina datoteke");
    int brPodataka=velicina/sizeof(double);

    for (int i = 0; i < brPodataka; i++) {
        ulaznaDatoteka.seekg(i * sizeof(double));
        double vrijednost;
        ulaznaDatoteka.read(reinterpret_cast<char*>(&vrijednost), sizeof(double));
        pomocna.seekp((brPodataka - i - 1) * sizeof(double));
        pomocna.write(reinterpret_cast<const char*>(&vrijednost), sizeof(double));
    }

    ulaznaDatoteka.close();
    pomocna.close();

    std::remove(nazivDatoteke.c_str());
    std::rename("pomocna.dat", nazivDatoteke.c_str());
}

int main (){
    try{
        IzvrniDatoteku("test.dat");
        std::cout<<"Izvrtanje uspjesno"<<std::endl;
    }
    catch(std::logic_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}

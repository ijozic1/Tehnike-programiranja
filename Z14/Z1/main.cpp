//TP 2022/2023: LV 14, Zadatak 1
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <algorithm>

struct Mjerenja{
    std::string DatumMjerenja, komentar;
    int dan, mjesec, godina;
    std::vector<int>temperature;
    double prosjecnaTemperatura;
};

std::vector<Mjerenja> ucitajPodatke(const std::string &imeDatoteke){
    std::vector<Mjerenja> mjerenja;
    std::ifstream ulazni_tok(imeDatoteke);
    if(!ulazni_tok){
        std::cout<<"Datoteka TEMPERATURE.TXT ne postoji!"<<std::endl;
        return mjerenja;
    }
    std::string redDatoteke;
    while(std::getline(ulazni_tok, redDatoteke)){
        Mjerenja mjerenje1;
        mjerenje1.DatumMjerenja=redDatoteke;
        std::string d, m, g;
        std::istringstream datum(redDatoteke);
        std::getline(datum, d, '/');
        std::getline(datum, m, '/');
        std::getline(datum, g);
        mjerenje1.dan=std::stoi(d);
        mjerenje1.mjesec=std::stoi(m);
        mjerenje1.godina=std::stoi(g);
        if(!std::getline(ulazni_tok, redDatoteke)){
            std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<std::endl;
            return mjerenja;
        }
        mjerenje1.komentar=redDatoteke;
        if(!std::getline(ulazni_tok, redDatoteke)){
            std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<std::endl;
            return mjerenja;
        }
        std::istringstream linija(redDatoteke);
        std::string temperatura;
        while(std::getline(linija, temperatura, ',')){
            try{
                double temp=std::stod(temperatura);
                mjerenje1.temperature.push_back(temp);
            }
            catch(...){
                std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<std::endl;
                return mjerenja;
            }
        }
        double suma=0;
        for(int temp : mjerenje1.temperature) suma+=temp;
        mjerenje1.prosjecnaTemperatura=suma/mjerenje1.temperature.size();
        mjerenja.emplace_back(mjerenje1);
    }
    ulazni_tok.close();
    return mjerenja;
}

void IspisiIzvjestaj(const std::vector<Mjerenja> &mjerenja, const std::string &imeDatoteke){
    std::ofstream izlazni_tok(imeDatoteke);
    if(!izlazni_tok){
        std::cout<<"Problemi pri otvaranju datoteke IZVJESTAJ.TXT"<<std::endl;
        return;
    }
    std::vector<Mjerenja> sortirano=mjerenja;
    std::sort(sortirano.begin(), sortirano.end(), [](Mjerenja m1, Mjerenja m2){
        if(m1.godina==m2.godina && m1.mjesec==m2.mjesec && m1.dan==m2.dan) return m1.prosjecnaTemperatura<m2.prosjecnaTemperatura;
        if(m1.godina!=m2.godina) return m1.godina<m2.godina;
        if(m1.godina==m2.godina && m1.mjesec!=m2.mjesec) return m1.mjesec<m2.mjesec;
        return m1.dan<m2.dan;
    });

    for(Mjerenja m : sortirano){
        izlazni_tok<<m.komentar<<std::endl;
        for(int i=0; i<m.komentar.size(); i++) izlazni_tok<<"-";
        izlazni_tok<<std::endl<<"Datum mjerenja: "<<m.DatumMjerenja<<std::endl;
        izlazni_tok<<"Minimalna temperatura: "<<*(std::min_element(m.temperature.begin(), m.temperature.end()))<<std::endl;
        izlazni_tok<<"Maksimalna temperatura: "<<*(std::max_element(m.temperature.begin(), m.temperature.end()))<<std::endl;
        izlazni_tok<<"Prosjecna temperatura: "<<std::fixed<<std::setprecision(2)<<m.prosjecnaTemperatura<<std::endl;
        izlazni_tok<<std::endl;
    }

    izlazni_tok.close();
}

int main (){
    std::vector<Mjerenja> m=ucitajPodatke("TEMPERATURE.TXT");
    if(m.size()!=0) IspisiIzvjestaj(m, "IZVJESTAJ.TXT");
	return 0;
}

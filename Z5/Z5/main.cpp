//TP 2022/2023: Zadaća 5, Zadatak 5
#include <iostream>
#include <cmath>
#include <fstream>
#include <functional>
#include <limits>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename TipElemenata>
class DatotecniKontejner {
    std::fstream tok;
 public:
    DatotecniKontejner(const std::string &ime_datoteke);
    void DodajNoviElement(const TipElemenata &element);
    int DajBrojElemenata();
    TipElemenata DajElement(int pozicija);
    void IzmijeniElement(int pozicija, const TipElemenata &element);
    void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)> kriterij = std::less<TipElemenata>());
};

template <typename TipElemenata>
DatotecniKontejner<TipElemenata>::DatotecniKontejner(const std::string &ime_datoteke){
    std::ifstream pomocna(ime_datoteke);
    if(pomocna){
        pomocna.close(); //tok.clear();
        tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
        //tok.clear();
    }
    else{
        //tok.clear();
        tok.open(ime_datoteke, std::ios::out | std::ios::binary);
        tok.close();
        tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
        //tok.clear();
    }
    //Moglo je krace
    /*if(!pomocna){
        tok.open(ime_datoteke, std::ios::out | std::ios::binary);
        tok.close();
    }
    pomocna.close();
    tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    */
    if(!tok) throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
}

template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::DodajNoviElement(const TipElemenata &element){
    if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
    //tok.clear();
    tok.seekp(0, std::ios::end);
    tok.write(reinterpret_cast<const char*>(&element), sizeof(TipElemenata));
    tok.flush();
    tok.seekg(0, std::ios::end);
    tok.seekp(0, std::ios::end);
    //tok.clear();
}

template <typename TipElemenata>
int DatotecniKontejner<TipElemenata>::DajBrojElemenata(){
    if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
    //tok.clear();
    tok.seekg(0, std::ios::end);
    return tok.tellg()/sizeof(TipElemenata);
}

template<typename TipElemenata>
TipElemenata DatotecniKontejner<TipElemenata>::DajElement(int pozicija){
    if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
    //tok.clear();
    int brElemenata=DajBrojElemenata();
    //tok.clear();
    if(pozicija<0 || pozicija>=brElemenata) throw std::range_error("Neispravna pozicija");
    tok.seekg(pozicija*sizeof(TipElemenata), std::ios::beg);
    TipElemenata element;
    tok.read(reinterpret_cast<char*>(&element), sizeof(TipElemenata));
    //tok.clear();
    //std::cout<<element<<std::endl;
    return element;
}

template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::IzmijeniElement(int pozicija, const TipElemenata &element){
    if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
    int brElemenata=DajBrojElemenata();
    //tok.clear();
    if(pozicija<0 || pozicija>=brElemenata) throw std::range_error("Neispravna pozicija");
    tok.seekp(pozicija*sizeof(TipElemenata), std::ios::beg);
    tok.write(reinterpret_cast<const char*>(&element), sizeof(element));
    tok.flush();
    //tok.clear();
}

template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)> kriterij /*= std::less<TipElemenata>()*/){
    if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
    //tok.clear();
    int brElemenata=DajBrojElemenata();
    tok.clear();
    //std::cout<<brElemenata<<std::endl;
    if(brElemenata<=1) return;
    tok.seekg(0, std::ios::beg);
    for(int i=0; i<brElemenata-1; i++){
        //tok.seekg(i*sizeof(TipElemenata), std::ios::beg);
        TipElemenata trenutnaVrijednost=DajElement(i);
        //tok.read(reinterpret_cast<char*>(&trenutnaVrijednost), sizeof(TipElemenata));
        //tok.clear();
        for(int j=i+1; j<brElemenata; j++){
            //tok.seekg(j*sizeof(TipElemenata), std::ios::beg);
            TipElemenata sljedecaVrijednost=DajElement(j);
            //tok.read(reinterpret_cast<char*>(&sljedecaVrijednost), sizeof(TipElemenata));
            //tok.clear();
            //std::cout<<trenutnaVrijednost<<"  "<<sljedecaVrijednost<<std::endl;
            if(kriterij(sljedecaVrijednost,trenutnaVrijednost)){
                //tok.seekp(i*sizeof(TipElemenata), std::ios::beg);
                //tok.write(reinterpret_cast<const char*>(&sljedecaVrijednost), sizeof(TipElemenata));
                //tok.flush(); tok.clear();
                //tok.seekp(j*sizeof(TipElemenata), std::ios::beg);
                //tok.write(reinterpret_cast<const char*>(&trenutnaVrijednost), sizeof(TipElemenata));
                //tok.flush(); tok.clear();
                //tok.clear();
                IzmijeniElement(j,trenutnaVrijednost);
                //tok.clear();
                IzmijeniElement(i,sljedecaVrijednost);
                //tok.clear();
                trenutnaVrijednost=sljedecaVrijednost;
                sljedecaVrijednost=DajElement(j);
            }
        }
    }
    /*for(int i=0; i<brElemenata-1; i++){
        for(int j=i+1; j<brElemenata; j++){
            TipElemenata trenutnaVrijednost=DajElement(i);
            if(kriterij(DajElement(j),DajElement(i))){
                IzmijeniElement(i, DajElement(j));
                IzmijeniElement(j, trenutnaVrijednost);
            }
        }
    }*/
}

int main (){
    try{
        std::vector<double> podaci={11,52,32,19,88.3,7,2,47};
        std::ofstream izlazni_tok("datoteka.bin", std::ios::binary);
        if(!izlazni_tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
        izlazni_tok.write(reinterpret_cast<const char*>(&podaci[0]), podaci.size()*sizeof(double));
        izlazni_tok.flush();
        izlazni_tok.close();
        DatotecniKontejner <double> kontejner("datoteka.bin");
        kontejner.Sortiraj();
        kontejner.DodajNoviElement(0);
        std::ifstream ulazni_tok("datoteka.bin", std::ios::binary);
        ulazni_tok.seekg(0, std::ios::beg);
        std::vector<double>pomocni(9);
        ulazni_tok.read(reinterpret_cast<char*>(&pomocni[0]), sizeof(double)*pomocni.size());
        std::cout<<kontejner.DajElement(3)<<std::endl;
        std::cout<<kontejner.DajBrojElemenata()<<std::endl;
        ulazni_tok.close();
        for(double broj : pomocni) std::cout<<broj<<" ";
        kontejner.IzmijeniElement(3, 6);
        kontejner.Sortiraj([](int a, int b){return a>b;});
        ulazni_tok.open("datoteka.bin", std::ios::binary);
        ulazni_tok.read(reinterpret_cast<char*>(&pomocni[0]),sizeof(double)*pomocni.size());
        ulazni_tok.close();
        std::cout<<std::endl;
        for(double broj : pomocni) std::cout<<broj<<" ";
        kontejner.Sortiraj(std::greater<double>());
    }
    catch(std::exception &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}
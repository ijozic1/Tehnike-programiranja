//TP 2022/2023: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <set>
#include <stdexcept>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::set<std::tuple<std::string, int, int>> Skup;
typedef std::map<std::string, Skup> IndeksPojmova;

IndeksPojmova KreirajIndeksPojmova(const Knjiga &TekstZaAnalizu){
    IndeksPojmova mapaIndeksa;
    for(const auto &par: TekstZaAnalizu){
        const std::string &poglavlje=par.first;
        const std::vector<std::string> &stranice=par.second;
        for(int i=0; i<stranice.size(); i++){
            const std::string &stranica=stranice[i];
            int pozicija=0;
            std::string rijec="";
            for(int j=0; j<stranica.length(); j++){
                if(std::isalnum(stranica[j])) rijec+=stranica[j];
                else{
                    if(rijec.length()>0){
                        std::string RijecMalimSlovima;
                        for(char znak : rijec) RijecMalimSlovima+=std::tolower(znak);
                        mapaIndeksa[RijecMalimSlovima].insert(std::make_tuple(poglavlje, i+1, pozicija));
                        pozicija+=rijec.length()+1;
                        rijec="";
                        
                    }
                }
            }
            if(rijec.length()>0){
                std::string RijecMalimSlovima="";
                for (char znak : rijec) RijecMalimSlovima+=std::tolower(znak);
                mapaIndeksa[RijecMalimSlovima].insert(std::make_tuple(poglavlje, i+1, pozicija));
            }
        }
    }
    return mapaIndeksa;
}

Skup PretraziIndeksPojmova(const std::string &rijec, const IndeksPojmova &mapaIndeksa){
    std::string RijecMalimSlovima="";
    for(char znak : rijec) RijecMalimSlovima+=std::tolower(znak);
    if(mapaIndeksa.find(RijecMalimSlovima)!=mapaIndeksa.end()) return mapaIndeksa.at(RijecMalimSlovima);
    throw std::logic_error("Pojam nije nadjen");
}

void IspisiIndeksPojmova(const IndeksPojmova &mapaIndeksa){
    for(const auto &par : mapaIndeksa){
        std::cout<<par.first<<": ";
        const auto &pozicija= par.second;
        auto iterator=pozicija.begin();
        auto posljednji=pozicija.end();
        posljednji--;
        while(iterator!=pozicija.end()){
            std::cout<<std::get<0>(*iterator)<<"/"<<std::get<1>(*iterator)<<"/"<<std::get<2>(*iterator);
            if(iterator!=posljednji) std::cout<<", ";
            iterator++;
        }
        std::cout<<std::endl;
    }
}

int main (){
    Knjiga knjiga;
    while(true){
        std::cout<<"\nUnesite naziv poglavlja: ";
        std::string NazivPoglavlja="";
        std::getline(std::cin, NazivPoglavlja);
        if(NazivPoglavlja!="."){
            knjiga[NazivPoglavlja];
            int stranica=1;
            while(true){
                std::cout<<"\nUnesite sadrzaj stranice "<<stranica<<": ";
                std::string SadrzajStranice="";
                std::getline(std::cin, SadrzajStranice);
                if(SadrzajStranice!="."){
                    knjiga[NazivPoglavlja].push_back(SadrzajStranice);
                    stranica++;
                }
                else break;
            }
        }
        else break;
    }
    IndeksPojmova mapaIndeksa=KreirajIndeksPojmova(knjiga);
    std::cout<<std::endl<<"Kreirani indeks pojmova: "<<std::endl;
    IspisiIndeksPojmova(mapaIndeksa);
    std::cout<<std::endl;

    while(true){
        std::cout<<"\nUnesite rijec: ";
        std::string rijec="";
        std::getline(std::cin, rijec);
        if(rijec==".") break;
        try{
            Skup pronadjen=PretraziIndeksPojmova(rijec, mapaIndeksa);
            for(const auto &pozicija : pronadjen)
                std::cout<<std::get<0>(pozicija)<<"/"<<std::get<1>(pozicija)<<"/"<<std::get<2>(pozicija)<<" ";
        }
        catch(std::logic_error &izuzetak){
            std::cout<<"\nUnesena rijec nije nadjena!"<<std::endl;
        }
    }
	return 0;
}
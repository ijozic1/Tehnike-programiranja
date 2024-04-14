//TP 2022/2023: Zadaća 4, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <map>
#include <memory>

class Korisnik{
    int clanskiBrojKorisnika;
    std::string ImeIPrezimeKorisnika, AdresaKorisnika, TelefonKorisnika;
  public:
    Korisnik(int cl_broj, std::string ime_prezime, std::string adresa, std::string telefon): clanskiBrojKorisnika(cl_broj), 
        ImeIPrezimeKorisnika(ime_prezime), AdresaKorisnika(adresa), TelefonKorisnika(telefon) {}
    int DajClanskiBroj()const {return clanskiBrojKorisnika;}
    std::string DajImeIPrezime()const {return ImeIPrezimeKorisnika;}
    std::string DajAdresu() const {return AdresaKorisnika;}
    std::string DajTelefon() const {return TelefonKorisnika;}
    void Ispisi() const{
        std::cout<<"Clanski broj: "<<DajClanskiBroj()<<"\nIme i prezime: "<<DajImeIPrezime()<<"\nAdresa: "<<DajAdresu()<<"\nTelefon: "<<DajTelefon()<<std::endl;
    }
};

class Film{
    int EvidencijskiBrojFilma, GodinaIzdavanjaFilma;
    bool TrakaIliDVD; //ako je true onda je DVD, a ako je false onda je VideoTraka
    Korisnik *KorisnikKojiJeZaduzioFilm;
    std::string NazivFilma, ZanrFilma;
  public:
    Film(int ev_broj, bool naCemuJe, std::string naziv, std::string zanr, int god_izdavanja): EvidencijskiBrojFilma(ev_broj), 
        GodinaIzdavanjaFilma(god_izdavanja), TrakaIliDVD(naCemuJe), NazivFilma(naziv), ZanrFilma(zanr){ KorisnikKojiJeZaduzioFilm=nullptr; }
    int DajEvidencijskiBroj() const {return EvidencijskiBrojFilma;}
    std::string DajNaziv() const{return NazivFilma;}
    std::string DajZanr() const {return ZanrFilma;}
    int DajGodinuProdukcije() const{return GodinaIzdavanjaFilma;}
    bool DaLiJeDVD() const {return TrakaIliDVD;}
    void ZaduziFilm(Korisnik &k){ KorisnikKojiJeZaduzioFilm=&k;}
    void RazduziFilm(){ KorisnikKojiJeZaduzioFilm=nullptr;}
    bool DaLiJeZaduzen() const{
        if(KorisnikKojiJeZaduzioFilm!=nullptr) return true;
        return false;
    }
    Korisnik & DajKodKogaJe(){
        if(KorisnikKojiJeZaduzioFilm==nullptr) throw std::domain_error("Film nije zaduzen");
        return *KorisnikKojiJeZaduzioFilm;
    }
    Korisnik * DajPokKodKogaJe() const{return KorisnikKojiJeZaduzioFilm;}
    void Ispisi() const;
};

class Videoteka{
    std::map<int, std::shared_ptr<Korisnik>> Korisnici_mapa;
    std::map<int, std::shared_ptr<Film>> Filmovi_mapa;
  public:
    Videoteka()=default;
    Videoteka(const Videoteka &v);
    Videoteka &operator=(const Videoteka &v);
    Videoteka &operator=(Videoteka &&v);
    void RegistrirajNovogKorisnika(int cl_broj, std::string ime_prezime, std::string adresa, std::string telefon);
    void RegistrirajNoviFilm(int ev_broj, bool naCemuJe, std::string naziv, std::string zanr, int god_izdavanja);
    Korisnik &NadjiKorisnika(const int cl_broj) const;
    Film &NadjiFilm(const int ev_broj) const;
    void IzlistajKorisnike() const;
    void IzlistajFilmove() const;
    void ZaduziFilm(int ev_broj, int cl_broj);
    void RazduziFilm(int ev_broj);
    void PrikaziZaduzenja(int cl_broj) const;
};

void Film::Ispisi() const{
    std::cout<<"Evidencijski broj: "<<DajEvidencijskiBroj()<<"\nMedij: ";
    if(DaLiJeDVD()) std::cout<<"DVD";
    else std::cout<<"Video traka";
    std::cout<<"\nNaziv filma: "<<DajNaziv()<<"\nZanr: "<<DajZanr()<<"\nGodina produkcije: "<<DajGodinuProdukcije()<<std::endl;
}

Videoteka::Videoteka(const Videoteka &v){
    for(const auto &korisnik : v.Korisnici_mapa) Korisnici_mapa[korisnik.first]=std::make_shared<Korisnik>(*korisnik.second);
    for(const auto &film : v.Filmovi_mapa) Filmovi_mapa[film.first]=std::make_shared<Film>(*film.second);
}

Videoteka & Videoteka::operator=(const Videoteka &v){
    for(const auto &korisnik : v.Korisnici_mapa) Korisnici_mapa[korisnik.first]=std::make_shared<Korisnik>(*korisnik.second);
    for(const auto &film : v.Filmovi_mapa) Filmovi_mapa[film.first]=std::make_shared<Film>(*film.second);
    return *this;
}

Videoteka & Videoteka::operator=(Videoteka &&v){
    Korisnici_mapa=std::move(v.Korisnici_mapa);
    Filmovi_mapa=std::move(v.Filmovi_mapa);
    return *this;
}

void Videoteka::RegistrirajNovogKorisnika(int cl_broj, std::string ime_prezime, std::string adresa, std::string telefon){
    auto it=Korisnici_mapa.find(cl_broj);
    if(it!=Korisnici_mapa.end()) throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
    std::shared_ptr<Korisnik> noviKorisnik=std::make_shared<Korisnik>(cl_broj, ime_prezime, adresa, telefon);
    Korisnici_mapa[cl_broj]=noviKorisnik;
}

void Videoteka::RegistrirajNoviFilm(int ev_broj, bool naCemuJe, std::string naziv, std::string zanr, int god_izdavanja){
    auto it=Filmovi_mapa.find(ev_broj);
    if(it!=Filmovi_mapa.end()) throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
    std::shared_ptr<Film> noviFilm=std::make_shared<Film>(ev_broj, naCemuJe, naziv, zanr, god_izdavanja);
    Filmovi_mapa[ev_broj]=noviFilm;
}

Korisnik &Videoteka::NadjiKorisnika(const int cl_broj)const{
    auto it=Korisnici_mapa.find(cl_broj);
    if(it==Korisnici_mapa.end()) throw std::logic_error("Korisnik nije nadjen");
    return *(it->second);
}

Film &Videoteka::NadjiFilm(const int ev_broj) const{
    auto it=Filmovi_mapa.find(ev_broj);
    if(it==Filmovi_mapa.end()) throw std::logic_error("Film nije nadjen");
    return *(it->second);
}

void Videoteka::IzlistajKorisnike() const{
    for(const auto &korisnik : Korisnici_mapa){
        korisnik.second->Ispisi();
        std::cout<<std::endl;
    }
}

void Videoteka::IzlistajFilmove() const{
    for(const auto &film : Filmovi_mapa){
        film.second->Ispisi();
        if(film.second->DaLiJeZaduzen()){
            auto pok=film.second->DajPokKodKogaJe();
            std::cout<<"Zaduzen kod korisnika: "<<pok->DajImeIPrezime()<<" ("<<film.second->DajEvidencijskiBroj()<<")\n";
        }
        std::cout<<std::endl;
    }
}

void Videoteka::ZaduziFilm(int ev_broj, int cl_broj){
    auto film_iterator=Filmovi_mapa.find(ev_broj);
    if(film_iterator==Filmovi_mapa.end()) throw std::logic_error("Film nije nadjen");
    auto korisnik_iterator=Korisnici_mapa.find(cl_broj);
    if(korisnik_iterator==Korisnici_mapa.end()) throw std::logic_error("Korisnik nije nadjen");
    if(film_iterator->second->DaLiJeZaduzen()) throw std::logic_error("Film vec zaduzen");
    film_iterator->second->ZaduziFilm(*korisnik_iterator->second);
}

void Videoteka::RazduziFilm(int ev_broj){
    auto film_iterator=Filmovi_mapa.find(ev_broj);
    if(film_iterator==Filmovi_mapa.end()) throw std::logic_error("Film nije nadjen");
    if(!film_iterator->second->DaLiJeZaduzen()) throw std::logic_error("Film nije zaduzen");
    film_iterator->second->RazduziFilm();
}

void Videoteka::PrikaziZaduzenja(int cl_broj) const{
    auto korisnik_iterator=Korisnici_mapa.find(cl_broj);
    if(korisnik_iterator==Korisnici_mapa.end()) throw std::logic_error("Korisnik nije nadjen");
    std::shared_ptr<Korisnik> korisnik=korisnik_iterator->second;
    bool zaduzenja_postoje=false;

    for(const auto &film : Filmovi_mapa){
        std::shared_ptr<Film> pok_na_film=film.second;
        if(pok_na_film->DaLiJeZaduzen() && pok_na_film->DajKodKogaJe().DajClanskiBroj()==korisnik->DajClanskiBroj()){
            pok_na_film->Ispisi();
            std::cout<<std::endl;
            zaduzenja_postoje=true;
        }
    }
    if(!zaduzenja_postoje) std::cout<<"Korisnik nema zaduzenja!"<<std::endl;
}

int main (){
    Videoteka v;
    int opcija=0;
    do{
        std::cout<<"MENI VIDEOTEKE:"<<std::endl;
        std::cout<<"1. Registriraj novog korisnika"<<std::endl;
        std::cout<<"2. Registriraj novi film"<<std::endl;
        std::cout<<"3. Madji korisnika"<<std::endl;
        std::cout<<"4. Nadji film"<<std::endl;
        std::cout<<"5. Izlistaj korisnike"<<std::endl;
        std::cout<<"6. Izlistaj filmove"<<std::endl;
        std::cout<<"7. Zaduzi film"<<std::endl;
        std::cout<<"8. Razduzi film"<<std::endl;
        std::cout<<"9. Prikazi zaduzenja"<<std::endl;
        std::cout<<"10. Zavrsi program"<<std::endl<<std::endl;
        std::cout<<"Izaberite opciju: ";
        std::cin>>opcija;
        int cl_broj=0, ev_broj=0;

    
        if(opcija==1){
            std::string ime_i_prezime, adresa, telefon;
            std::cout<<"Unesite ime i prezime korisnika: ";
            std::getline(std::cin, ime_i_prezime);
            std::cout<<"Unesite adresu korisnika: ";
            std::getline(std::cin, adresa);
            std::cout<<"Unesite telefon korisnika: ";
            std::getline(std::cin, telefon);
            std::cout<<"Unesite clanski broj: ";
            std::cin>>cl_broj;
            try{
                v.RegistrirajNovogKorisnika(cl_broj, ime_i_prezime, adresa, telefon);
                std::cout<<"Registracija uspjesna!"<<std::endl<<std::endl;
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
            }
        }
        else if(opcija ==2){
            std::string naziv, zanr;
            int god_izdavanja=0;
            bool na_dvd=false;
            std::cout<<"Unesite evidencijski broj filma: ";
            std::cin>>ev_broj;
            std::cout<<"Unesite naziv filma: ";
            std::getline(std::cin, naziv);
            std::cout<<"Unesite zanr: ";
            std::getline(std::cin, zanr);
            std::cout<<"Unesite godinu izdavanja: ";
            std::cin>>god_izdavanja;
            std::cout<<"Da li je na DVD (1-da, 0 - ne): ";
            std::cin>>na_dvd;
            try{
                v.RegistrirajNoviFilm(ev_broj, na_dvd, naziv, zanr, god_izdavanja);
                std::cout<<"Film je uspjesno dodan!"<<std::endl<<std::endl;
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
            }
        }
        else if(opcija==3){
            std::cout<<"Unesite clasnki broj korisnika: ";
            std::cin>>cl_broj;
            try{
                const Korisnik &korisnik=v.NadjiKorisnika(cl_broj);
                korisnik.Ispisi();
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
            }
        }
        else if(opcija==4){
            std::cout<<"Unesite evidencijski broj filma: ";
            std::cin>>ev_broj;
            try{
                const Film &film=v.NadjiFilm(ev_broj);
                film.Ispisi();
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
            }
        }
        else if(opcija==5){
            std::cout<<"Lista korisnika:"<<std::endl;
            v.IzlistajKorisnike();
            std::cout<<std::endl;
        }
        else if(opcija==6){
            std::cout<<"Lista filmova:"<<std::endl;
            v.IzlistajFilmove();
            std::cout<<std::endl;
        }
        else if(opcija==7){
            std::cout<<"Unesite evidncijski broj filma: ";
            std::cin>>ev_broj;
            std::cout<<"Unesite clanski broj korisnik: ";
            std::cin>>cl_broj;
            try{
                v.ZaduziFilm(ev_broj, cl_broj);
                std::cout<<"Film uspjesno zaduzen"<<std::endl;
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
            }
        }
        else if(opcija ==8){
            std::cout<<"Unesite evidencijski broj filma: ";
            std::cin>>ev_broj;
            try{
                v.RazduziFilm(ev_broj);
                std::cout<<"Film uspjesno razduzen!"<<std::endl;
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
            }
        }
        else if(opcija==9){
            std::cout<<"Unesite clasnki broj korisnika: ";
            std::cin>>cl_broj;
            try{
                v.PrikaziZaduzenja(cl_broj);
            }
            catch(std::logic_error &izuzetak){
                std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
            }
        }
        else if(opcija==10) std::cout<<"Dovidjenja."<<std::endl;
        else std::cout<<"Unesena opcija ne postoji, unesite ponovo!"<<std::endl;
    }while(opcija!=10);
	return 0;
}

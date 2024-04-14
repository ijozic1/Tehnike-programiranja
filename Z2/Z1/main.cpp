//TP 2022/2023: Zadaća 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

std::vector<std::vector<char>>Polje(21,std::vector<char>(61,' '));
bool vidljivost=true, bioVidljiv=true;
enum class Pravci{Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
enum class KodoviGresaka{PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande{Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj};

void Idi(int &x, int &y, Pravci orjentacija, int korak){
    std::vector<int>dx{0,1,1,1,0,-1,-1,-1};
    std::vector<int>dy{-1,-1,0,1,1,1,0,-1};
    if(bioVidljiv)Polje.at(y+10).at(x+30)='*';
    else Polje.at(y+10).at(x+30)=' ';
    bioVidljiv=vidljivost;
    x+=30; y+=10;
    while(korak!=0){
        if(korak<0){
            x+=dx[(int(orjentacija)+4)%8];
            y+=dy[(int(orjentacija)+4)%8];
            korak++;
        }
        else{
            x+=dx.at(int(orjentacija));
            y+=dy.at(int(orjentacija));
            korak--;
        }
        if(x>=61) x=0; 
        if(x<0) x=60;
        if(y>=21) y=0; 
        if(y<0) y=20;
        if(vidljivost) Polje.at(y).at(x)='*';
    }
    Polje.at(y).at(x)='O';
    x-=30; y-=10;
}

void Rotiraj(Pravci &orjentacija, int ugao){
    orjentacija=static_cast<Pravci>((int(orjentacija)-ugao+80)%8);
}

void PostaviVidljivost(bool vidljiv){
    vidljivost=vidljiv;
    if(vidljivost) bioVidljiv=true;
}

void IspisiPoziciju(int x, int y, Pravci orjentacija){
    const char *Orjentacije[8]{"sjever", "sjeveroistok", "istok", "jugoistok", "jug", "jugozapad", "zapad", "sjeverozapad"};
    const char *Vidljivost[2]{"nevidljiv", "vidljiv"};
    std::cout<<"Robot je "<<Vidljivost[int(vidljivost)]<<", nalazi se na poziciji ("<<x<<","<<y*(-1)<<") i gleda na "<<Orjentacije[int(orjentacija)]<<"."<<std::endl;
}

void PrikaziTeren(){
    for(int i=0; i<23; i++){
        for(int j=0; j<63; j++){
            if(i==0 || j==0 || i==22 || j==62) std::cout<<'#';
            else std::cout<<Polje.at(i-1).at(j-1);
        }
        std::cout<<std::endl;
    }
}

void PrijaviGresku(KodoviGresaka kod_greske){
    const char *Greske[4]{"Nerazumljiva komanda!", "Komanda trazi parametar koji nije naveden!",
    "Zadan je suvisan parametar nakon komande!", "Parametar komande nije ispravan!"};
    std::cout<<Greske[int(kod_greske)]<<std::endl;
}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orjentacija){
    if(int(komanda)==0) Idi(x,y,orjentacija,parametar);
    else if(int(komanda)==1) Rotiraj(orjentacija, parametar);
    else if(int(komanda)==2) PostaviVidljivost(false);
    else if(int(komanda)==3) PostaviVidljivost(true);
    else if(int(komanda)==4) PrikaziTeren();
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greska){
    std::cout<<"Unesi komandu: ";
    char znak=' ';
    while(std::cin.get(znak), znak!='\n'){
        if(znak!=' ' && znak!='I' && znak!='R' && znak!='S' && znak!='T' && znak!='K'){
            kod_greska=KodoviGresaka::PogresnaKomanda;
            std::cin.clear(); std::cin.ignore(1000, '\n'); return false;
        }
        else if(znak!=' ' && (znak=='I' || znak=='R' || znak=='S' || znak=='T' || znak=='K')){
            if(znak=='T' || znak=='K'){
                if(znak=='T') komanda=Komande::PrikaziTeren;
                else komanda=Komande::Kraj;
            }
            else if(znak=='S'){
                znak=std::cin.get();
                while(znak==' ' && znak!='\n') std::cin.get(znak);
                if(znak=='+') komanda=Komande::Sakrij;
                else if(znak=='-') komanda=Komande::Otkrij;
                else if(znak=='\n'){
                    kod_greska=KodoviGresaka::NedostajeParametar;
                    std::cin.clear(); std::cin.ignore(100,'\n'); return false;
                }
                else{
                    kod_greska=KodoviGresaka::PogresnaKomanda;
                    std::cin.clear(); std::cin.ignore(100, '\n');return false;
                }
            }
            else if(znak=='I' || znak=='R'){
                if(znak=='I') komanda=Komande::Idi;
                else komanda=Komande::Rotiraj;
                znak=std::cin.get();
                while(znak==' ' && znak!='\n') std::cin.get(znak);
                if(znak=='\n'){
                    kod_greska=KodoviGresaka::NedostajeParametar;
                    return false;
                }
                else if(!isdigit(znak) && znak!='-'){
                    kod_greska=KodoviGresaka::NeispravanParametar;
                    std::cin.clear(); std::cin.ignore(100, '\n'); return false;
                }
                int predznak=1, broj=0;
                if(znak=='-'){
                    predznak=-1;
                    znak=std::cin.get();
                }
                while(isdigit(znak)){
                    broj=broj*10+(znak-'0');
                    if(std::cin.peek()!='\n') std::cin.get(znak);
                    else break;
                }
                if(!isdigit(znak) && znak!=' '){
                    kod_greska=KodoviGresaka::NeispravanParametar;
                    std::cin.clear(); std::cin.ignore(100, '\n'); return false;
                }
                parametar=broj*predznak;
                if(std::cin.peek()=='\n') return true; 
            }
            znak=std::cin.peek();
            while(znak==' ' && znak!='\n') std::cin.get(znak);
            if(znak=='\n')return true;
            kod_greska=KodoviGresaka::SuvisanParametar;
            std::cin.clear(); std::cin.ignore(100, '\n'); return false;
        }
    }
    kod_greska=KodoviGresaka::PogresnaKomanda;
    std::cin.clear(); std::cin.ignore(100, '\n'); return false;
}

int main (){
    Komande komanda=Komande::Kraj;
    KodoviGresaka greska=KodoviGresaka::PogresnaKomanda;
    Pravci orjentacija=Pravci::Sjever;
    //Robota pozicioniram u gornji lijevi ugao polja    
    int x=0, y=0, parametar=0;
    Polje.at(y+10).at(x+30)='O';
    IspisiPoziciju(x, y,orjentacija);
    while(true){
        if(!UnosKomande(komanda, parametar, greska)) PrijaviGresku(greska);
        else if(int(komanda)==5){
            std::cout<<"Dovidjenja!"; break;
        }
        else{
            IzvrsiKomandu(komanda,parametar,x,y,orjentacija);
            if(komanda!=Komande::PrikaziTeren)IspisiPoziciju(x,y,orjentacija);
            std::cin.clear(); std::cin.ignore(100, '\n');
        }
    }
	return 0;
}
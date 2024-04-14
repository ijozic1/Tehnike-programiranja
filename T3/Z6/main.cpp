//TP 2022/2023: LV 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

typedef std::vector<std::vector<int>> Matrica;

Matrica KroneckerovProizvod(std::vector<int>a, std::vector<int>b){
    Matrica m(a.size(), std::vector<int>(b.size()));
    if(a.size()==0 || b.size()==0) return m;
    for(int i=0; i<a.size(); i++){
        for(int j=0; j<b.size(); j++){
            m[i][j]=a[i]*b[j];
        }
    }
    return m;
}

int BrojCifara(int broj){
    if(broj==0)return 0;
    else return 1+BrojCifara(broj/10);
}

int NajvecaSirina(Matrica m){
    int max_sirina=0;
    if(m.size()==0 || m[0].size()==0) return 0;
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m[i].size(); j++){
            int broj= m[i][j];
            int predznak=0;
            int sirina=0;
            if(broj<0) predznak=1;
            sirina=BrojCifara(abs(broj));

            if(sirina+predznak>max_sirina) max_sirina=sirina+predznak;
        }
    }
    return max_sirina;
}

std::vector<int>UnesiElemente(std::vector<int>v){
    for(int i=0; i<v.size(); i++)
        std::cin>>v[i];
    return v;
}


int main (){
    int brRedova;
    std:: cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>brRedova;
    if(brRedova<0){
        std::cout<<"Pogresne dimenzije!";
        return 0;
    }
    std::vector<int>a(brRedova);
    std:: cout<<"Unesite elemente prvog vektora: ";
    a=UnesiElemente(a);

    int brKolona;
    std:: cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>brKolona;
    if(brKolona<0){
        std::cout<<"Pogresne dimenzije!";
        return 0;
    }
    std::vector<int>b(brKolona);
    std:: cout<<"Unesite elemente drugog vektora: ";
    b=UnesiElemente(b);

    Matrica m=KroneckerovProizvod(a,b);
    int sirina_ispisa=NajvecaSirina(m)+1;
    
    std::cout<<std::endl;
    for(int i=0; i<brRedova; i++){
        for(int j=0; j<brKolona; j++){
            std::cout<<std::setw(sirina_ispisa)<<m[i][j];
        }
        std::cout<<std::endl;
    }

	return 0;
}

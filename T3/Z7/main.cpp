//TP 2022/2023: LV 3, Zadatak 7
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

typedef std::vector<std::vector<int>> Matrica;

int NajvecaSirina(Matrica m){
    int max_sirina=0;
    if(m.size()==0 || m[0].size()==0) return 0;
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m[i].size(); j++){
            int broj= m[i][j];
            int predznak=0;
            int sirina=0;
            if(broj<0) predznak=1;
            do{
                sirina++;
                broj/=10;
            }while(broj!=0);

            if(sirina+predznak>max_sirina) max_sirina=sirina+predznak;
        }
    }
    return max_sirina;
}

Matrica KreirajMatricu(int n){
    Matrica m;
    m.resize(n);
    for(int i=0; i<n; i++) m[i].resize(i+1);
    return m;
}

Matrica PascalovTrougao(int n){
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    Matrica mat=KreirajMatricu(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<mat[i].size(); j++){
            if(j==0 || i==j) mat[i][j]=1;
            else mat[i][j]=mat[i-1][j-1]+mat[i-1][j];
        }
    }
    return mat;
}

int main (){
    int n;
    std::cout<<"Unesite broj redova: ";
    std::cin>>n;
    try{
        Matrica m=PascalovTrougao(n);
        int sirina_ispisa=NajvecaSirina(m)+1;
    
        std::cout<<std::endl;
        for(int i=0; i<m.size(); i++){
            for(int j=0; j<m[i].size(); j++){
                std::cout<<std::setw(sirina_ispisa)<<m[i][j];
            }
            std::cout<<std::endl;
        }
    }
    catch(std:: domain_error izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }

	return 0;
}

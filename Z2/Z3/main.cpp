//TP 2022/2023: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <string>
#include <iomanip>

typedef std::vector<std::vector<std::string>> Matrica;

std::string FunkcijaF(std::string prvi, std::string drugi){return prvi+"+"+drugi;}
std::string FunkcijaG(std::string prvi, std::string drugi){return prvi+"*"+drugi;}

int SirinaIspisa(std::vector<std::vector<std::string>> &C){
    int max_sirina=0;
    for(int i=0; i<C.size(); i++){
        for(int j=0; j<C.at(i).size(); j++)
            if(C.at(i).at(j).length()>max_sirina) max_sirina=C.at(i).at(j).length();
    }
    return max_sirina+1;
}

template<typename TipA, typename TipB, typename FunTip1, typename FunTip2>
auto GeneraliziraniMatricniProizvod(std::vector<std::vector<TipA>> &A, std::vector<std::vector<TipB>>&B, FunTip1 f/*(FunTip, FunTip)*/, FunTip2 g/*(TipA, TipB)*/)
    /*->std::remove_reference_t<decltype(g(A.at(0).at(0),B.at(0).at(0)))>*/{
    if(A.at(0).size()!=B.size()){
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
    using TipC=std::remove_reference_t<decltype(g(A.at(0).at(0), B.at(0).at(0)))>;
    if(A.size()!=0 && B.size()==0) return std::vector<std::vector<TipC>>(A.size());
    int m=A.size(), n=B.size(), p=B.at(0).size();
    //Test za grbave ili prazne matrice
    for(int i=1; i<A.size(); i++)
        if(A.at(i-1).size()!=A.at(i).size()) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    for(int i=1; i<B.size(); i++)
        if(B.at(i-1).size()!=B.at(i).size()) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    std::vector<std::vector<TipC>>C(m,std::vector<TipC>(p));
    try{
        for(int i=0; i<m; i++){
            for(int j=0; j<p; j++){
                int k=0;
                C.at(i).at(j)=g(A.at(i).at(k), B.at(k).at(j));
                for(k=1; k<n; k++){
                    C.at(i).at(j)=f(C.at(i).at(j), g(A.at(i).at(k), B.at(k).at(j)));
                }
            }
        }
    }
    catch(...){
        throw std::runtime_error("Neocekivani problemi pri racunanju");
    }
    return C;
}

int main (){
    std::cout<<"Unesite broj redova prve matrice: ";
    int m=0, n=0, p=0;
    std::cin>>m;
    std::cout<<"Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
    std::cin>>n;
    std::cout<<"Unesite broj kolona druge matrice: ";
    std::cin>>p;
    try{
        std::cout<<"\nUnesite elemente prve matrice: "<<std::endl;
        Matrica A(m,std::vector<std::string>(n)), B(n,std::vector<std::string>(p));
        //Kako su u pitanju rijeci, to mozemo unositi sa cin-om jer ce stati na prvom razmaku
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                std::cin>>A.at(i).at(j);
                if(i!=m-1 && j!=n-1)std::cin>>std::ws;
            }
        }
        std::cout<<"Unesite elemente druge matrice: "<<std::endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<p; j++){
                std::cin>>B.at(i).at(j);
                if(i!=n-1 && j!=p-1)std::cin>>std::ws;
            }
        }
        //auto C=GeneraliziraniMatricniProizvod(A, B, [](std::string a, std::string b){return a+"+"+b;}, [](std::string a, std::string b){return a+"*"+b;});
        auto C=GeneraliziraniMatricniProizvod(A,B, FunkcijaF, FunkcijaG);
        int sirinaIspisa=SirinaIspisa(C);
        std::cout<<"\n\nMatricni proizvod:\n";
        for(int i=0; i<m; i++){
            for(int j=0; j<p; j++){
                std::cout<<std::left<<std::setw(sirinaIspisa)<<C.at(i).at(j);
            }
            std::cout<<std::endl;
        }
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    catch(std::runtime_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}
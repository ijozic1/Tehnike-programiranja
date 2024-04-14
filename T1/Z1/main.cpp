//TP 2016/2017: LV 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
    std:: cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    int a, b, c;
    std:: cin>>a>>b>>c;
    std:: cout<<"Unesite sirinu plocice u centimetrima: ";
    int plocica;
    std:: cin>>plocica;

    a*=100;
    b*=100;
    c*=100;
    
    double povrsina_bazena=a*b+2*(a*c+b*c);
    double povrsina_plocice=plocica*plocica;
    double broj_plocica=static_cast<double>(povrsina_bazena)/povrsina_plocice;

    std:: cout<<std::endl;

    double broj_po_visini=static_cast<double>(c)/plocica;
    double broj_po_sirini=static_cast<double>(b)/plocica;
    double broj_po_duzini=static_cast<double>(a)/plocica;
    
    if(broj_po_visini!=static_cast<int>(broj_po_visini) || broj_po_sirini!=static_cast<int>(broj_po_sirini) || broj_po_duzini!=static_cast<int>(broj_po_duzini)){
        std:: cout<<"Poplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "<<plocica<<"x"<<plocica<<"cm nije izvodljivo bez lomljenja plocica!"<<std::endl;
    }
    else{
        if(broj_plocica!=static_cast<int>(broj_plocica)){
            std:: cout<<"Poplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "<<plocica<<"x"<<plocica<<"cm nije izvodljivo bez lomljenja plocica!"<<std::endl;
        }
        else{
            std:: cout<<"Za poplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "<<plocica<<"x"<<plocica<<"cm\npotrebno je "<<broj_plocica<<" plocica."<<std::endl;
        }
    }
	return 0;
}
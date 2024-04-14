//TP 2022/2023: LV 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <deque>

int IzracunajSumu(int broj){
    if(broj==0)return 0;
    else return (broj%10)+IzracunajSumu(broj/10);
}

bool SumaParna(int broj){
    int suma=0;
    suma=IzracunajSumu(abs(broj));
    if(suma%2==0) return true;
    return false;
}
std::deque<int> IzdvojiElemente(std::deque<int>a, bool parni){
    std::deque<int>novi;
    //ako trebaju parni elementi - vrijednost varijable parni ce biti true
    if(parni){
        for(int broj : a)
            if(SumaParna(broj))
                novi.push_front(broj);
    }
    else{
        for(int broj : a)
            if(!SumaParna(broj))
                novi.push_front(broj);
    }
    return novi;
}

int main (){
    std:: deque <int> a;
    int n;
    std:: cout<<"Koliko zelite unijeti elemenata: ";
    std:: cin>>n;
    if(n<=0){
        std::cout<<"Broj elemenata mora biti veci od 0!";
        return 0;
    }
    a.resize(n);
    std:: cout<<"Unesite elemente: ";
    for(int i=0; i<a.size(); i++)
        std::cin>>a[i];

    bool parni=true;
    bool neparni=false;
    std:: deque<int>b=IzdvojiElemente(a,parni);
    std:: deque<int>c=IzdvojiElemente(a,neparni);

    for(int i=0; i<b.size(); i++){
        std::cout<<b[i];
        if(i<b.size()-1) std::cout<<",";
    } 
    std::cout<<std::endl;
    for(int i=0; i<c.size(); i++){
        std::cout<<c[i];
        if(i<c.size()-1) std::cout<<",";
    } 

	return 0;
}
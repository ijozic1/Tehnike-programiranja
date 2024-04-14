//TP 2022/2023: LV 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

//Suma se racuna rekurzijom
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

std::vector<int> IzdvojiElemente(std::vector<int>a, bool parni){
    std::vector<int>novi;
    //ako trebaju parni elementi - vrijednost varijable parni ce biti true
    if(parni){
        for(int broj : a)
            if(SumaParna(broj))
                novi.push_back(broj);
    }
    else{
        for(int broj : a)
            if(!SumaParna(broj))
                novi.push_back(broj);
    }
    return novi;
}

int main (){
    std:: vector <int> a;
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
    std:: vector<int>b=IzdvojiElemente(a,parni);
    std:: vector<int>c=IzdvojiElemente(a,neparni);

    for(int element : b) std::cout<<element<<" ";
    std::cout<<std::endl;
    for(int element : c) std::cout<<element<<" ";

	return 0;
}

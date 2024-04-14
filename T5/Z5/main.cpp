//TP 2022/2023: LV 5, Zadatak 5
#include <iostream>
#include <cmath>
#include <iomanip>

double TrapeznoPravilo(double (*funkcija)(double), double a, double b, int n){
    double integral=0;
    double suma=0;
    for(int k=1; k<n; k++)
        suma+=funkcija(a+(b-a)/n*k);
    integral=((b-a)/n)*(0.5*funkcija(a)+0.5*funkcija(b)+suma);    
    return integral;
}

int main (){
    std::cout<<"Unesite broj podintervala: ";
    int podinterval=0;
    std::cin>>podinterval;
    std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:"<<std::endl;
    double pi=(4*atan(1));
    std::cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo([](double x){return std::sin(x);}, 0, (4*atan(1)), podinterval)<<std::endl;
    std::cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::fixed<<std::setprecision(2)<<TrapeznoPravilo([](double x){return x*x*x;}, 0, 10, podinterval)<<std::endl;
    std::cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo([](double x){return 1./x;}, 1, 2, podinterval)<<std::endl;
	return 0;
}
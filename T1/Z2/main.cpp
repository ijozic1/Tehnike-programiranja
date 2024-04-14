//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
int main ()
{
    double a,b,c;
    std::cout<<"Unesite tri broja: ";
    std::cin>>a>>b>>c;
    if(a+b<=c || b+c<=a || a+c<=b){
        std:: cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!"<<std::endl;
    }
    else{
        double obim=a+b+c;
        double s=obim/2;
        double povrsina=std::sqrt(s*(s-a)*(s-b)*(s-c));
        double min;
        /*Naspram najkrace stranice se nalazi i najmanji ugao*/
        int stepeni, minute, sekunde;
        if(a<=b && a<=c){
            min=((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
        }
        else if(b<=a && b<=c){
            min=((pow(a,2)+pow(c,2)-pow(b,2))/(2*a*c));
        }
        else{
            min=((pow(b,2)+pow(a,2)-pow(c,2))/(2*b*a));
        }
        min=acos(min);
        min=min*180/(4*atan(1));
        stepeni=static_cast<int>(min);
        min=min*60-stepeni*60;
        minute=static_cast<int>(min);
        min=min*60-minute*60;
        sekunde=min;
        
        std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<obim<<"."<<std::endl;
        std::cout<<"Njegova povrsina iznosi "<<povrsina<<"."<<std::endl;
        std::cout<<"Njegov najmanji ugao ima "<<stepeni<<" stepeni, "<<minute<<" minuta i "<<sekunde<<" sekundi."<<std::endl;
    }
	return 0;
}
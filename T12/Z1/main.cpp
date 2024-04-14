//TP 2022/2023: LV 12, Zadatak 1
#include <iostream>
#include <iomanip>
#include <ostream>
#include <stdexcept>

class Sat {
private:
    int sati, minute, sekunde;

public:
    Sat(): sati(), minute(), sekunde(){}
    Sat(int h, int m, int s){PostaviNormalizirano(h,m,s);}
    static bool DaLiJeIspravno(int sati, int minute, int sekunde) {
        return sati >= 0 && sati <= 23 && minute >= 0 && minute <= 59 && sekunde >= 0 && sekunde <= 59;
    }
    
    Sat Postavi(int sati, int minute, int sekunde) {
        if (!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno vrijeme");
        this->sati = sati;
        this->minute = minute;
        this->sekunde = sekunde;
        return *this;
    }
    Sat PostaviNormalizirano(int sati, int minute, int sekunde) {
    while (sekunde < 0) {
        sekunde += 60; minute--;
    }
    while (sekunde > 59) {
        sekunde -= 60; minute++;
    }
    while (minute < 0) {
        minute += 60; sati--;
    }
    while (minute > 59) {
        minute -= 60; sati++;
    }
    while (sati < 0) sati += 24;
    while (sati > 23) sati -= 24;
    Postavi(sati, minute, sekunde);
    return *this;
    }

    int DajSate() const {return sati;}
    int DajMinute() const {return minute;}
    int DajSekunde() const {return sekunde;}

    Sat &operator ++();
    Sat operator ++(int);
    Sat &operator --();
    Sat operator --(int);
    Sat &operator +=(int pomak);
    Sat &operator -=(int pomak);
    Sat operator -() const;
    friend std::ostream &operator <<(std::ostream &tok, const Sat &t);
    friend int operator -(const Sat &s1, const Sat &s2);
    friend Sat operator +(const Sat &s1, int pomak);
    friend Sat operator -(const Sat &s1, int pomak);
};

std::ostream &operator <<(std::ostream &tok, const Sat &t){
    tok << std::setw(2) << std::setfill('0') << t.sati << ":"
        << std::setw(2) << std::setfill('0') << t.minute << ":"
        << std::setw(2) << std::setfill('0') << t.sekunde;
    return tok;
}

int operator -(const Sat &s1, const Sat &s2) {
    int razlika=std::abs((s1.sati-s2.sati)*3600+(s1.minute-s2.minute)*60+s1.sekunde-s2.sekunde);
    return razlika;
}

Sat & Sat::operator ++() {
    sekunde++;
    PostaviNormalizirano(sati, minute, sekunde);
    return *this;
}
Sat Sat:: operator ++(int) {
    Sat pomocni(*this);
    operator++();
    return pomocni;
}

Sat & Sat::operator --() {
    sekunde--;
    PostaviNormalizirano(sati, minute, sekunde);
    return *this;
}

Sat Sat:: operator --(int) {
    Sat pomocni(*this);
    operator--();
    return pomocni;
}

Sat Sat:: operator -() const{
    return Sat(-sati, -minute, -sekunde);
}

Sat & Sat:: operator+=(int pomak) {
    this->sekunde += pomak;
    this->PostaviNormalizirano(this->sati, this->minute, this->sekunde);
    return *this;
}
Sat & Sat:: operator-=(int pomak) {
    this->sekunde -= pomak;
    this->PostaviNormalizirano(this->sati, this->minute, this->sekunde);
    return *this;
}

Sat operator +(const Sat &s1, int pomak){
    Sat pomocni=s1;
    pomocni+=pomak;
    return pomocni;
}

Sat operator -(const Sat &s1, int pomak){
    Sat pomocni=s1;
    pomocni-=pomak;
    return pomocni;
}

int main() {
    Sat s(10, 30, 45);
    std::cout << "Vrijeme s: " << s << std::endl;

    ++s;
    std::cout << "Vrijeme s nakon ++s: " << s << std::endl;

    s--;
    std::cout << "Vrijeme s nakon s--: " << s << std::endl;

    s += 10;
    std::cout << "Vrijeme s nakon s += 10: " << s << std::endl;

    s -= 5;
    std::cout << "Vrijeme s nakon s -= 5: " << s << std::endl;

    Sat t = -s;
    std::cout << "Vrijeme t (kopija -s): " << t << std::endl;

    int u = s - t;
    std::cout << "Vrijeme u (s - t): " << u << std::endl;

    Sat v = s + 15;
    std::cout << "Vrijeme v (s + 15): " << v << std::endl;

    Sat w = s - 7;
    std::cout << "Vrijeme w (s - 7): " << w << std::endl;
    return 0;
}
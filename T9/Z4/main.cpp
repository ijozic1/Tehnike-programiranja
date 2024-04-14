//TP 2022/2023: LV 9, Zadatak 4
#include <iostream>
#include <iomanip>
#include <stdexcept>

class Sat {
private:
    int sati, minute, sekunde;

public:
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

    Sat Sljedeci() {
        this->sekunde++;
        this->PostaviNormalizirano(this->sati, this->minute, this->sekunde);
        return *this;
    }

    Sat Prethodni() {
        this->sekunde--;
        this->PostaviNormalizirano(this->sati, this->minute, this->sekunde);
        return *this;
    }

    Sat PomjeriZa(int pomak) {
        this->sekunde += pomak;
        this->PostaviNormalizirano(this->sati, this->minute, this->sekunde);
        return *this;
    }
    void Ispisi() const;

    int DajSate() const {return sati;}
    int DajMinute() const {return minute;}
    int DajSekunde() const {return sekunde;}

    friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2);
    static int Razmak(const Sat &s1, const Sat &s2) {
        return BrojSekundiIzmedju(s1, s2);
    }
};

void Sat::Ispisi() const {
    std::cout << std::setw(2) << std::setfill('0') << this->sati << ":"
        << std::setw(2) << std::setfill('0') << this->minute << ":"
        << std::setw(2) << std::setfill('0') << this->sekunde;
}

int BrojSekundiIzmedju(const Sat &s1, const Sat &s2) {
    int razlika = (s1.sati - s2.sati) * 3600 + (s1.minute - s2.minute) * 60 + (s1.sekunde - s2.sekunde);
    return razlika;
}

int main() {
    Sat s;
    s.Postavi(10,10,10);
    s.Sljedeci();
    s.Sljedeci().Sljedeci().Ispisi();
    std::cout << std::endl;
    return 0;
}
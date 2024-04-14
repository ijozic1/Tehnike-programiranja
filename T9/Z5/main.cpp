//TP 2022/2023: LV 9, Zadatak 5
#include <iostream>
#include <iomanip>
#include <cmath>

class Sat {
private:
    int ukupnoSekundi;
public:
    static bool DaLiJeIspravno(int sati, int minute, int sekunde) {
        return sati >= 0 && sati <= 23 && minute >= 0 && minute <= 59 && sekunde >= 0 && sekunde <= 59;
    }
    Sat(int h = 0, int m = 0, int s = 0) {
        Postavi(h, m, s);
    }

    Sat Postavi(int h, int m, int s) {
        if (!DaLiJeIspravno(h, m, s)) throw std::domain_error("Neispravno vrijeme");
        ukupnoSekundi = h * 3600 + m * 60 + s;
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
        ukupnoSekundi = (ukupnoSekundi + 1) % (24 * 3600);
        return *this;
    }

    Sat Prethodni() {
        ukupnoSekundi = (ukupnoSekundi + 24 * 3600 - 1) % (24 * 3600);
        return *this;
    }

    Sat PomjeriZa(int pomak) {
        ukupnoSekundi = (ukupnoSekundi + pomak + 24 * 3600) % (24 * 3600);
        return *this;
    }

    int DajSate() const {
        return ukupnoSekundi / 3600;
    }

    int DajMinute() const {
        return (ukupnoSekundi / 60) % 60;
    }

    int DajSekunde() const {
        return ukupnoSekundi % 60;
    }

    void Ispisi() const {
        std::cout << std::setfill('0') << std::setw(2) << DajSate() << ":"
             << std::setfill('0') << std::setw(2) << DajMinute() << ":"
             << std::setfill('0') << std::setw(2) << DajSekunde();
    }

    friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2);
    static int Razmak(const Sat &s1, const Sat &s2);
};

int BrojSekundiIzmedju(const Sat &s1, const Sat &s2) {
    return (s1.ukupnoSekundi - s2.ukupnoSekundi);
}

int Sat::Razmak(const Sat &s1, const Sat &s2) {
    return BrojSekundiIzmedju(s1, s2);
}

int main() {
    Sat s;
    try{
        s.Postavi(23, 59, 55);
        s.Ispisi();
        std::cout << std::endl;
        s.Sljedeci();
        s.Ispisi();
        std::cout << std::endl;
        s.Postavi(1, 10, 5);
        Sat t(2, 20, 15);
        std::cout << BrojSekundiIzmedju(s, t) << std::endl;
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    return 0;
}
//TP 2022/2023: LV 12, Zadatak 3
#include <iostream>

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

std::ostream& operator<<(std::ostream& tok, Dani dan) {
    switch (dan) {
        case Ponedjeljak:
            tok << "Ponedjeljak";
            break;
        case Utorak:
            tok << "Utorak";
            break;
        case Srijeda:
            tok << "Srijeda";
            break;
        case Cetvrtak:
            tok << "Cetvrtak";
            break;
        case Petak:
            tok << "Petak";
            break;
        case Subota:
            tok << "Subota";
            break;
        case Nedjelja:
            tok << "Nedjelja";
            break;
    }
    return tok;
}

Dani& operator++(Dani& dan) {
    dan = Dani((int(dan) + 1) % 7);
    return dan;
}

Dani operator++(Dani& dan, int) {
    Dani pomocni = dan;
    ++dan;
    return pomocni;
}

int main() {
    for (Dani d = Ponedjeljak; d <= Petak; d++) {
        std::cout << d << std::endl;
    }

    for (Dani d = Ponedjeljak; d <= Nedjelja; d++) {
        std::cout << d << std::endl;
    }

    return 0;
}

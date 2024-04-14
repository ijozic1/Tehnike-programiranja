// TP 2022/2023: Zadaća 1, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matrica;

int BrojCifara(int broj) {
    if (broj == 0) return 0;
    return 1 + BrojCifara(broj / 10);
}

int SirinaIspisa(Matrica &m) {
    int max_sirina = 0;
    if (m.size() == 0 || m.at(0).size() == 0) return 0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.at(i).size(); j++) {
            int predznak = 0;
            if (m.at(i).at(j) < 0) predznak = 1;
            int sirina = BrojCifara(abs(m.at(i).at(j))) + predznak;
            if (sirina > max_sirina) max_sirina = sirina;
        }
    }
    return max_sirina + 1;
}

void IspisiMatricu(Matrica &mat, int sirinaIspisa, bool orjentacija) {
    std::cout << std::endl;
    std::cout << "Kreirana spiralna matrica: " << std::endl;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat.at(i).size(); j++)
            std::cout << std::setw(sirinaIspisa) << mat.at(i).at(j);
        std::cout << std::endl;
    }
}

void IdiDesno(Matrica &m, int pomocni, int &broj, int &red, int &kolona, int &brojac) {
    while (kolona < m.at(red).size() - pomocni && m.at(red).at(kolona) == 0) {
        m.at(red).at(kolona) = broj++;
        kolona++;
        brojac++;
    }
}
void IdiLijevo(Matrica &m, int pomocni, int &broj, int &red, int &kolona, int &brojac) {
    while (kolona >= pomocni && m.at(red).at(kolona) == 0) {
        m.at(red).at(kolona) = broj++;
        kolona--;
        brojac++;
    }
}
void IdiGore(Matrica &m, int pomocni, int &broj, int &red, int &kolona, int &brojac) {
    while (red >= pomocni && m.at(red).at(kolona) == 0) {
        m.at(red).at(kolona) = broj++;
        red--;
        brojac++;
    }
}
void IdiDole(Matrica &m, int pomocni, int &broj, int &red, int &kolona, int &brojac) {
    while (red < m.size() - pomocni && m.at(red).at(kolona) == 0) {
        m.at(red).at(kolona) = broj++;
        red++;
        brojac++;
    }
}

Matrica KreirajSpiralnuMatricu(int brRedova, int brKolona, int k, bool spiralna) {
    if (brRedova <= 0 || brKolona <= 0) {
        Matrica matrica;
        return matrica;
    }
    Matrica mat(brRedova, std::vector<int>(brKolona, 0));
    int red = 0, kolona = 0, broj = k, i = 0;
    int brojac=0;
    if (spiralna) {
        while (broj <= k + brRedova * brKolona - 1 && brojac<brRedova*brKolona) {
            IdiDesno(mat, i, broj, red, kolona, brojac);
            kolona--; red++;
            IdiDole(mat, i, broj, red, kolona, brojac);
            red--; kolona--;
            IdiLijevo(mat, i, broj, red, kolona, brojac);
            kolona++; red--;
            IdiGore(mat, i, broj, red, kolona, brojac);
            red++;  kolona++;
            i++;
        }
    } 
    else {
        while (broj <= k + brRedova * brKolona - 1 && brojac<brRedova*brKolona) {
            IdiDole(mat, i, broj, red, kolona, brojac);
            red--; kolona++;
            IdiDesno(mat, i, broj, red, kolona, brojac);
            kolona--; red--;
            IdiGore(mat, i, broj, red, kolona, brojac);
            red++; kolona--;
            IdiLijevo(mat, i, broj, red, kolona, brojac);
            kolona++; red++;
            i++;
        }
    }
    return mat;
}

bool DaLiJeSpiralnaMatrica(Matrica &mat) {
    if (mat.size() == 0 || mat.at(0).size() == 0) return false;
    for (int i = 0; i < mat.size(); i++)
        if (i > 0 && mat.at(i).size() != mat.at(i - 1).size()) return false;
    bool dSpiralna = true;
    Matrica ispravna = KreirajSpiralnuMatricu(mat.size(), mat.at(0).size(), mat.at(0).at(0), true);
    for (int i = 0; i < ispravna.size(); i++) {
        for (int j = 0; j < ispravna.at(i).size(); j++)
            if (ispravna.at(i).at(j) != mat.at(i).at(j)) {
                dSpiralna = false; break;
            }
        if (!dSpiralna) break;
    }
    if (dSpiralna) return true;
    ispravna = KreirajSpiralnuMatricu(mat.size(), mat.at(0).size(),mat.at(0).at(0), false);
    for (int i = 0; i < ispravna.size(); i++) {
        for (int j = 0; j < ispravna.at(i).size(); j++)
            if (ispravna.at(i).at(j) != mat.at(i).at(j)) return false;
    }
    return true;
}

int main() {
    int redovi, kolone;
    std::cout << "Unesite broj redova i kolona matrice: ";
    std::cin >> redovi >> kolone;
    int pocetna;
    std::cout << "Unesite pocetnu vrijednost: ";
    std::cin >> pocetna;
    char znak;
    std::cout << "Unesite L za lijevu, a D za desnu spiralnu matricu: ";
    std::cin >> znak;
    bool smijerSpiralne = true;
    if (znak == 'L') smijerSpiralne = false;

    auto Spiralna = KreirajSpiralnuMatricu(redovi, kolone, pocetna, smijerSpiralne);
    IspisiMatricu(Spiralna, SirinaIspisa(Spiralna), smijerSpiralne);
    return 0;
}
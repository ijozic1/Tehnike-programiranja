//TP 2022/2023: LV 13, Zadatak 1
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <limits>

const double PI = 4*std::atan(1);

class Lik {
public:
    virtual void IspisiSpecificnosti() const = 0;
    virtual double DajObim() const = 0;
    virtual double DajPovrsinu() const = 0;
    void Ispisi() const {
        IspisiSpecificnosti();
        std::cout << "Obim: " << DajObim();
        std::cout << " Povrsina: " << DajPovrsinu() << std::endl;
    }
    virtual ~Lik() = default;
};

class Krug : public Lik {
private:
    double poluprecnik;
public:
    explicit Krug(double r) {
        if (r <= 0)
            throw std::domain_error("Neispravni parametri");
        poluprecnik = r;
    }

    void IspisiSpecificnosti() const override {
        std::cout << "Krug poluprecnika " << poluprecnik << std::endl;
    }

    double DajObim() const override {
        return 2 * PI * poluprecnik;
    }

    double DajPovrsinu() const override {
        return PI * poluprecnik * poluprecnik;
    }
};

class Pravougaonik : public Lik {
private:
    double a, b;
public:
    Pravougaonik(double pa, double pb) {
        if (pa <= 0 || pb <= 0)
            throw std::domain_error("Neispravni parametri");
        a = pa;
        b = pb;
    }

    void IspisiSpecificnosti() const override {
        std::cout << "Pravougaonik sa stranicama duzine " << a << " i " << b << std::endl;
    }

    double DajObim() const override {
        return 2 * (a + b);
    }

    double DajPovrsinu() const override {
        return a * b;
    }
};

class Trougao : public Lik {
private:
    double a, b, c;
public:
    Trougao(double ta, double tb, double tc) {
        if (ta <= 0 || tb <= 0 || tc <= 0 || std::fabs(ta+tb-tc)<0.00001 || ta + tb < tc || ta + tc < tb || 
            std::fabs(ta+tc-tb)<0.00001|| tb + tc < ta || std::fabs(tc+tb-ta)<0.00001)
            throw std::domain_error("Neispravni parametri");
        a = ta;
        b = tb;
        c = tc;
    }

    void IspisiSpecificnosti() const override {
        std::cout << "Trougao sa stranicama duzine " << a << ", " << b << " i " << c << std::endl;
    }

    double DajObim() const override {
        return a + b + c;
    }

    double DajPovrsinu() const override {
        double s = DajObim() / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

int main() {
    int br;
    std::cout << "Koliko zelite likova: ";
    std::cin >> br;
    std::cin.ignore();
    std::vector<std::unique_ptr<Lik>> lik;

    for (int i = 0; i < br; i++) {
        std::string unos;
        std::cout << "Lik " << i + 1 << ": ";
        std::getline(std::cin, unos);

        char c = unos[0];

        try {
            switch (c) {
                case 'K': {
                    double r = std::stod(unos.substr(1));
                    int preostalo = unos.substr(1).find_first_not_of("0123456789.-");
                    if (preostalo != std::string::npos) throw std::domain_error("Pogresni podaci, ponovite unos!");
                    lik.emplace_back(std::make_unique<Krug>(r));
                    break;
                }

                case 'P': {
                    int zarez = unos.find(',');
                    double a = std::stod(unos.substr(1, zarez - 1));
                    double b = std::stod(unos.substr(zarez + 1));
                    int preostalo = unos.substr(1).find_first_not_of("0123456789.,");
                    if (preostalo != std::string::npos) throw std::domain_error("Pogresni podaci, ponovite unos!");
                    lik.emplace_back(std::make_unique<Pravougaonik>(a, b));
                    break;
                }

                case 'T': {
                    int zarez1 = unos.find(',');
                    int zarez2 = unos.find(',', zarez1 + 1);
                    double a = std::stod(unos.substr(1, zarez1 - 1));
                    double b = std::stod(unos.substr(zarez1 + 1, zarez2 - zarez1 - 1));
                    double c = std::stod(unos.substr(zarez2 + 1));
                    int preostalo = unos.substr(1).find_first_not_of("0123456789.,");
                    if (preostalo != std::string::npos) throw std::domain_error("Pogresni podaci, ponovite unos!");
                    lik.emplace_back(std::make_unique<Trougao>(a, b, c));
                    break;
                }

                default: {
                    std::cout << "Pogresni podaci, ponovite unos!\n";
                    i--;
                    break;
                }
            }
        }
        catch (const std::domain_error& e) {
            std::cout << "Pogresni podaci, ponovite unos!\n";
            i--;
        }
    }

    std::cout << std::endl;
    for (const auto& l : lik) l->Ispisi();
    return 0;
}
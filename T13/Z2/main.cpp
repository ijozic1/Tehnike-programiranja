//TP 2022/2023: LV 13, Zadatak 2
#include <iostream>
#include <stdexcept>
#include <string>

class ApstraktniStudent {
private:
    std::string ime;
    std::string prezime;
    int brojIndeksa;
    int brojPolozenih;
    double prosjek;

public:
    ApstraktniStudent(const std::string& ime, const std::string& prezime, int brojIndeksa)
        : ime(ime), prezime(prezime), brojIndeksa(brojIndeksa), brojPolozenih(0), prosjek(5.0) {}

    virtual ~ApstraktniStudent() {}

    std::string DajIme() const { return ime; }
    std::string DajPrezime() const { return prezime; }
    int DajBrojIndeksa() const { return brojIndeksa; }
    int DajBrojPolozenih() const { return brojPolozenih; }
    double DajProsjek() const { return prosjek; }

    virtual void IspisiPodatke() const = 0;
    virtual ApstraktniStudent* DajKopiju() const = 0;

    void RegistrirajIspit(int ocjena) {
        if (ocjena < 5 || ocjena > 10) {
            throw std::domain_error("Neispravna ocjena");
        }

        if (ocjena == 5) {
            return;
        }

        brojPolozenih++;
        prosjek = (prosjek * (brojPolozenih - 1) + ocjena) / brojPolozenih;
    }

    void PonistiOcjene() {
        brojPolozenih = 0;
        prosjek = 5.0;
    }
};

class StudentBachelor : public ApstraktniStudent {
public:
    StudentBachelor(const std::string& ime, const std::string& prezime, int brojIndeksa)
        : ApstraktniStudent(ime, prezime, brojIndeksa) {}

    void IspisiPodatke() const override {
        std::cout << "Student bachelor studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << ",\nima prosjek " << DajProsjek() << "." << std::endl;
    }

    StudentBachelor* DajKopiju() const override {
        return new StudentBachelor(*this);
    }
};

class StudentMaster : public ApstraktniStudent {
    int godinaZavrsetkaBachelor;

public:
    StudentMaster(const std::string& ime, const std::string& prezime, int brojIndeksa, int godinaZavrsetkaBachelor)
        : ApstraktniStudent(ime, prezime, brojIndeksa), godinaZavrsetkaBachelor(godinaZavrsetkaBachelor) {}

    void IspisiPodatke() const override {
        std::cout << "Student master studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << ",\nzavrsio bachelor studij godine " << godinaZavrsetkaBachelor << ",ima prosjek " << DajProsjek() << "." << std::endl;
    }

    StudentMaster* DajKopiju() const override {
        return new StudentMaster(*this);
    }
};

int main() {
    StudentBachelor studentbsc("Paja", "Patak", 123);
    studentbsc.RegistrirajIspit(9);
    studentbsc.IspisiPodatke();

    StudentMaster studentms("Miki", "Maus", 456, 2022);
    studentms.RegistrirajIspit(10);
    studentms.IspisiPodatke();

    ApstraktniStudent *KopijaBsc=studentbsc.DajKopiju();
    KopijaBsc->IspisiPodatke();

    delete KopijaBsc;

    return 0;
}
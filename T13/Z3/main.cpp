//TP 2022/2023: LV 13, Zadatak 3
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <vector>

class ApstraktniStudent{
   private:
    std::string ime;
    std::string prezime;
    int brojIndeksa;
    int brojPolozenih;
    double prosjek;
  public:
    virtual ~ApstraktniStudent(){}
    ApstraktniStudent(const std::string& ime, const std::string& prezime, int brojIndeksa) : ime(ime), prezime(prezime), brojIndeksa(brojIndeksa), brojPolozenih(0), prosjek(5.0) {}
    std::string DajIme() const { return ime; }
    std::string DajPrezime() const { return prezime; }
    int DajBrojIndeksa() const { return brojIndeksa; }
    int DajBrojPolozenih() const { return brojPolozenih; }
    double DajProsjek() const { return prosjek; }

    virtual void IspisiPodatke() const = 0;
    virtual ApstraktniStudent* DajKopiju() const = 0;

    void RegistrirajIspit(int ocjena) {
        if (ocjena < 5 || ocjena > 10) throw std::domain_error("Neispravna ocjena");
        if (ocjena == 5) return;
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
    StudentBachelor(const std::string& ime, const std::string& prezime, int brojIndeksa) : ApstraktniStudent(ime, prezime, brojIndeksa) {}
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
    StudentMaster(const std::string& ime, const std::string& prezime, int brojIndeksa, int godinaZavrsetkaBachelor) : ApstraktniStudent(ime, prezime, brojIndeksa), godinaZavrsetkaBachelor(godinaZavrsetkaBachelor) {}
    void IspisiPodatke() const override {
        std::cout << "Student master studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << ",\nzavrsio bachelor studij godine " << godinaZavrsetkaBachelor << ",ima prosjek " << DajProsjek() << "." << std::endl;
    }
    StudentMaster* DajKopiju() const override {
        return new StudentMaster(*this);
    }
};

class Fakultet {
private:
    std::vector<ApstraktniStudent*> studenti;
public:
    Fakultet() {}
    Fakultet(const Fakultet& other) {
        for (const auto& student : other.studenti) studenti.emplace_back(student->DajKopiju());
    }
    Fakultet(Fakultet&& other) noexcept {
        studenti = std::move(other.studenti);
        other.studenti.clear();
    }
    Fakultet& operator=(const Fakultet& other) {
        if (this != &other) {
            for (const auto& student : studenti) delete student;
            studenti.clear();

            for (const auto& student : other.studenti) studenti.emplace_back(student->DajKopiju());
        }
        return *this;
    }

    Fakultet& operator=(Fakultet&& other) noexcept {
        if (this != &other) {
            for (const auto& student : studenti) delete student;
            studenti.clear();

            studenti = std::move(other.studenti);
            other.studenti.clear();
        }
        return *this;
    }

    ~Fakultet() {
        for (const auto& student : studenti) delete student;
        studenti.clear();
    }

    void UpisiStudenta(const std::string& ime, const std::string& prezime, int brojIndeksa) {
        for (const auto& student : studenti) {
            if (student->DajBrojIndeksa() == brojIndeksa) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
        }
        studenti.emplace_back(new StudentBachelor(ime, prezime, brojIndeksa));
    }

    void UpisiStudenta(const std::string& ime, const std::string& prezime, int brojIndeksa,  int godinaZavrsetkaBachelor) {
        for (const auto& student : studenti) {
            if (student->DajBrojIndeksa() == brojIndeksa) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
        }
        studenti.emplace_back(new StudentMaster(ime, prezime, brojIndeksa, godinaZavrsetkaBachelor));
    }

    void ObrisiStudenta(int brojIndeksa) {
        auto it = std::find_if(studenti.begin(), studenti.end(), [brojIndeksa](const ApstraktniStudent* student) {
            return student->DajBrojIndeksa() == brojIndeksa;
        });

        if (it != studenti.end()) {
            delete *it;
            studenti.erase(it);
        } 
        else throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    }

    ApstraktniStudent& operator[](int brojIndeksa) {
        auto it = std::find_if(studenti.begin(), studenti.end(), [brojIndeksa](const ApstraktniStudent* student) {
            return student->DajBrojIndeksa() == brojIndeksa;
        });

        if (it != studenti.end()) return **it;
        else throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    }

    const ApstraktniStudent& operator[](int brojIndeksa) const {
        auto it = std::find_if(studenti.begin(), studenti.end(), [brojIndeksa](const ApstraktniStudent* student) {
            return student->DajBrojIndeksa() == brojIndeksa;
        });

        if (it != studenti.end()) return **it;
        else throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    }

    void IspisiSveStudente() const {
        std::vector<const ApstraktniStudent*> sortiraniStudenti(studenti.size());
        std::transform(studenti.begin(), studenti.end(), sortiraniStudenti.begin(), [](const ApstraktniStudent* student) {
            return student;
        });

        std::sort(sortiraniStudenti.begin(), sortiraniStudenti.end(), [](const ApstraktniStudent* s1, const ApstraktniStudent* s2) {
            if (s1->DajProsjek() == s2->DajProsjek()) return s1->DajBrojIndeksa() < s2->DajBrojIndeksa();
            return s1->DajProsjek() > s2->DajProsjek();
        });

        for (const auto& student : sortiraniStudenti) student->IspisiPodatke();
    }
};

int main() {
    Fakultet fakultet;
    fakultet.UpisiStudenta("Pera", "Peric", 123);
    fakultet.UpisiStudenta("Mika", "Mikic", 456, 2020);
    fakultet.UpisiStudenta("Zika", "Zikic", 789);
    fakultet.ObrisiStudenta(456);
    fakultet[123].RegistrirajIspit(8);
    fakultet[123].IspisiPodatke();
    fakultet.IspisiSveStudente();

    return 0;
}
//TP 2022/2023: LV 13, Zadatak 4
#include <iostream>
#include <string>
#include <utility>

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

class Student {
    ApstraktniStudent* student;
public:
    Student() : student(nullptr) {}
    Student(StudentBachelor& sb) : student(new StudentBachelor(sb)) {}
    Student(StudentMaster& sm) : student(new StudentMaster(sm)) {}
    Student(ApstraktniStudent* s) : student(s) {}
    Student(const Student& stud) : student(nullptr) {
        if (stud.student != nullptr) {
            // Provjeri kojem podrazumijevanom podtipu pripada objekt other.student
            StudentBachelor* bachelorStudent = dynamic_cast<StudentBachelor*>(stud.student);
            if (bachelorStudent != nullptr) student = new StudentBachelor(*bachelorStudent);
            else {
                StudentMaster* masterStudent = dynamic_cast<StudentMaster*>(stud.student);
                if (masterStudent != nullptr) student = new StudentMaster(*masterStudent);
            }
        }
    }

    Student& operator=(const Student& stud) {
        if (this == &stud) return *this;
        delete student;
        student = nullptr;
        if (stud.student != nullptr) {
            if (dynamic_cast<StudentBachelor*>(stud.student) != nullptr) {
                student = new StudentBachelor(*dynamic_cast<StudentBachelor*>(stud.student));
                student->RegistrirajIspit(5);
            } 
            else if (dynamic_cast<StudentMaster*>(stud.student) != nullptr) {
                student = new StudentMaster(*dynamic_cast<StudentMaster*>(stud.student));
                student->RegistrirajIspit(5);
            }
        }
        return *this;
    }

    ~Student() {delete student;}

    void RegistrirajIspit(int ocjena) {
        if (student != nullptr) student->RegistrirajIspit(ocjena);
    }

    void IspisiPodatke() const {
        if (student != nullptr) student->IspisiPodatke();
    }

    void PostaviStudenta(ApstraktniStudent* s) {
        student = s;
    }

    void PonistiOcjene() {
        if (student != nullptr) student->PonistiOcjene();
    }
    std::string DajIme()const{return student->DajIme();}
    std::string DajPrezime()const{return student->DajPrezime();}
    int DajBrojIndeksa() const {return student->DajBrojIndeksa();}
    int DajBrojPolozenih() const{return student->DajBrojPolozenih();}
    double DajProsjek() const{return student->DajProsjek();}
};

int main() {
    StudentBachelor sb("Paja", "Patak", 12345);
    StudentMaster sm("Miki", "Maus", 54321, 2018);

    Student s1, s2;
    s1.PostaviStudenta(&sb);
    s2.PostaviStudenta(&sm);

    s1.IspisiPodatke();
    s2.IspisiPodatke();

    return 0;
}
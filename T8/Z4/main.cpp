//TP 2022/2023: LV 8, Zadatak 4
#include <iostream>
#include <cmath>
#include <map>
#include <string>


std::string ZamijeniPremaRjecniku(std::string stringZaZamjenu, std::map<std::string, std::string> rijecnik) {
    std::string noviString, rijec;
    int i = 0;
    while (i < stringZaZamjenu.length()) {
        if (isalnum(stringZaZamjenu[i])) rijec += stringZaZamjenu[i];
        else {
            if (rijecnik.count(rijec)) noviString += rijecnik[rijec];
            else noviString += rijec;
            noviString += stringZaZamjenu[i];
            rijec.resize(0);
        }
        i++;
    }
    if (rijecnik.count(rijec)) noviString += rijecnik[rijec];
    else noviString += rijec;
    return noviString;
}

int main (){
    std::map<std::string, std::string> moj_rjecnik{{"jabuka", "apple"}, {"da", "yes"}, {"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};
    std::cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik);
	return 0;
}

//TP 2022/2023: LV 7, Zadatak 9
#include <iostream>
#include <cmath>
#include <functional>

std::function<double(double)> plus2(double element){
    return [element](double x){return element + x;};
}

template<typename Tip>
auto plus3(Tip x) {
    return [x](Tip y) {return [x, y](Tip z) { return x + y + z;};};
}
//std::function<std::function<double(double)>(double)>plus3(Tipx){}

int main (){
    std::cout << plus2(3)(5) << std::endl;
  	std::cout << plus3(3)(5)(6) << std::endl;
	return 0;
}

#include "product.h"
#include <iomanip>

Product::Product(std::string name, double price) : _name{name}, _price{price} {}
Product::Product(std::istream& ist) {
    std::getline(ist, _name);
    ist >> _price;
    ist.ignore();

}

std::string Product::name() const {return _name;}
double Product::price() const {return _price;}

void Product::save(std::ofstream& ofs) {
    ofs << _name << "\n";
    ofs << _price << "\n";

}

std::ostream& operator<<(std::ostream& ost, const Product& product) {
    ost << product._name << " ($" << std::fixed << std::setprecision(2) << product._price << ')';
    return ost;
}

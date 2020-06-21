#ifndef __PRODUCT_H
#define __PRODUCT_H

#include <fstream>

class Product {
  public:
    Product(std::string name, double price);
    std::string name() const;
    double price() const;
    friend std::ostream& operator<<(std::ostream& ost, const Product& product);
  private:
    std::string _name;
    double _price;
};
#endif

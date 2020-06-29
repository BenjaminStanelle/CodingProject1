#include "order.h"

Order::Order(std::string email) : _email{email} { }
Order::Order(std::istream& ist) {
    std::getline(ist, _email);
    int i = 0;
    int products;
    ist >> products; 
    ist.ignore();
    while (i < products) {
        _products.push_back(Product_order{ ist });
        i++;
    }

}
std::string Order::email() const {return _email;}
double Order::cost() {
    double sum;
    for (auto& po : _products) sum += po.cost();
    return sum;
}
void Order::add_product_order(Product_order po) {
    _products.push_back(po);
}
int Order::num_product_orders() {return _products.size();}
Product_order Order::product_order(int index) {
    if (0 > index || index > (_products.size()-1)) 
        throw std::out_of_range{"Order: Product index " + std::to_string(index) 
            + " with only " + std::to_string(_products.size()-1) + " products"};
    return _products[index];
}

void Order::save(std::ofstream& ofs) {
    ofs << _email << "\n";
    ofs << _products.size() << "\n";
    for (auto& p : _products) {
        p.save(ofs);
    }
}
std::ostream& operator<<(std::ostream& ost, const Order& order) {
    ost << "  Email: " << order.email() << "\n";
    for (auto& po : order._products) ost << "  " << po << '\n';
    return ost;
}


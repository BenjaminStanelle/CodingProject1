#include "order.h"

Order::Order(std::string email) : _email{email} { }
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
std::ostream& operator<<(std::ostream& ost, const Order& order) {
    ost << "  Email: " << order.email() << "\n";
    for (auto& po : order._products) ost << "  " << po << '\n';
    return ost;
}


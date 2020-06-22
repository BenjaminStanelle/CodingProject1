#include "store.h"

Store::Store(std::string name) : _name{name} { }
Store::Store(std::istream& ist) {
    int products_num;
    int i = 0;
    std::getline(ist, _name);
    ist >> products_num; 
    ist.ignore();
    while (i < products_num) {
        _products.push_back(Product{ ist });
        i++;
    }

    int orders_num;
    ist >> orders_num;
    ist.ignore();

    i = 0;
    while (i < orders_num) {
        _orders.push_back(Order{ist});
        i++;
    }
  


}
std::string Store::name() const {return _name;}

// Product Management
void Store::add_product(Product product) {_products.push_back(product);}
int Store::num_products() const {return _products.size();}
Product Store::product(int index) const {
    if (0 > index || index > (_products.size()-1)) 
        throw std::out_of_range{"Store " + _name + ": Product index " + std::to_string(index) 
            + " with only " + std::to_string(_products.size()-1) + " products"};
    return _products[index];
}

// Order Management
int Store::create_order(std::string email) {
    _orders.push_back(Order{email});
    return _orders.size()-1;
}
void Store::add_to_order(int order_num, Product_order po) {
    if (0 > order_num || order_num > (_orders.size()-1)) 
        throw std::out_of_range{"Store " + _name + ": Tried to add to Order " + std::to_string(order_num) 
            + " with only " + std::to_string(_orders.size()-1) + " orders"};
    _orders[order_num].add_product_order(po);
}
int Store::num_orders() const {return _orders.size();}
Order Store::order(int order_num) const {
    if (0 > order_num || order_num > (_orders.size()-1)) 
        throw std::out_of_range{"Store " + _name + ": Tried to access Order " + std::to_string(order_num) 
            + " with only " + std::to_string(_orders.size()-1) + " orders"};
    return _orders[order_num];
}
std::ostream& operator<<(std::ostream& ost, const Store& store) {
    for (int i=0; i<store.num_products(); ++i) ost << i << ") " << store.product(i) << std::endl;
    return ost;
}

void Store::save(std::ofstream& ofs) {
    ofs << _name << "\n";
    ofs << _products.size()<<"\n";
    for (auto& p : _products) {
        p.save(ofs);
    }
    ofs << _orders.size();
    for (auto& o : _orders) {
        o.save(ofs);
    }


}

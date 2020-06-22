#include "controller.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

Controller::Controller() : Controller(Store{"Mavmart"}) { }
Controller::Controller(Store store) : _store{store}, _view{View{_store}} { }

double Controller::get_double(std::string prompt) {
    while(true) {
        try {
            std::cout << prompt << "? ";
            std::string s;
            std::getline(std::cin, s);
            if(s == "") break;
            std::istringstream iss{s};
            double d;
            iss >> d;
            return d;
        } catch(std::runtime_error e) {
            std::cerr << "#### Error: Invalid input: " << e.what() << std::endl;
        }
    }
    throw std::runtime_error{prompt + " was not entered"};
}
int Controller::get_int(std::string prompt) {
    while(true) {
        try {
            std::cout << prompt << "? ";
            std::string s;
            std::getline(std::cin, s);
            if(s == "") break;
            std::istringstream iss{s};
            int d;
            iss >> d;
            return d;
        } catch(std::runtime_error e) {
            std::cerr << "#### Error: Invalid input: " << e.what() << std::endl;
        }
    }
    throw std::runtime_error{prompt + " was not entered"};
}
void Controller::cli() {
    while(true) {
        try {
            std::cout << _view.main_menu();
            int cmd = get_int("Command");
            if (cmd == 0) break;
            execute_cmd(cmd);
        } catch (std::runtime_error e) {
            std::cerr << "#### Error: Invalid input" << std::endl;
        }
    }
}

void Controller::execute_cmd(int cmd) {
    switch(cmd) {
        case 1: add_product(); break;
        case 2: list_all_products(); break;
        case 4: add_order(); break;
        case 5: list_all_orders(); break;
        case 6: load_file(); break;
        case 7: save_file(); break;
        case 9: help(); break;
        case 42: easter_egg(); break;
        default: std::cerr << "#### Invalid command" << std::endl;
    }
}

void Controller::add_product() {
    try {
        std::string name;
        std::cout << "Product name? ";
        std::getline(std::cin, name);
        if (name.empty()) throw std::runtime_error{"Empty product name"};
        double price = get_double("Price");
        _store.add_product(Product{name, price});
    } catch(std::runtime_error e) {
        std::cerr << "#### Add Product aborted: " << e.what() << std::endl;
    }
}

void Controller::list_all_products() {
    std::cout << "\nAvailable Products\n==================\n";
    std::cout << _store; //since store has a overloaded operator, and a friend of this class, just used its overloaded operator<<;
}

void Controller::add_order() {
    try {
        std::string email;
        std::cout << "Customer email address? ";
        std::getline(std::cin, email);
        if (email.empty()) throw std::runtime_error{"Empty email address"};
        int order_num = _store.create_order(email);

        while(true) {
            std::cout << "\n\nCurrent Products in Order " << order_num << "\n=============================\n" 
                      << _store.order(order_num) << std::endl << std::endl;
            list_all_products();
            int product_num = get_int("Product number to add (-1 when done)");
            if (0 <= product_num && product_num < _store.num_products()) {
                int product_quantity = get_int("Quantity");
                if (0 <= product_quantity)
                    _store.add_to_order(order_num, Product_order{_store.product(product_num), product_quantity});
                else
                    std::cerr << "#### Invalid quantity: " << product_quantity << std::endl;
            } else if (product_num == -1) {
                break;
            } else {
                std::cerr << "#### No such product number: " << product_num << std::endl;
            }
        }
    } catch (std::runtime_error e) {
        std::cerr << "#### Place Order aborted: " << e.what() << std::endl;
    }
}
void Controller::list_all_orders() {
    for(int i=0; i<_store.num_orders(); ++i)
        std::cout << i << ") " << _store.order(i) << std::endl;
}
void Controller::easter_egg() {
        _store.add_product(Product {"Hamburger", 4.00});
        _store.add_product(Product {"Hot Dog", 2.00});
        _store.add_product(Product {"Sandwich", 3.50});
        _store.add_product(Product {"Fries", 0.75});
        _store.add_product(Product {"Chips", 1.50});
        _store.add_product(Product {"Pickle", 0.25});
        _store.add_product(Product {"Coke", 1.25});
        _store.add_product(Product {"Diet Coke", 1.25});
        _store.add_product(Product {"Dr Pepper", 1.25});
}

void Controller::load_file() {
    std::string f_name;
    std::cout << "Enter the Name of the file: ";
    std::getline(std::cin, f_name);
    std::ifstream ifs{f_name};
    if (ifs) {
        _store = Store{ ifs };

        std::cout << "\nFile " << f_name << " loaded successfully.";
    }
    else  std::cerr << "\nNo such file exists. Try again.";

    }



void Controller::save_file() {
    std::string f_name;
    std::cout << "Enter new file to be saved to: ";
    std::getline(std::cin, f_name);
    std::ofstream ofs{ f_name };
    if (ofs) {
        _store.save(ofs);

        std::cout << "File saved as " << f_name << std::endl;
    }
    else std::cerr << "File failed to save.";

}


void Controller::help() {
    std::cout << _view.help() << std::endl;
}


#include "controller.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <experimental/filesystem>
#include "dialogs.h"

Controller::Controller() : Controller(nullptr) { }
Controller::Controller(Gtk::Window* window) : Controller(window, Store{ "Mavmart" }) { }
Controller::Controller(Gtk::Window* window, Store store) : _store{ store }, _view{ View{_store} }, _window{ window }, _filename{ "untitled.dat" } { }

std::string Controller::get_string(std::string prompt, std::string title) {
    while (true) {
        try {
            std::string s = Dialogs::input(prompt, title);
            return s;
        }
        catch (std::runtime_error e) {
            Dialogs::message("#### Error: Invalid input: " + std::string{e.what()});
        }
    }
    throw std::runtime_error(prompt + "was not entered");
}

double Controller::get_double(std::string prompt, std::string title) {
    while(true) {
        try {
            std::string s = Dialogs::input(prompt,title);
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
int Controller::get_int(std::string prompt, std::string title) {
    while(true) {
        try {
            std::string s = Dialogs::input(prompt, title);
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
            int cmd = get_int("Command","title");
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
        double price;


        Gtk::Dialog* dialog = new Gtk::Dialog();
        dialog->set_title("Add Product");

        // Name
        Gtk::HBox b_name;

        Gtk::Label l_name{"Name"};
        l_name.set_width_chars(15);
        b_name.pack_start(l_name, Gtk::PACK_SHRINK);

        Gtk::Entry entry1;
        entry1.set_max_length(50);
        b_name.pack_start(entry1, Gtk::PACK_SHRINK);
        dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

        // Price
        Gtk::HBox b_price;

        Gtk::Label l_price{"Price"};
        l_price.set_width_chars(15);
        b_price.pack_start(l_price, Gtk::PACK_SHRINK);

        Gtk::Entry entry2;
        entry2.set_max_length(50);
        b_price.pack_start(entry2, Gtk::PACK_SHRINK);
        dialog->get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

        // Show dialog
        dialog->add_button("Cancel", 0);
        dialog->add_button("OK", 1);
        dialog->show_all();
        int result = dialog->run();


        dialog->close();
        while (Gtk::Main::events_pending()) Gtk::Main::iteration();

        if (result == 1) {
            name = entry1.get_text();
            std::string e_2 = entry2.get_text();
            price = std::stod(e_2);
        }

        delete dialog;
        
        if (name.empty()) { throw std::runtime_error{ "Empty product name" }; };
        _store.add_product(Product{name, price});
    } catch(std::runtime_error e) {
        Dialogs::message("#### Error: Invalid input: " + std::string{e.what()});
    }
}

void Controller::list_all_products() {
    std::ostringstream stream;
    stream << _store;
    Dialogs::message(stream.str(), "Available Products");
}

void Controller::add_order() {
    try {
        std::string email = get_string("Email Address:", "Place Order");
        if (email.empty()) throw std::runtime_error{ "Empty email address" };
        int order_num = _store.create_order(email);

        while (true) {
            std::ostringstream oss;
            oss << _store;
            int product_num = get_int(oss.str(), "Product number to add (-1 when done)");
            if (0 <= product_num && product_num < _store.num_products()) {
                int product_quantity = get_int("Quantity", "Product Quantity");
                if (0 <= product_quantity)
                    _store.add_to_order(order_num, Product_order{ _store.product(product_num), product_quantity });
                else {
                    std::ostringstream osp;
                    osp << "#### Invalid quantity : " << product_quantity;
                    Dialogs::message(osp.str(), "Error");
                }
            }   
            else if (product_num == -1) {
                break;
            }
            else {
                std::ostringstream osp;
                osp << "####No such product number: " << product_num;
                Dialogs::message(osp.str(), "Error");
            }




        }
            
    } catch (std::runtime_error e) {
        std::ostringstream ose;
        ose << "#### Place Order aborted:" << e.what();
        Dialogs::message(ose.str(), "Error");
    }
}



void Controller::list_all_orders() {
    std::ostringstream oss;
    for (int i = 0; i < _store.num_orders(); ++i)
        oss << i << ") " << _store.order(i) << std::endl;
        Dialogs::message(oss.str(), "List all Orders");
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
    try {
            Gtk::FileChooserDialog dialog(*_window, "Please choose a file", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
            auto filter_dat = Gtk::FileFilter::create();
            filter_dat->set_name("DAT files");
            filter_dat->add_pattern("*.dat");
            dialog.add_filter(filter_dat);

            auto filter_any = Gtk::FileFilter::create();
            filter_any->set_name("Any files");
            filter_any->add_pattern("*");
            dialog.add_filter(filter_any);

            dialog.set_filename("untitled.dat");

            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Save", Gtk::RESPONSE_OK);

            int result = dialog.run();

            if (result != Gtk::RESPONSE_OK) return;
            _filename = dialog.get_filename();

        std::ofstream ofs{ _filename };
        if (ofs) _store.save(ofs);
        
    }
    catch (std::exception e) {
        Dialogs::message("Save aborted", "Save Store");
    }

}


void Controller::help() {
    std::cout << _view.help() << std::endl;
}


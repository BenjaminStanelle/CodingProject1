#include "view.h"
#include <iostream>
#include <fstream>

View::View(Store& store) : _store{store} { }

std::string View::main_menu() { 
    return R"(
               ========================
               Welcome to C1325 MavMart
               ========================

Products                 Orders                Utility
--------                 ------                -------
(1) Add product          (4) Place order       (9) Help
(2) List all products    (5) List all orders   (0) Exit

)";
}

std::string View::help() {
    std::string result;
    std::ifstream ifs{"help.txt"};
    for(std::string s; std::getline(ifs, s); ) result += s + '\n';
    return result;
}

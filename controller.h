#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include "view.h"
#include "store.h"

class Controller {
  public:
    Controller();
    Controller(Store store);
    void cli();
    void execute_cmd(int cmd);

    // Commands (behaviors)
    void add_product();
    void list_all_products();
    void add_order();
    void list_all_orders();
    void easter_egg();
    void help();
    void load_file();
    void save_file();
  private:
    double get_double(std::string prompt);
    int get_int(std::string prompt);
    Store _store;
    View _view;
};
#endif

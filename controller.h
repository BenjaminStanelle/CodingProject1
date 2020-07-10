#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include "view.h"
#include <gtkmm.h>
#include "store.h"

class Controller {
  public:
    Controller();
    Controller(Gtk::Window* window);
    Controller(Gtk::Window* window, Store store);
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
      double get_double(std::string prompt, std::string title);
    int get_int(std::string prompt, std::string title);
    std::string get_string(std::string prompt, std::string title);
    Gtk::Window* _window;
    std::string _filename;
    Store _store;
    View _view;
};
#endif

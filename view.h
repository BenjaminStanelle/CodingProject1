#ifndef __VIEW_H
#define __VIEW_H
#include "store.h"
#include <string>
#include <vector>

class View {
  public:
    View(Store& store);
    std::string main_menu();
    std::string help();
  private:
    Store& _store;
};
#endif

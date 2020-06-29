#include "main_window.h"
#include <gtkmm.h>
#include <iostream>
int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(argc, argv, "edu.uta.cse.cse1325.example");

    Main_window window;

    return app->run(window);

    return 0;
}

#ifndef _DIALOGS_H
#define _DIALOGS_H

#include <iostream>
#include <gtkmm.h>
#include <vector>
#include <string>
#include <sstream>

class Dialogs {
public:

    // A message is like cout, simply displaying information to the user
    static void message(std::string msg, std::string title = "Info");

    // A question is a message that allows the user to respond with a button
    static int question(std::string msg, std::string title = "Question",
        std::vector<std::string> buttons = { "Cancel", "OK" });

    /*
     static std::string input(std::string msg, std::string title = "Input", std::string default_text = "", std::string cancel_text = "CANCEL");
    */
    // Display an image from a disk file
    static void image(std::string filename, std::string title = "Image", std::string msg = "");
    
    static std::string input_string_double(std::string msg1, std::string msg2, std::string title);

    // Remember window to avoid discouraging warnings
    static void set_window(Gtk::Window* window);

private:
    static Gtk::Window* _window;
};
#endif

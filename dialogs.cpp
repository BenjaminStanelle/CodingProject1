#include "dialogs.h"

//remembers the window to avoid warnings
Gtk::Window* Dialogs::_window;

void Dialogs::set_window(Gtk::Window* window) { _window = window; };

// A message is like cout, simply displaying information to the user
void Dialogs::message(std::string msg, std::string title) {
    Gtk::MessageDialog* dialog = new Gtk::MessageDialog(*_window, title);
    dialog->set_secondary_text(msg, true);
    dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete dialog;
}

int Dialogs::question(std::string msg, std::string title, std::vector<std::string> buttons) {
    Gtk::Dialog* dialog = new Gtk::Dialog(title, *_window);

    Gtk::Label* label = new Gtk::Label(msg);
    label->set_use_markup(true);
    dialog->get_content_area()->pack_start(*label);
    label->show();

    for (int i = 0; i < buttons.size(); ++i) dialog->add_button(buttons[i], i);

    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete label;
    delete dialog;

    return result;
}

std::string Dialogs::input_string_double(std::string msg1, std::string msg2, std::string title) {
    Gtk::Dialog* dialog = new Gtk::Dialog();
    dialog->set_title(title);

    // Name
    Gtk::HBox b_name;

    Gtk::Label l_name{ msg1 };
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry entry1;
    entry1.set_max_length(50);
    b_name.pack_start(entry1, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    // Price
    Gtk::HBox b_price;

    Gtk::Label l_price{ msg2 };
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

    std::string s;
    std::stringstream ss;
    std::string text1 = entry1.get_text();
    std::string text2 = entry2.get_text();
    ss << text1;
    ss << "!price!";
    ss << text2;


    dialog->close();
    while (Gtk::Main::events_pending()) Gtk::Main::iteration();
    
    delete dialog;

    //if ok pressed return text else returned the failed arguement text
    if (result == 1) {
        return ss.str();
    }
    else { return "cancel"; }
}
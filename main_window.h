#ifndef MAIN_WINDOW_H
#define	MAIN_WINDOW_H
#include <gtkmm.h>
#include "controller.h"
#include "dialogs.h"


class Main_window : public Gtk::Window
{

public:
	Main_window();
	virtual ~Main_window();
protected:
	void on_load_click();
	void on_quit_click();
	void on_save_click();
	void on_new_store_click();
	void on_add_product_click();
	void on_list_product_click();
	void on_add_order_click();
	void on_list_order_click();
	void on_easter_egg_click();

private:
	Controller* controller;
	Gtk::Label* sticks;
	Gtk::Label* msg;
	Gtk::ToolButton* botton1;
	Gtk::ToggleToolButton* computer_player;

};
#endif
#include "main_window.h"
#include <iostream>

Main_window::Main_window() {
	//GUI Setup
	Dialogs::set_window(this);

	set_default_size(400, 200);
	set_title("MavMart");
	
	Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
	add(*vbox);

	//menu
	Gtk::MenuBar* menubar = Gtk::manage(new Gtk::MenuBar());
	vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

	//file menu 1
	Gtk::MenuItem* menuitem_file = Gtk::manage(new Gtk::MenuItem("File", true));
	menubar->append((*menuitem_file));
	Gtk::Menu* filemenu = Gtk::manage(new Gtk::Menu());
	menuitem_file->set_submenu(*filemenu);


	//File - drop down Menu
	Gtk::MenuItem* menuitem_new = Gtk::manage(new Gtk::MenuItem("_New", true));
	menuitem_new->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_new_store_click));
	filemenu->append(*menuitem_new);

	//open store
	Gtk::MenuItem* menuitem_load = Gtk::manage(new Gtk::MenuItem("_Open", true));
	menuitem_load->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_load_click));
	filemenu->append(*menuitem_load);


	// Append save to the File menu
	Gtk::MenuItem* menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
	menuitem_save->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_save_click));
	filemenu->append(*menuitem_save);


	//Quit -file
	Gtk::MenuItem* menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
	menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_quit_click));
	filemenu->append(*menuitem_quit);


	//Products - drop down Menu
	Gtk::MenuItem* menuitem_product = Gtk::manage(new Gtk::MenuItem("Product", true));
	menubar->append((*menuitem_product));
	Gtk::Menu* filemenu_products = Gtk::manage(new Gtk::Menu());
	menuitem_product->set_submenu(*filemenu_products);

	//Add new Product
	Gtk::MenuItem* menuitem_add_product = Gtk::manage(new Gtk::MenuItem("_Add New", true));
	menuitem_add_product->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_add_product_click));
	filemenu_products->append(*menuitem_add_product);

	//List all Products
	Gtk::MenuItem* menuitem_list_product = Gtk::manage(new Gtk::MenuItem("_List All", true));
	menuitem_list_product->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_list_product_click));
	filemenu_products->append(*menuitem_list_product);

	//Easter Egg
	Gtk::MenuItem* menuitem_easter = Gtk::manage(new Gtk::MenuItem("_Easter Egg", true));
	menuitem_easter->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_easter_egg_click));
	filemenu_products->append(*menuitem_easter);


	//Orders - drop down Menu
	Gtk::MenuItem* menuitem_order = Gtk::manage(new Gtk::MenuItem("Order", true));
	menubar->append((*menuitem_order));
	Gtk::Menu* filemenu_order = Gtk::manage(new Gtk::Menu());
	menuitem_order->set_submenu(*filemenu_order);

	//Add new Order
	Gtk::MenuItem* menuitem_add_order = Gtk::manage(new Gtk::MenuItem("_Add New", true));
	menuitem_add_order->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_add_order_click));
	filemenu_order->append(*menuitem_add_order);

	//List all orders
	Gtk::MenuItem* menuitem_list_order = Gtk::manage(new Gtk::MenuItem("_List All", true));
	menuitem_list_order->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_list_order_click));
	filemenu_order->append(*menuitem_list_order);

	//ToolBar
	

	vbox->show_all();

	controller = new Controller{ this }; // in case add product is clicked without adding new store.
}

//destructs the class
Main_window::~Main_window() { }

//CALLBACKS

void Main_window::on_quit_click() {
	exit(0);
}
void Main_window::on_new_store_click() {
	controller = new Controller{this};

}

void Main_window::on_load_click() {

}

void Main_window::on_save_click() {
	controller->save_file();

}

void Main_window::on_add_product_click() {

	controller->add_product();
}

void Main_window::on_list_product_click() {
	controller->list_all_products();
}

void Main_window::on_add_order_click() {

	controller->add_order();
}

void Main_window::on_list_order_click() {
	controller->list_all_orders();
}

void Main_window::on_easter_egg_click() {
	controller->easter_egg();
}

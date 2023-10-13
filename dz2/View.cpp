#include "View.h"


View::View(Controller* controller) {
	this->controller = controller;
}

void View::read_data() {
	std::cout << "Enter food reserve (n):\n";
	std::cin >> n;
	std::cout << "Enter food purchase (m):\n";
	std::cin >> m;
	start();
}

void View::show_information() {
	std::vector<People> peoples = controller->get_peoples();
	std::cout << std::endl << "Year = " << controller->get_year() << std::endl;
	std::cout << "All food = " << controller->get_all_food() << std::endl;
	std::cout << "Peoples = " << peoples.size() << std::endl;
	for (People people : peoples)
		std::cout << std::setw(2) << static_cast<char>(toupper(people.get_gender()[0])) << "  ";
	std::cout << std::endl;
	for (People people : peoples) 
		std::cout << std::setw(2) << people.get_age() << "  ";
	std::cout << std::endl;
}

void View::start() {
	controller->start(n, m);
}

void View::show_end() {
	std::cout << "The population lived for " << controller->get_year() - 1 << " years\n";
}

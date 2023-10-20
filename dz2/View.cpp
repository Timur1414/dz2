#include "View.h"


View::View(Controller* controller) {
	this->controller = controller;
}

void View::read_data(int argc, char* argv[], Constants* constants) {
	if (argc < 3) {
		std::cout << "Wrong arguments\n";
		controller->error_arguments();
		return;
	}
	std::string path_to_data;
	if (argc == 4)
		path_to_data = argv[3];
	else
		path_to_data = "data.txt";
	std::ifstream fin(path_to_data);
	std::string input;
	std::vector<int> arguments;
	try {
		while (fin >> input) {
			std::string arg = input.substr(input.find("=") + 1, input.length());
			if (arg == "false")
				arguments.push_back(0);
			else if (arg == "true")
				arguments.push_back(1);
			else
				arguments.push_back(stoi(arg));
		}
	}
	catch (std::invalid_argument) {
		std::cout << "Wrong data\n";
		controller->error_arguments();
		return;
	}
	fin.close();
	if (arguments.size() != 4) {
		std::cout << "Wrong data\n";
		controller->error_arguments();
		return;
	}
	n = std::stoi(argv[1]);
	m = std::stoi(argv[2]);
	start(arguments);
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
	std::cout << std::endl << std::endl;
}

void View::start(std::vector<int> arguments) {
	controller->start(n, m, arguments);
}

void View::show_end() {
	if (controller->check_valide()) {
		std::cout << "The population lived for " << controller->get_year() - 1 << " years\n\n";
		system("pause");
		system("cls");
	}
}

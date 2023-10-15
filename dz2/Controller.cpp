#include "Controller.h"


Controller::Controller() {}

Controller::Controller(Model* model) {
	this->model = model;
}

void Controller::start(int n, int m) {
	model->start(n, m);
	std::ofstream file("log.txt");
	file.close();
	if (!model->get_constants().get_debug())
		system("cls");
}

void Controller::check_conditions() {
	size_t size = model->get_peoples().size();
	model->check_death();
	size_t size_after_death = model->get_peoples().size();
	model->check_food();
	size_t size_after_eat = model->get_peoples().size();
	model->check_offspring();
	size_t size_after_born = model->get_peoples().size();
	logging(model->get_year(), size, size_after_death, size_after_eat, size_after_born);
}

bool Controller::check_end() {
	return model->get_end() == false;
}

std::vector<People> Controller::get_peoples() {
	return model->get_peoples();
}

int Controller::get_year() {
	return model->get_year();
}

int Controller::get_all_food() {
	return model->get_all_food();
}

void Controller::new_year() {
	model->increase_peoples();
	model->increase_year();
	model->increase_food();
}

void Controller::postscript() {
	if (model->get_constants().get_debug()) {
		if (model->get_peoples().empty() || model->get_year() > 16)
			model->set_end(true);
	}
	else {
		system("pause");
		system("cls");
		if (model->get_peoples().empty())
			model->set_end(true);
	}
}

void Controller::logging(int year, size_t size, size_t size_after_death, size_t size_after_eat, size_t size_after_born) {
	std::ofstream file("log.txt", std::ios::app);
	file << "В " << year << " году умерло (от старости): " << size - size_after_death 
		<< " умерло (от голода): " << size_after_death - size_after_eat 
		<< " родилось: " << size_after_born - size_after_eat << std::endl;
	file.close();
}

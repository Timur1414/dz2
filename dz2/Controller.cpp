#include "Controller.h"


Controller::Controller() {}

Controller::Controller(Model* model) {
	this->model = model;
}

void Controller::start(int n, int m, std::vector<int> arguments) {
	model->get_constants()->set_arguments(arguments);
	model->start(n, m);
	std::ofstream file("log.txt");
	file << "CONST_DIE=" << model->get_constants()->get_const_die() << "  "
		<< "CONST_BORN=" << model->get_constants()->get_const_born() << "  "
		<< "CONST_EAT=" << model->get_constants()->get_const_eat() << std::endl;
	file.close();
	if (!model->get_constants()->get_debug())
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
	if (model->get_constants()->get_debug()) {
		if (model->get_peoples().empty() || model->get_year() > 160)
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
	std::pair<int, int> male_and_female_count = model->get_male_and_female_count();
	std::ofstream file("log.txt", std::ios::app);
	file << "В " << std::setw(2) << year << " году умерло (от старости): " << size - size_after_death 
		<< " умерло (от голода): " << size_after_death - size_after_eat 
		<< " родилось: " << size_after_born - size_after_eat
		<< "       Male: " << std::setw(2) << male_and_female_count.first << "     Female: " << std::setw(2) << male_and_female_count.second << std::endl;
	file.close();
}

void Controller::error_arguments() {
	model->set_valide(false);
	model->set_end(true);
}

bool Controller::check_valide() {
	return model->get_valide();
}

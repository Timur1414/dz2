#include "Controller.h"


Controller::Controller() {}

Controller::Controller(Model* model) {
	this->model = model;
}

void Controller::start(int n, int m) {
	model->start(n, m);
	if (!model->get_constants().get_debug())
		system("cls");
}

void Controller::check_conditions() {
	model->check_death();
	model->check_food();
	model->check_offspring();
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

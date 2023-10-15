#pragma once
#include "Model.h"
#include <map>
#include <fstream>


class Controller {
private:
	Model* model;
public:
	Controller();
	Controller(Model* model);

	void start(int n, int m);
	void check_conditions();
	bool check_end();
	std::vector<People> get_peoples();
	int get_year();
	int get_all_food();
	void new_year();
	void postscript();
	void logging(int year, size_t size, size_t size_after_death, size_t size_after_eat, size_t size_after_born);
};
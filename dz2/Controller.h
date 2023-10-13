#pragma once
#include "Model.h"
#include <map>


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
};
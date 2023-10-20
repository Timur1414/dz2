#pragma once
#include "Controller.h"
#include <iostream>
#include <iomanip>


class View {
private:
	Controller* controller;
	int n, m;
public:
	View(Controller* controller);
	void read_data(int argc, char* argv[], Constants* constants);
	void show_information();
	void start(std::vector<int> arguments);
	void show_end();
};
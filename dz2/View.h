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
	void read_data();
	void show_information();
	void start();
	void show_end();
};
#pragma once
#include <string>
#include <vector>
#include <random>
#include <algorithm>


class Constants {
private:
	int CONST_DIE;
	int CONST_BORN;
	int CONST_EAT;
	bool DEBUG;
public:
	Constants();
	Constants(int const_die, int const_born, int const_eat, bool debug);

	int get_const_die();
	int get_const_born();
	int get_const_eat();
	bool get_debug();
};

class People {
private:
	Constants constants;
	std::string gender;
	int age;
	int death_probability;
	int offspring_probability;
	int food_consumption;
public:
	People();
	People(std::string gender, int age, Constants constants);
	std::string get_gender();
	int get_age();
	int get_death_probability();
	int get_offspring_probability();
	int get_food_consumption();

	void update_probability();
	void increase();
};

class Model {
private:
	Constants constants;
	std::vector<People> peoples;
	int n, m;
	int all_food;
	bool end = false;
	int year = 1;
public:
	Model();
	Model(Constants constants);

	Constants get_constants();
	std::vector<People> get_peoples();
	int get_all_food();
	bool get_end();
	int get_year();
	void set_peoples(std::vector<People> peoples);
	void set_end(bool end);

	People create_people();
	void check_death();
	bool enough_food(std::vector<People> peoples);
	int get_need_food();
	void check_food();
	std::vector<std::pair<People, People>> create_pairs();
	void check_offspring();
	void increase_peoples();
	void start(int n, int m);
	void increase_year();
	void increase_food();
};
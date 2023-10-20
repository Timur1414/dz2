#include "Model.h"


People::People() {
	gender = "NULL";
	age = -1;
	death_probability = -1;
	offspring_probability = -1;
	food_consumption = -1;
}

People::People(std::string gender, int age, Constants* constants) {
	this->gender = gender;
	this->age = age;
	this->constants = constants;
	update_probability();
}

std::string People::get_gender() {
	return gender;
}

int People::get_age() {
	return age;
}

int People::get_death_probability() {
	return death_probability;
}

int People::get_offspring_probability() {
	return offspring_probability;
}

int People::get_food_consumption() {
	return food_consumption;
}

void People::update_probability() {
	if (age <= 10)
		death_probability = 0;
	else if (age > 15)
		death_probability = 100;
	else
		death_probability = constants->get_const_die();

	if (age <= 1 || age > 13)
		offspring_probability = 0;
	else
		offspring_probability = constants->get_const_born();

	if (age <= 1)
		food_consumption = 0;
	else
		food_consumption = constants->get_const_eat();
}

void People::increase() {
	age++;
	update_probability();
}


Constants::Constants() {
	CONST_DIE = rand() % 100;
	CONST_BORN = rand() % 100;
	CONST_EAT = rand() % 100;
	DEBUG = true;
}

Constants::Constants(int const_die, int const_born, int const_eat, bool debug) {
	CONST_DIE = const_die;
	CONST_BORN = const_born;
	CONST_EAT = const_eat;
	DEBUG = debug;
}

Constants::Constants(std::vector<int> arg) {
	CONST_DIE = arg[0];
	CONST_BORN = arg[1];
	CONST_EAT = arg[2];
	DEBUG = static_cast<bool>(arg[3]);
}

void Constants::set_arguments(std::vector<int> arg) {
	CONST_DIE = arg[0];
	CONST_BORN = arg[1];
	CONST_EAT = arg[2];
	DEBUG = static_cast<bool>(arg[3]);
}

int Constants::get_const_die() {
	return CONST_DIE;
}

int Constants::get_const_born() {
	return CONST_BORN;
}

int Constants::get_const_eat() {
	return CONST_EAT;
}

bool Constants::get_debug() {
	return DEBUG;
}

void Constants::set_const_die(int const_die) {
	CONST_DIE = const_die;
}

void Constants::set_const_born(int const_born) {
	CONST_BORN = const_born;
}

void Constants::set_const_eat(int const_eat) {
	CONST_EAT = const_eat;
}

void Constants::set_debug(bool debug) {
	DEBUG = debug;
}


Model::Model() {}

Model::Model(Constants* constants) {
	this->constants = constants;
}

Constants* Model::get_constants() {
	return constants;
}

std::vector<People> Model::get_peoples() {
	return peoples;
}

int Model::get_all_food() {
	return all_food;
}

bool Model::get_end() {
	return end;
}

int Model::get_year() {
	return year;
}

void Model::set_peoples(std::vector<People> peoples) {
	this->peoples = peoples;
}

void Model::set_end(bool end) {
	this->end = end;
}

void Model::set_valide(bool valide) {
	this->valide = valide;
}

bool Model::get_valide() {
	return valide;
}

People Model::create_people() {
	std::string gender = ((rand() % 2) == 0 ? "male" : "female");
	return People(gender, 0, constants);
}

void Model::check_death() {
	std::vector<People> new_peoples;
	for (People people : peoples) 
		if ((rand() % 100) >= people.get_death_probability())
			new_peoples.push_back(people);
	peoples = new_peoples;
}

bool Model::enough_food(std::vector<People> peoples) {
	int need_food = 0;
	for_each(peoples.begin(), peoples.end(),
		[&need_food](People people) {
			need_food += people.get_food_consumption();
		});
	return need_food <= all_food;
}

int Model::get_need_food() {
	int res = 0;
	for_each(peoples.begin(), peoples.end(),
		[&res](People people) {
			res += people.get_food_consumption();
		});
	return res;
}

void Model::check_food() {
	std::vector<People> new_peoples = peoples;
	while (!enough_food(new_peoples))
		new_peoples.erase(new_peoples.begin() + (rand() % new_peoples.size()));
	peoples = new_peoples;
	all_food -= get_need_food();
}

std::vector<std::pair<People, People>> Model::create_pairs() {
	std::vector<People> men, women;
	std::vector<std::pair<People, People>> pairs;
	for_each(peoples.begin(), peoples.end(),
		[&men, &women](People people) {
			if (people.get_gender() == "male")
				men.push_back(people);
			else
				women.push_back(people);
		});
	size_t size = std::min(men.size(), women.size());
	for (size_t i = 0; i < size; i++)
		pairs.push_back(std::make_pair(men[i], women[i]));
	return pairs;
}

void Model::check_offspring() {
	std::vector<People> new_peoples = peoples;
	std::vector<std::pair<People, People>> pairs = create_pairs();
	for (size_t i = 0; i < pairs.size(); i++)
		if ((rand() % 100) < std::min(pairs[i].first.get_offspring_probability(), pairs[i].second.get_offspring_probability()))
			new_peoples.push_back(create_people());
	peoples = new_peoples;
}

void Model::increase_peoples() {
	for_each(peoples.begin(), peoples.end(),
		[](People& people) {
			people.increase();
		});
}

void Model::start(int n, int m) {
	this->n = n;
	this->m = m;
	all_food = n;
	peoples.push_back(People("male", 1, constants));
	peoples.push_back(People("female", 1, constants));
}

void Model::increase_year() {
	year++;
}

void Model::increase_food() {
	all_food += m;
}

std::pair<int, int> Model::get_male_and_female_count() {
	int male_count = 0, female_count = 0;
	for (People i : peoples)
		if (i.get_gender() == "male")
			male_count++;
		else
			female_count++;
	return std::make_pair(male_count, female_count);
}

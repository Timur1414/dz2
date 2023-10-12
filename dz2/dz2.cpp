#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>


using namespace std;


const int CONST_DIE = 40;
const int CONST_BORN = 70;
const int CONST_EAT = 2;
bool DEBUG = true;


class People {
private:
	string gender;
	int age;
	int death_probability;
	int offspring_probability;
	int food_consumption;
public:
	People(string gender, int age) {
		this->gender = gender;
		this->age = age;
		update_probability();
	}
	string get_gender() {
		return this->gender;
	}
	int get_age() {
		return this->age;
	}
	int get_death_probability() {
		return this->death_probability;
	}
	int get_offspring_probability() {
		return this->offspring_probability;
	}
	int get_food_consumption() {
		return this->food_consumption;
	}

	void update_probability() {
		if (this->age < 10)
			this->death_probability = 0;
		else if (this->age > 15)
			this->death_probability = 100;
		else
			this->death_probability = CONST_DIE;

		if (this->age < 1)
			this->offspring_probability = 0;
		else if (this->age > 13)
			this->offspring_probability = 0;
		else
			this->offspring_probability = CONST_BORN;

		if (this->age <= 1)
			this->food_consumption = 0;
		else
			this->food_consumption = CONST_EAT;
	}
	void increase() {
		this->age++;
		update_probability();
	}
};


vector<People> check_death(vector<People> peoples) {
	vector<People> new_peoples;
	for (People people : peoples) {
		if ((rand() % 100) >= people.get_death_probability())
			new_peoples.push_back(people);
	}
	return new_peoples;
}


bool enough_food(int all_food, vector<People> peoples) {
	int need_food = 0;
	for_each(peoples.begin(), peoples.end(), 
		[&need_food](People people) {
			need_food += people.get_food_consumption();
		});
	return need_food <= all_food;
}


int get_need_food(vector<People> peoples) {
	int res = 0;
	for_each(peoples.begin(), peoples.end(), 
		[&res](People people) {
			res += people.get_food_consumption();
		});
	return res;
}


vector<People> check_food(int& all_food, vector<People> peoples) {
	vector<People> new_peoples = peoples;
	while (!enough_food(all_food, new_peoples))
		new_peoples.erase(new_peoples.begin() + (rand() % new_peoples.size()));
	all_food -= get_need_food(new_peoples);
	return new_peoples;
}


void increase(vector<People>& peoples) {
	for_each(peoples.begin(), peoples.end(), 
		[](People& people) {
			people.increase();
		});
}


void show_information(int year, int all_food, vector<People> peoples) {
	cout << "Year = " << year << endl;
	cout << "All food = " << all_food << endl;
	cout << "Peoples = " << peoples.size() << endl;
	for (People people : peoples) {
		cout << people.get_age() << " ";
	}
	cout << endl;
}


int main() {
	srand(time(0));
	int n, m;
	cout << "Enter food reserve (n):\n";
	cin >> n;
	cout << "Enter food purchase (m):\n";
	cin >> m;
	vector<People> peoples;
	peoples.push_back(People("male", 1));
	peoples.push_back(People("female", 1));

	int all_food = n;
	bool end = false;
	int year = 1;
	while (!end) {
		peoples = check_death(peoples);
		peoples = check_food(all_food, peoples);

		show_information(year, all_food, peoples);
		increase(peoples);
		year++;
		all_food += m;
		if (!DEBUG) {
			system("pause");
			system("cls");
		}
		else {
			if (year > 16)
				end = true;
		}
	}


	return 0;
}

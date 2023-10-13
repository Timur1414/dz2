#include <ctime>

#include "Model.h"
#include "Controller.h"
#include "View.h"


using namespace std;


int main() {
	Constants constants(40, 70, 2, false);
	srand(time(0));
	Model model(constants);
	Controller controller(&model);
	View view(&controller);

	view.read_data();
	while (controller.check_end()) {
		controller.check_conditions();
		view.show_information();
		controller.new_year();
		controller.postscript();
	}
	view.show_end();


	return 0;
}

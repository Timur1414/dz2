#include <ctime>
#include "Model.h"
#include "Controller.h"
#include "View.h"


int main(int argc, char* argv[]) {
	srand(time(0));
	Constants constants;
	Model model(&constants);
	Controller controller(&model);
	View view(&controller);

	view.read_data(argc, argv, &constants);
	while (controller.check_end()) {
		controller.check_conditions();
		view.show_information();
		controller.new_year();
		controller.postscript();
	}
	view.show_end();


	return 0;
}

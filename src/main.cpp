#include "../hdr/Application.hpp"

int main() {
	app::create(); 

	while (app::isOpen())
		app::update();

	app::cleanUp();
	return 0; 
}
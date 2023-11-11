#include "../hdr/Application.hpp"

namespace app {
	gs::util::Clock timer;

	void create() {
		FreeConsole(); 

		render::window::create();
		render::loadAssets();
		render::ui::loadAssets(); 
		Image::initColorPalettes();

		sourceImage.create(imageSize.x, imageSize.y); 
		updateFromSourceImage(); 
	}
	void update() {
		timer.begin(); 

		handleEvents(); 
		if (render::window::eventTick % (render::window::eventFramerate 
				/ render::window::visualFramerate) == 0)
			handleGraphics(); 

		timer.end(); 
		timer.wait(render::window::eventFramerate); 
	}
	void handleEvents() {
		render::window::update(); 

		if (!render::window::winmain->hasFocus())
			return; 

		render::ui::updateMenu(); 
		render::updateImageRendering(); 
		render::updateImageOutline();
		render::ui::updateImageMenu(); 
	}
	void handleGraphics() {
		render::window::clear(render::backgroundColor); 

		render::ui::renderImageMenu(); 
		render::renderImageOutline();
		render::renderImage(image, *render::window::winmain); 
		render::ui::renderMenu(); 

		render::window::display(); 
	}
	void cleanUp() {
		render::window::cleanUp(); 
	}

	bool isOpen() {
		return render::window::winmain->isOpen(); 
	}
}
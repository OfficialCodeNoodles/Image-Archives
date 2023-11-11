#pragma once

// Dependencies
#include "../hdr/UI.hpp"

namespace app {
	using namespace engine; 
	extern gs::util::Clock timer; 

	void create(); 
	void update();
	void handleEvents(); 
	void handleGraphics(); 
	void cleanUp();

	bool isOpen(); 
}
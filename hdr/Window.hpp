#pragma once

// Dependencies
#include "Include.hpp"

namespace engine {
	namespace render {
		namespace window {
			constexpr const char* title = "Image Archive";
			extern const gs::Vec2i defaultWindowSize; 

			extern sf::RenderWindow* winmain; 
			extern bool isFullscreen; 
			extern int eventFramerate; 
			extern int visualFramerate; 
			extern int eventTick; 
			extern sf::Image icon; 

			void create(bool fullscreen = true); 
			void initialize(); 
			void update(); 
			void cleanUp(); 

			void clear(gs::Color backgroundColor = gs::Color::Black); 
			void display(); 
		}
	}
}
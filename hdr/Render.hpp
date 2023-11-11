#pragma once

// Dependencies
#include "Window.hpp"
#include "Image.hpp"

namespace engine {
	namespace render {
		extern gs::Color backgroundColor;  
		extern float outlineThickness; 
		extern gs::Color outlineColor;
		extern float imageRenderingAspectRatio; 
		extern float imageRenderingOutlineWidth; 
		extern float imageRenderingOutlineHeight; 
		extern float imageRenderingWidth;
		extern float imageRenderingHeight; 
		extern bool maintainSquarePixels; 
		extern sf::RectangleShape imageRenderingOutline; 

		void loadAssets(); 
		void initAssets();

		void updateImageRendering(); 
		void renderImage(Image& image, sf::RenderTarget& target);
		void updateImageOutline();
		void renderImageOutline(); 
	}
}
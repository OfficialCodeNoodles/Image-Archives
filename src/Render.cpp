#include "../hdr/UI.hpp"

namespace engine {
	namespace render {
		gs::Color backgroundColor = gs::Color(13, 15, 17);
		float outlineThickness = 5.0f;
		gs::Color outlineColor = gs::Color::White;
		float imageRenderingAspectRatio = 16.0f / 9.0f;
		float imageRenderingOutlineWidth = 1920.0f; 
		float imageRenderingOutlineHeight;
		float imageRenderingWidth; 
		float imageRenderingHeight;
		bool maintainSquarePixels = false; 
		sf::RectangleShape imageRenderingOutline;

		void loadAssets() {
			initAssets(); 
		}
		void initAssets() {
			// Initalizes the outline for the image rendering. 

			imageRenderingOutline.setFillColor(gs::Color::Black); 
			imageRenderingOutline.setOutlineThickness(outlineThickness); 
			imageRenderingOutline.setOutlineColor(outlineColor); 
		}

		void updateImageRendering() {
			imageRenderingOutlineWidth = ui::menu.getPosition().x; 
			imageRenderingOutlineHeight = imageRenderingOutlineWidth / imageRenderingAspectRatio; 
			
			if (maintainSquarePixels) {
				const float imageAspectRatio = static_cast<float>(image.getSize().x)
					/ static_cast<float>(image.getSize().y);

				if (imageAspectRatio < imageRenderingAspectRatio) {
					imageRenderingWidth = imageRenderingOutlineHeight * imageAspectRatio;
					imageRenderingHeight = imageRenderingOutlineHeight;
				}
				else {
					imageRenderingWidth = imageRenderingOutlineWidth;
					imageRenderingHeight = imageRenderingOutlineWidth / imageAspectRatio;
				}
			}
			else {
				imageRenderingWidth = imageRenderingOutlineWidth; 
				imageRenderingHeight = imageRenderingOutlineHeight; 
			}
		}
		void renderImage(Image& image, sf::RenderTarget& target) {
			sf::Sprite imageSprite(image.getTexture());

			imageSprite.setScale(gs::Vec2f(
				imageRenderingWidth / static_cast<float>(image.getSize().x),
				imageRenderingHeight / static_cast<float>(image.getSize().y) 
			));
			imageSprite.setPosition(
				(imageRenderingOutlineWidth - imageRenderingWidth) * 0.5f, 
				(window::defaultWindowSize.y - imageRenderingHeight) * 0.5f
			); 

			target.draw(imageSprite); 
		}
		void updateImageOutline() {
			imageRenderingOutline.setSize(
				gs::Vec2f(imageRenderingOutlineWidth, imageRenderingOutlineHeight)
			);
			imageRenderingOutline.setPosition(
				gs::Vec2f(0.0f, (window::defaultWindowSize.y - imageRenderingOutlineHeight) * 0.5f) 
			);
		}
		void renderImageOutline() {
			window::winmain->draw(imageRenderingOutline); 
		}
	}
}
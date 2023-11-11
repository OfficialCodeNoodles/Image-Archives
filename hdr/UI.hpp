#pragma once

// Dependencies
#include "Render.hpp"

namespace engine {
	namespace render {
		namespace ui {
			extern const std::string assetDirectory; 
			extern const float closedMenuHorizontalPosition; 
			extern const float openMenuHorizontalPosition; 
			extern const gs::Color panelColor; 

			extern sf::Font font; 
			extern bool menuOpen;
			extern sf::RectangleShape rightPanel;
			extern gs::Menu menu; 
			extern gs::Button menuOpenButton; 
			extern sf::Texture arrowTextures[4]; 
			extern gs::Text menuTitleText; 
			extern gs::Text menuImageOptionsText; 
			extern gs::Text menuImageWidthText; 
			extern gs::Slider menuImageWidthSlider; 
			extern gs::Textbox menuImageWidthTextbox; 
			extern gs::Text menuImageHeightText; 
			extern gs::Slider menuImageHeightSlider; 
			extern gs::Textbox menuImageHeightTextbox; 
			extern gs::Checkbox menuImageAutoAdjustCheckbox; 
			extern sf::Texture checkBoxTextures[2]; 
			extern gs::Text menuImageAutoAdjustText; 
			extern gs::Button menuImageChangeColorPaletteButton; 
			extern gs::Text menuImageColorPaletteText; 
			extern gs::Checkbox menuImageAutoAdjustColorCheckbox;
			extern gs::Text menuImageAutoAdjustColorText; 
			extern gs::Button menuImageValueCountUpArrowButton; 
			extern gs::Button menuImageValueCountDownArrowButton;
			extern gs::Textbox menuImageValueCountTextbox; 
			extern gs::Text menuImageValueCountText; 
			extern gs::Checkbox menuImageAutoAdjustValueCountCheckbox; 
			extern gs::Text menuImageAutoAdjustValueCountText; 
			extern gs::Button menuImageGenerateButton; 
			extern gs::Button menuImageGenerateRandomButton; 
			extern gs::Text menuDisplayOptionsText;
			extern gs::Checkbox menuDisplayTopImageMenuCheckbox; 
			extern gs::Text menuDisplayTopImageMenuText; 
			extern gs::Checkbox menuDisplayMaintainSquarePixelsCheckbox; 
			extern gs::Text menuDisplayMaintainSquarePixelsText; 
			extern gs::Text menuBottomText; 
			extern gs::Button menuExitButton; 
			extern gs::Menu topImageMenu; 
			extern gs::RoundedRectangle topImageDividers[2]; 
			extern gs::Text imageSourceInfoTitleText; 
			extern gs::Text imageSourceInfoText; 
			extern gs::Text menuImageInfoTitleText; 
			extern gs::Text menuImageInfoText; 
			extern gs::Text menuImageIDInfoTitleText; 
			extern gs::Text menuImageIDInfoText; 
			extern gs::Menu bottomImageMenu; 
			extern gs::RoundedRectangle bottomImageDivider; 
			extern gs::Button bottomButtons[4]; 

			void loadAssets(); 
			void initAssets(); 
 
			void updateMenu();  
			void renderMenu(); 
			void updateImageMenu(); 
			void renderImageMenu(); 
		}
	}
}
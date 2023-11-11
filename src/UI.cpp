#include "../hdr/UI.hpp"

namespace engine {
	namespace render {
		namespace ui {
			const std::string assetDirectory = "assets/";
			const float closedMenuHorizontalPosition = 1920.0f;
			const float openMenuHorizontalPosition = 1440.0f; 
			const gs::Color panelColor = gs::Color(35, 38, 40); 

			sf::Font font;
			bool menuOpen = true; 
			sf::RectangleShape rightPanel;
			gs::Menu menu;
			gs::Button menuOpenButton;
			sf::Texture arrowTextures[4];
			gs::Text menuTitleText;
			gs::Text menuImageOptionsText;
			gs::Text menuImageWidthText;
			gs::Slider menuImageWidthSlider;
			gs::Textbox menuImageWidthTextbox;
			gs::Text menuImageHeightText;
			gs::Slider menuImageHeightSlider;
			gs::Textbox menuImageHeightTextbox;
			gs::Checkbox menuImageAutoAdjustCheckbox;
			sf::Texture checkBoxTextures[2];
			gs::Text menuImageAutoAdjustText;
			gs::Button menuImageChangeColorPaletteButton;
			gs::Text menuImageColorPaletteText;
			gs::Checkbox menuImageAutoAdjustColorCheckbox;
			gs::Text menuImageAutoAdjustColorText;
			gs::Button menuImageValueCountUpArrowButton;
			gs::Button menuImageValueCountDownArrowButton;
			gs::Textbox menuImageValueCountTextbox;
			gs::Text menuImageValueCountText;
			gs::Checkbox menuImageAutoAdjustValueCountCheckbox;
			gs::Text menuImageAutoAdjustValueCountText;
			gs::Button menuImageGenerateButton;
			gs::Button menuImageGenerateRandomButton;
			gs::Text menuDisplayOptionsText;
			gs::Checkbox menuDisplayTopImageMenuCheckbox;
			gs::Text menuDisplayTopImageMenuText;
			gs::Checkbox menuDisplayMaintainSquarePixelsCheckbox;
			gs::Text menuDisplayMaintainSquarePixelsText;
			gs::Text menuBottomText;
			gs::Button menuExitButton;
			gs::Menu topImageMenu;
			gs::RoundedRectangle topImageDividers[2];
			gs::Text imageSourceInfoTitleText;
			gs::Text imageSourceInfoText;
			gs::Text menuImageInfoTitleText;
			gs::Text menuImageInfoText;
			gs::Text menuImageIDInfoTitleText;
			gs::Text menuImageIDInfoText;
			gs::Menu bottomImageMenu;
			gs::RoundedRectangle bottomImageDivider;
			gs::Button bottomButtons[4];

			void loadAssets() {
				// Loads in the font used for text rendering.
				font.loadFromFile(assetDirectory + "Retron2000.ttf");

				// Loads in the arrow textures. 
				arrowTextures[0].loadFromFile(assetDirectory + "leftArrow.png");
				arrowTextures[1].loadFromFile(assetDirectory + "rightArrow.png");
				arrowTextures[2].loadFromFile(assetDirectory + "upArrow.png"); 
				arrowTextures[3].loadFromFile(assetDirectory + "downArrow.png"); 

				// Loads in the checkbox textures.
				checkBoxTextures[0].loadFromFile(assetDirectory + "uncheckedBox.png"); 
				checkBoxTextures[1].loadFromFile(assetDirectory + "checkedBox.png"); 

				initAssets(); 
			}
			void initAssets() {
				// Initializes the right panel. 
				rightPanel.setSize(gs::Vec2f(
					window::defaultWindowSize.x - openMenuHorizontalPosition,
					window::defaultWindowSize.y
				));
				rightPanel.setFillColor(panelColor); 
				rightPanel.setOutlineThickness(outlineThickness); 
				rightPanel.setOutlineColor(outlineColor); 
				
				// Initialize the menu. 
				menu.setPosition(closedMenuHorizontalPosition, 0.0f); 

				// Initializes the menu components. 
				menuOpenButton.setSize(32.0f, 80.0f); 
				menuOpenButton.setPosition(-menuOpenButton.getSize().x - outlineThickness, 24.0f); 
				menuOpenButton.setOutlineThickness(outlineThickness); 
				menuOpenButton.setOutlineColor(outlineColor); 
				menuOpenButton.clear();
				menuOpenButton.setSelectedFillColor(gs::Color(180, 180, 180)); 
				menu.add(&menuOpenButton); 

				menuTitleText.setPosition(80.0f, 10.0f); 
				menuTitleText.getText().setCharacterSize(75); 
				menuTitleText.setFont(font); 
				menuTitleText.setString("Options"); 
				menuTitleText.setShadow(true); 
				menuTitleText.setShadowOffset(0.0f, 8.0f); 
				menuTitleText.getText().setStyle(sf::Text::Bold); 
				menu.add(&menuTitleText); 

				menuImageOptionsText = menuTitleText; 
				menuImageOptionsText.setPosition(25.0f, 115.0f);
				menuImageOptionsText.getText().setCharacterSize(40); 
				menuImageOptionsText.setString("Image Config"); 
				menu.add(&menuImageOptionsText); 

				menuImageWidthText = menuImageOptionsText; 
				menuImageWidthText.move(20.0f, 70.0f); 
				menuImageWidthText.getText().setCharacterSize(30); 
				menuImageWidthText.setFillColor(gs::Color(200, 200, 200)); 
				menuImageWidthText.setString("Width"); 
				menuImageWidthText.setShadow(false); 
				menu.add(&menuImageWidthText); 

				menuImageWidthSlider.setSize(150.0f, 15.0f); 
				menuImageWidthSlider.setPosition(170.0f, 198.0f); 
				menuImageWidthSlider.button.setSize(20.0f, 30.0f); 
				menuImageWidthSlider.setPercentage(imageSize.x - 1, maxImageSize.x); 
				menuImageWidthSlider.button.clearScaleModifiers();
				menuImageWidthSlider.button.setOutlineThickness(1.0f);
				
				menu.add(&menuImageWidthSlider); 

				menuImageWidthTextbox.setSize(80.0f, 30.0f); 
				menuImageWidthTextbox.setPosition(
					345.0f, menuImageWidthSlider.getCenter().y
						- menuImageWidthTextbox.getSize().y * 0.5f
				);
				menuImageWidthTextbox.setScaleModifiers(1.0f); 
				menuImageWidthTextbox.setTextScale(0.75f, 0.75f); 
				menuImageWidthTextbox.setFont(font); 
				menuImageWidthTextbox.setTextOffset(0.0f, -2.0f); 
				menuImageWidthTextbox.setMaxInputLength(4); 
				menuImageWidthTextbox.setMessageString(""); 
				menuImageWidthTextbox.validInputs = gs::Textbox::ValidInputs::Numeric; 
				menuImageWidthTextbox.setStoredString(std::to_string(imageSize.x)); 
				menu.add(&menuImageWidthTextbox); 

				menuImageHeightText = menuImageWidthText; 
				menuImageHeightText.move(0.0f, 50.0f); 
				menuImageHeightText.setString("Height");
				menu.add(&menuImageHeightText); 

				menuImageHeightSlider = menuImageWidthSlider; 
				menuImageHeightSlider.move(0.0f, 50.0f); 
				menuImageHeightSlider.setPercentage(imageSize.y - 1, maxImageSize.y);
				menu.add(&menuImageHeightSlider); 

				menuImageHeightTextbox = menuImageWidthTextbox; 
				menuImageHeightTextbox.move(0.0f, 50.0f); 
				menuImageHeightTextbox.setStoredString(std::to_string(imageSize.y));
				menu.add(&menuImageHeightTextbox); 

				menuImageAutoAdjustCheckbox.setSize(40.0f, 40.0f); 
				menuImageAutoAdjustCheckbox.setPosition(53.0f, 295.0f); 
				menuImageAutoAdjustCheckbox.clear(); 
				menuImageAutoAdjustCheckbox.setSelectedFillColor(gs::Color(200, 200, 200)); 
				menuImageAutoAdjustCheckbox.isSelected = true; 
				menuImageAutoAdjustCheckbox.isClickedOn = resizeImage; 
				menuImageAutoAdjustCheckbox.eventTriggerer = gs::Button::EventTriggerer::None;
				menuImageAutoAdjustCheckbox.update();
				menuImageAutoAdjustCheckbox.eventTriggerer = 
					gs::Button::EventTriggerer::ActiveMouse;
				menu.add(&menuImageAutoAdjustCheckbox); 

				menuImageAutoAdjustText = menuImageWidthText; 
				menuImageAutoAdjustText.setPosition(110.0f, 302.0f); 
				menuImageAutoAdjustText.getText().setCharacterSize(22);  
				menuImageAutoAdjustText.setString("Auto Adjust Image Size"); 
				menu.add(&menuImageAutoAdjustText); 

				menuImageChangeColorPaletteButton.setSize(200.0f, 50.0f); 
				menuImageChangeColorPaletteButton.setPosition(53.0f, 350.0f);
				menuImageChangeColorPaletteButton.setFont(font); 
				menuImageChangeColorPaletteButton.setString("Change Palette"); 
				menuImageChangeColorPaletteButton.setTextScale(0.7f, 0.7f); 
				menuImageChangeColorPaletteButton.setInactiveTextFillColor(
					menuImageWidthSlider.getOffColor()
				); 
				menuImageChangeColorPaletteButton.clearScaleModifiers(); 
				menu.add(&menuImageChangeColorPaletteButton); 

				menuImageColorPaletteText = menuImageAutoAdjustText; 
				menuImageColorPaletteText.setPosition(270.0f, 363.0f);
				menuImageColorPaletteText.setString(
					Image::colorPaletteStrings[static_cast<int>(image.colorPalette)]
				); 
				menu.add(&menuImageColorPaletteText); 

				menuImageAutoAdjustColorCheckbox = menuImageAutoAdjustCheckbox; 
				menuImageAutoAdjustColorCheckbox.move(0.0f, 120.0f); 
				menuImageAutoAdjustColorCheckbox.isSelected = true; 
				menuImageAutoAdjustColorCheckbox.isClickedOn = recolorImage; 
				menuImageAutoAdjustColorCheckbox.eventTriggerer = 
					gs::Button::EventTriggerer::None; 
				menuImageAutoAdjustColorCheckbox.update(); 
				menuImageAutoAdjustColorCheckbox.eventTriggerer = 
					gs::Button::EventTriggerer::ActiveMouse; 
				menu.add(&menuImageAutoAdjustColorCheckbox);

				menuImageAutoAdjustColorText = menuImageAutoAdjustText;
				menuImageAutoAdjustColorText.setPosition(110.0f, 423.0f);
				menuImageAutoAdjustColorText.setString("Auto Adjust Image Color"); 
				menu.add(&menuImageAutoAdjustColorText); 

				menuImageValueCountUpArrowButton.setSize(40.0f, 25.0f);
				menuImageValueCountUpArrowButton.setPosition(53.0f, 470.0f); 
				menuImageValueCountUpArrowButton.clear(); 
				menuImageValueCountUpArrowButton.setSelectedFillColor(gs::Color(200, 200, 200)); 
				menuImageValueCountUpArrowButton.setTexture(arrowTextures[2]); 
				menu.add(&menuImageValueCountUpArrowButton); 

				menuImageValueCountDownArrowButton = menuImageValueCountUpArrowButton; 
				menuImageValueCountDownArrowButton.move(
					0.0f, menuImageValueCountUpArrowButton.getSize().y
				); 
				menuImageValueCountDownArrowButton.setTexture(arrowTextures[3]); 
				menu.add(&menuImageValueCountDownArrowButton); 

				const float valueCountTextboxOffset = 
					menuImageValueCountTextbox.getOutlineThickness(); 

				menuImageValueCountTextbox = menuImageWidthTextbox; 
				menuImageValueCountTextbox.setSize(
					45.0f - valueCountTextboxOffset * 2.0f, 50.0f - valueCountTextboxOffset * 2.0f
				);
				menuImageValueCountTextbox.setPosition(
					menuImageValueCountUpArrowButton.getPosition().x 
						+ menuImageValueCountUpArrowButton.getSize().x + valueCountTextboxOffset,
					menuImageValueCountUpArrowButton.getPosition().y + valueCountTextboxOffset
				); 
				menuImageValueCountTextbox.setStoredString(std::to_string(imageColorValues)); 
				menuImageValueCountTextbox.eventTriggerer = gs::Button::EventTriggerer::None; 
				menu.add(&menuImageValueCountTextbox); 

				menuImageValueCountText = menuImageAutoAdjustText;
				menuImageValueCountText.setPosition(155.0f, 480.0f);
				menuImageValueCountText.setString("Pixels Per Character");
				menu.add(&menuImageValueCountText); 

				menuImageAutoAdjustValueCountCheckbox = menuImageAutoAdjustColorCheckbox;
				menuImageAutoAdjustValueCountCheckbox.move(0.0f, 120.0f); 
				menuImageAutoAdjustValueCountCheckbox.isSelected = true;
				menuImageAutoAdjustValueCountCheckbox.isClickedOn = revalueImage;
				menuImageAutoAdjustValueCountCheckbox.eventTriggerer = 
					gs::Button::EventTriggerer::None;
				menuImageAutoAdjustValueCountCheckbox.update();
				menuImageAutoAdjustValueCountCheckbox.eventTriggerer = 
					gs::Button::EventTriggerer::ActiveMouse; 
				menu.add(&menuImageAutoAdjustValueCountCheckbox); 

				menuImageAutoAdjustValueCountText = menuImageAutoAdjustColorText; 
				menuImageAutoAdjustValueCountText.setPosition(110.0f, 542.0f); 
				menuImageAutoAdjustValueCountText.setString("Auto Adjust Value Counts"); 
				menu.add(&menuImageAutoAdjustValueCountText);

				menuImageGenerateButton = menuImageChangeColorPaletteButton; 
				menuImageGenerateButton.setSize(380.0f, 50.0f); 
				menuImageGenerateButton.move(0.0f, 241.0f);
				menuImageGenerateButton.setString("Generate Image");
				menu.add(&menuImageGenerateButton); 

				menuImageGenerateRandomButton = menuImageGenerateButton; 
				menuImageGenerateRandomButton.move(0.0f, 60.0f); 
				menuImageGenerateRandomButton.setString("Generate Random Image"); 
				menu.add(&menuImageGenerateRandomButton); 

				menuDisplayOptionsText = menuImageOptionsText; 
				menuDisplayOptionsText.move(0.0f, 600.0f); 
				menuDisplayOptionsText.setString("Display Config");
				menu.add(&menuDisplayOptionsText); 

				menuDisplayTopImageMenuCheckbox = menuImageAutoAdjustColorCheckbox; 
				menuDisplayTopImageMenuCheckbox.move(0.0f, 370.0f); 
				menuDisplayTopImageMenuCheckbox.isSelected = true;  
				menuDisplayTopImageMenuCheckbox.isClickedOn = true; 
				menuDisplayTopImageMenuCheckbox.eventTriggerer = gs::Button::EventTriggerer::None; 
				menuDisplayTopImageMenuCheckbox.update(); 
				menuDisplayTopImageMenuCheckbox.eventTriggerer = 
					gs::Button::EventTriggerer::ActiveMouse; 
				menu.add(&menuDisplayTopImageMenuCheckbox);

				menuDisplayTopImageMenuText = menuImageAutoAdjustColorText; 
				menuDisplayTopImageMenuText.move(0.0f, 370.0f); 
				menuDisplayTopImageMenuText.setString("Show Image Information"); 
				menu.add(&menuDisplayTopImageMenuText); 

				menuDisplayMaintainSquarePixelsCheckbox = menuImageAutoAdjustColorCheckbox; 
				menuDisplayMaintainSquarePixelsCheckbox.move(0.0f, 424.0f);
				menuDisplayMaintainSquarePixelsCheckbox.isSelected = true;
				menuDisplayMaintainSquarePixelsCheckbox.isClickedOn = maintainSquarePixels;
				menuDisplayMaintainSquarePixelsCheckbox.eventTriggerer = gs::Button::EventTriggerer::None;
				menuDisplayMaintainSquarePixelsCheckbox.update();
				menuDisplayMaintainSquarePixelsCheckbox.eventTriggerer =
					gs::Button::EventTriggerer::ActiveMouse;
				menu.add(&menuDisplayMaintainSquarePixelsCheckbox); 

				menuDisplayMaintainSquarePixelsText = menuImageAutoAdjustColorText; 
				menuDisplayMaintainSquarePixelsText.move(0.0f, 424.0f);
				menuDisplayMaintainSquarePixelsText.setString("Maintain Square Pixels"); 
				menu.add(&menuDisplayMaintainSquarePixelsText); 

				menuBottomText = menuImageWidthText; 
				menuBottomText.getText().setCharacterSize(20); 
				menuBottomText.move(80.0f, 865.0f); 
				menuBottomText.setString("CodeNoodles 2023"); 
				menuBottomText.setFillColor(gs::Color(127, 127, 127)); 
				menu.add(&menuBottomText); 

				menuExitButton = menuImageChangeColorPaletteButton; 
				menuExitButton.setSize(150.0f, 60.0f); 
				menuExitButton.setPosition(160.0f, 980.0f); 
				menuExitButton.setString("Exit"); 
				menuExitButton.setTextScale(1.0f, 1.0f); 
				menu.add(&menuExitButton); 

				menu.setPosition(openMenuHorizontalPosition, 0.0f); 
				menu.update(); 

				for (int topImageDividerIndex = 0; topImageDividerIndex < 2;
					topImageDividerIndex++)
				{
					gs::RoundedRectangle& roundedRectangle = topImageDividers[topImageDividerIndex];

					roundedRectangle.setSize(5.0f, 88.0f);
					roundedRectangle.setCornerRadius(2.5f);
					roundedRectangle.setPosition(
						(1 + topImageDividerIndex) * (openMenuHorizontalPosition / 3.0f)
						- (roundedRectangle.getSize().x / 2.0f), 20.0f
					);
					roundedRectangle.setFillColor(gs::Color(200, 200, 200));

					topImageMenu.add(&roundedRectangle);
				}

				imageSourceInfoTitleText = menuImageAutoAdjustText; 
				imageSourceInfoTitleText.setPosition(15.0f, 12.0f); 
				imageSourceInfoTitleText.getText().setCharacterSize(30);
				imageSourceInfoTitleText.setString("Source Image Info");
				imageSourceInfoTitleText.setFillColor(gs::Color::White);
				topImageMenu.add(&imageSourceInfoTitleText); 

				imageSourceInfoText = menuImageAutoAdjustText;
				imageSourceInfoText.setPosition(15.0f, 58.0f); 
				topImageMenu.add(&imageSourceInfoText); 

				const float subdivisionDistance = openMenuHorizontalPosition / 3.0f; 

				menuImageInfoTitleText = imageSourceInfoTitleText; 
				menuImageInfoTitleText.move(subdivisionDistance, 0.0f); 
				menuImageInfoTitleText.setString("Image Info");
				topImageMenu.add(&menuImageInfoTitleText); 

				menuImageInfoText = imageSourceInfoText; 
				menuImageInfoText.move(subdivisionDistance, 0.0f); 
				topImageMenu.add(&menuImageInfoText); 

				menuImageIDInfoTitleText = imageSourceInfoTitleText; 
				menuImageIDInfoTitleText.move(subdivisionDistance * 2.0f, 0.0f); 
				menuImageIDInfoTitleText.setString("ID Info"); 
				topImageMenu.add(&menuImageIDInfoTitleText); 

				menuImageIDInfoText = imageSourceInfoText; 
				menuImageIDInfoText.move(subdivisionDistance * 2.0f, 0.0f); 
				topImageMenu.add(&menuImageIDInfoText); 

				topImageMenu.update(); 

				bottomImageDivider = topImageDividers[0]; 
				bottomImageDivider.setPosition(
					(openMenuHorizontalPosition / 2.0f) - (bottomImageDivider.getSize().x / 2.0f)
						- outlineThickness,
					970.0f
				); 
				bottomImageMenu.add(&bottomImageDivider); 

				const float loadingButtonLength = 320.0f; 
				const float loadingButtonGap = 22.0f; 
				const std::string bottomButtonStrings[4] = { 
					"Load Image", "Load Text", "Save Image", "Save Text"
				};

				for (int loadingButtonIndex = 0; loadingButtonIndex < 4; loadingButtonIndex++) {
					gs::Button& loadingButton = bottomButtons[loadingButtonIndex]; 

					loadingButton.setSize(loadingButtonLength, 70.0f); 
					loadingButton.setPosition(
						20.0f + (loadingButtonLength * loadingButtonIndex) 
							+ (loadingButtonGap * loadingButtonIndex),
						980.0f
					); 
					loadingButton.setFont(font); 
					loadingButton.setString(bottomButtonStrings[loadingButtonIndex]);
					loadingButton.setTextOffset(0.0f, -2.0f); 

					if (loadingButtonIndex > 1)
						loadingButton.move(loadingButtonGap * 2.0f, 0.0f); 

					bottomImageMenu.add(&loadingButton); 
				}

				bottomImageMenu.update(); 
			}

			void updateMenu() {
				if (menuOpenButton.isSelected && menuOpenButton.isClickedOn)
					menuOpen = !menuOpen; 

				menu.setPosition(gs::util::approach(
					menu.getPosition().x, menuOpen ? openMenuHorizontalPosition
						: closedMenuHorizontalPosition, 15.0f), 
					0.0f
				);
				rightPanel.setPosition(menu.getPosition()); 
				menuOpenButton.setTexture(arrowTextures[menuOpen ? 1 : 0]); 
				menuImageAutoAdjustCheckbox.setTexture(checkBoxTextures[resizeImage ? 1 : 0]);
				menuImageAutoAdjustColorCheckbox.setTexture(checkBoxTextures[recolorImage ? 1 : 0]);
				menuImageAutoAdjustValueCountCheckbox.setTexture(checkBoxTextures[revalueImage ? 1 : 0]); 
				menuDisplayTopImageMenuCheckbox.setTexture(
					checkBoxTextures[menuDisplayTopImageMenuCheckbox.isClickedOn ? 1 : 0]
				);
				menuDisplayMaintainSquarePixelsCheckbox.setTexture(
					checkBoxTextures[maintainSquarePixels ? 1 : 0]
				);

				const bool menuImageWidthSliderPrvsClickedOn = menuImageWidthSlider.isClickedOn; 
				const bool menuImageHeightSliderPrvsClickedOn = menuImageHeightSlider.isClickedOn;  

				menu.update(); 

				if (menuImageWidthSliderPrvsClickedOn && !menuImageWidthSlider.isClickedOn) {
					imageSize.x = 1 + menuImageWidthSlider.getPercentage(maxImageSize.x - 1);
					menuImageWidthTextbox.setStoredString(std::to_string(imageSize.x)); 
					if (resizeImage) updateFromSourceImage(); 
				}
				else if (menuImageHeightSliderPrvsClickedOn && !menuImageHeightSlider.isClickedOn) {
					imageSize.y = 1 + menuImageHeightSlider.getPercentage(maxImageSize.y - 1); 
					menuImageHeightTextbox.setStoredString(std::to_string(imageSize.y)); 
					if (resizeImage) updateFromSourceImage();
				}

				if (menuImageWidthTextbox.getStoredString() != std::to_string(imageSize.x)) {
					if (!menuImageWidthTextbox.getStoredString().empty()) {
						imageSize.x = std::stoi(menuImageWidthTextbox.getStoredString());
						gs::util::clamp(&imageSize.x, 1, maxImageSize.x); 
						imageID.size.x = imageSize.x; 
						menuImageWidthSlider.setPercentage(imageSize.x - 1, maxImageSize.x); 
						menuImageWidthTextbox.setStoredString(std::to_string(imageSize.x));
						if (resizeImage) updateFromSourceImage();
					}
				}
				else if (menuImageHeightTextbox.getStoredString() != std::to_string(imageSize.y)) {
					if (!menuImageHeightTextbox.getStoredString().empty()) {
						imageSize.y = std::stoi(menuImageHeightTextbox.getStoredString());
						gs::util::clamp(&imageSize.y, 1, maxImageSize.y);
						imageID.size.y = imageSize.y; 
						menuImageHeightSlider.setPercentage(imageSize.y - 1, maxImageSize.y);
						menuImageHeightTextbox.setStoredString(std::to_string(imageSize.y));
						if (resizeImage) updateFromSourceImage();
					}
				}

				if (menuImageChangeColorPaletteButton.isSelected
					&& menuImageChangeColorPaletteButton.isClickedOn)
				{
					image.colorPalette = static_cast<Image::ColorPalette>(
						(static_cast<int>(image.colorPalette) + 1)	
							% static_cast<int>(Image::ColorPalette::End));
					sourceImage.colorPalette = image.colorPalette; 
					imageID.paletteIndex = static_cast<int>(image.colorPalette); 
					menuImageColorPaletteText.setString(
						Image::colorPaletteStrings[static_cast<int>(image.colorPalette)]
					); 
					if (recolorImage) updateFromSourceImage(); 
				}
				else if (menuImageValueCountUpArrowButton.isSelected
					&& menuImageValueCountUpArrowButton.isClickedOn)
				{
					imageColorValues = std::min(imageColorValues + 1, 7); 
					menuImageValueCountTextbox.setStoredString(std::to_string(imageColorValues)); 
					if (revalueImage) updateFromSourceImage(); 
				}
				else if (menuImageValueCountDownArrowButton.isSelected
					&& menuImageValueCountDownArrowButton.isClickedOn)
				{
					imageColorValues = std::max(imageColorValues - 1, 1);
					menuImageValueCountTextbox.setStoredString(std::to_string(imageColorValues));
					if (revalueImage) updateFromSourceImage();
				}
				else if (menuImageGenerateButton.isSelected && menuImageGenerateButton.isClickedOn)
					updateFromSourceImage();
				else if (menuImageGenerateRandomButton.isSelected 
					&& menuImageGenerateRandomButton.isClickedOn) 
				{
					imageID = image.generateID(); 
					imageID.generateRandomID(); 
					image.createFromID(imageID); 
				}
				else if (menuExitButton.isSelected && menuExitButton.isClickedOn)
					window::winmain->close();

				resizeImage = menuImageAutoAdjustCheckbox.isClickedOn; 
				recolorImage = menuImageAutoAdjustColorCheckbox.isClickedOn; 
				revalueImage = menuImageAutoAdjustValueCountCheckbox.isClickedOn; 
				maintainSquarePixels = menuDisplayMaintainSquarePixelsCheckbox.isClickedOn; 
			}
			void renderMenu() {
				if (menu.getPosition().x < closedMenuHorizontalPosition - outlineThickness)
					window::winmain->draw(rightPanel);

				gs::draw(window::winmain, menu); 
			}
			void updateImageMenu() {
				auto loadFileFromFileExplorer = [](const wchar_t* title, const wchar_t* filters) 
					-> std::string
				{
					OPENFILENAME ofn = { 0 };
					wchar_t filename[MAX_PATH] = { 0 };

					ofn.lStructSize = sizeof(ofn);
					ofn.lpstrTitle = title;
					ofn.lpstrFilter = filters;
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFile = filename;
					ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

					GetOpenFileName(&ofn); 

					const std::wstring filenameW = std::wstring(ofn.lpstrFile);
					return std::string(filenameW.begin(), filenameW.end());
				}; 
				auto saveFileFromFileExplorer = [](const wchar_t* title, const wchar_t* filters) 
					-> std::string 
				{
					OPENFILENAME sfn = { 0 };
					wchar_t filename[MAX_PATH] = { 0 };

					sfn.lStructSize = sizeof(sfn); 
					sfn.lpstrTitle = title; 
					sfn.lpstrFilter = filters;
					sfn.nMaxFile = MAX_PATH; 
					sfn.lpstrFile = filename; 
					sfn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST; 

					GetSaveFileName(&sfn);

					const std::wstring filenameW = std::wstring(sfn.lpstrFile); 
					return std::string(filenameW.begin(), filenameW.end()); 
				}; 

				if (menu.getPosition().x > closedMenuHorizontalPosition - outlineThickness)
					return;

				imageSourceInfoText.setString(
					"Filename: " + sourceFilename + "\n"
					"Size: " + std::to_string(sourceImage.getSize().x) + "x" 
						+ std::to_string(sourceImage.getSize().y) + "\n"
				);
				menuImageInfoText.setString(
					"Save Filename: " + imageFilename + "\n" 
					"Size: " + std::to_string(image.getSize().x) + "x"
						+ std::to_string(image.getSize().y) + "\n"
				); 
				menuImageIDInfoText.setString(
					"Num Of Characters: " + std::to_string(imageID.toString().size()) + "\n"
					"Num Of Pixels: " + std::to_string(imageID.getValueCount()) + "\n"
				); 

				topImageMenu.setPosition(
					0.0f, (openMenuHorizontalPosition / imageRenderingAspectRatio / 2.0f)
						- (imageRenderingOutlineHeight / 2.0f)
				);
				bottomImageMenu.setPosition(
					0.0f, -(openMenuHorizontalPosition / imageRenderingAspectRatio / 2.0f)
						+ (imageRenderingOutlineHeight / 2.0f)
				);

				if (menuDisplayTopImageMenuCheckbox.isClickedOn)
					topImageMenu.update(); 

				bottomImageMenu.update(); 

				if (bottomButtons[0].isSelected && bottomButtons[0].isClickedOn) {
					std::string selectedFilename = loadFileFromFileExplorer(
						L"Select an Image", L"Image Files\0\0.png\0\0.jpg\0\0.bmp\0\0.tga\0\0"
					);

					if (!selectedFilename.empty()) {
						if (sourceImage.loadFromFile(selectedFilename)) {
							const int slashIndex = selectedFilename.find_last_of('\\'); 

							if (slashIndex != -1) 
								selectedFilename = selectedFilename.substr(slashIndex + 1); 
							
							sourceFilename = selectedFilename.substr(0, 16);
							updateFromSourceImage();
						}
					}
				}
				else if (bottomButtons[1].isSelected && bottomButtons[1].isClickedOn) {
					const std::string& selectedFilename = loadFileFromFileExplorer(
						L"Select a Text Document", L"Text Documents\0\0.txt\0\0"
					); 

					if (!selectedFilename.empty()) {
						imageID.loadFromFile(selectedFilename); 
						imageSize = imageID.size; 
						imageColorValues = imageID.getValuesPerSegment(); 
						image.colorPalette = static_cast<Image::ColorPalette>(imageID.paletteIndex);

						sourceImage.create(imageSize.x, imageSize.y); 
						sourceImage.colorValues = imageColorValues; 
						sourceImage.colorPalette = image.colorPalette; 
						sourceImage.createFromID(imageID); 
						updateFromSourceImage(); 

						menuImageWidthSlider.setPercentage(imageSize.x - 1, maxImageSize.x);
						menuImageWidthTextbox.setStoredString(std::to_string(imageSize.x));
						menuImageHeightSlider.setPercentage(imageSize.y - 1, maxImageSize.y);
						menuImageHeightTextbox.setStoredString(std::to_string(imageSize.y));
						menuImageValueCountTextbox.setStoredString(std::to_string(imageColorValues));
						menuImageColorPaletteText.setString(
							Image::colorPaletteStrings[static_cast<int>(image.colorPalette)]
						);
					}
				}
				else if (bottomButtons[2].isSelected && bottomButtons[2].isClickedOn) {
					std::string savedFilename = saveFileFromFileExplorer(
						L"Save Image", L"Image Files\0\0.png\0\0.jpg\0\0.bmp\0\0.tga\0\0"
					); 

					if (!savedFilename.empty()) {
						if (image.saveToFile(savedFilename)) {
							const int slashIndex = savedFilename.find_last_of('\\');

							if (slashIndex != -1)
								savedFilename = savedFilename.substr(slashIndex + 1);

							imageFilename = savedFilename.substr(0, 16); 
						}
					}
				}
				else if (bottomButtons[3].isSelected && bottomButtons[3].isClickedOn) {
					const std::string& savedFilename = saveFileFromFileExplorer(
						L"Save Text Document", L"Text Documents\0\0.txt\0\0"
					); 
					
					if (!savedFilename.empty())
						imageID.saveToFile(savedFilename); 
				}
			}
			void renderImageMenu() {
				if (menu.getPosition().x > closedMenuHorizontalPosition - outlineThickness)
					return; 

				if (menuDisplayTopImageMenuCheckbox.isClickedOn)
					gs::draw(window::winmain, topImageMenu); 

				gs::draw(window::winmain, bottomImageMenu); 
			}
		}
	}
}
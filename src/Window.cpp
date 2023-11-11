#include "../hdr/Window.hpp"

namespace engine {
	namespace render {
		namespace window {
			const gs::Vec2i defaultWindowSize = { 1920, 1080 };

			sf::RenderWindow* winmain = nullptr;
			bool isFullscreen = false;
			int eventFramerate = 60;
			int visualFramerate = 60;
			int eventTick = 0; 
			sf::Image icon;

			void create(bool fullscreen) {
				auto getStyle = []() -> decltype(sf::Style::None) {
					return isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;              
				};

				isFullscreen = fullscreen; 

				if (winmain == nullptr) {
					winmain = new sf::RenderWindow(
						sf::VideoMode(defaultWindowSize.x, defaultWindowSize.y),
						title, getStyle()
					); 
				}
				else {
					winmain->create(
						sf::VideoMode(defaultWindowSize.x, defaultWindowSize.y),
						title, getStyle()
					); 
				}

				initialize(); 
			}
			void initialize() {
				gs::input::setWindow(winmain); 

				const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode(); 
				const gs::Vec2u desktopModeSize = gs::Vec2u(desktopMode.width, desktopMode.height);

				if (winmain->getSize() != desktopModeSize) 
					winmain->setSize(desktopModeSize); 

				if (icon.getSize() == gs::Vec2u()) 
					icon.loadFromFile("assets/icon.png"); 

				winmain->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); 
			}
			void update() {
				gs::input::updateInputs(); 

				sf::Event event; 

				while (winmain->pollEvent(event)) {
					gs::input::updateEvents(event); 

					switch (event.type) {
					case sf::Event::Closed:
CloseWindow:
						winmain->close();
						break; 
					case sf::Event::KeyPressed:
						switch (event.key.code) {
						case sf::Keyboard::F11:
							create(!isFullscreen); 
							break; 
						}
						break; 
					}
				}

				eventTick++; 
			}
			void cleanUp() {
				delete winmain; 
			}

			void clear(gs::Color backgroundColor) {
				winmain->clear(backgroundColor); 
			}
			void display() {
				winmain->display(); 
			}
		}
	}
}
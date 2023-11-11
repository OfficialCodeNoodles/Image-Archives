#pragma once

// Dependencies
#include "ID.hpp"

namespace engine {
	class Image : public sf::Image {
	public:
		enum class ColorPalette { Grayscale, Color, End } colorPalette;
		int colorValues; 

		Image();
		~Image() = default; 

		void createFromID(ID& id); 
		ID generateID(gs::Vec2i size = gs::Vec2i(-1, -1)) const; 

		const sf::Texture& getTexture(); 

		static constexpr int maxColorValueCount = (1 << ID::maxValuesPerSegment);
		static const std::string colorPaletteStrings[static_cast<int>(ColorPalette::End)]; 
		static gs::Color colorPalettes[static_cast<int>(ColorPalette::End)]
			[ID::maxValuesPerSegment][maxColorValueCount];

		static void initColorPalettes(); 
	private:
		sf::Texture texture; 
		bool updateTexture; 

		ID::IntType convertColorToIDValue(gs::Color color) const; 
	};

	extern const gs::Vec2i maxImageSize; 

	extern Image sourceImage; 
	extern std::string sourceFilename; 
	extern Image image; 
	extern std::string imageFilename; 
	extern ID imageID;
	extern gs::Vec2i imageSize; 
	extern int imageColorValues;
	extern bool resizeImage; 
	extern bool recolorImage; 
	extern bool revalueImage; 

	gs::Color hsvToRgb(float h, float s, float v); 
	void updateFromSourceImage(); 
}
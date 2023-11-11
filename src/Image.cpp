#include "../hdr/Image.hpp"

namespace engine {
	Image::Image() : 
		sf::Image(),
		colorValues(8), 
		colorPalette(ColorPalette::Grayscale), 
		updateTexture(true)
	{
	}

	void Image::createFromID(ID& id) {
		int pixelIndex = 0; 

		colorValues = id.getValuesPerSegment();
		colorPalette = static_cast<ColorPalette>(id.paletteIndex); 

		for (int ypos = 0; ypos < getSize().y; ypos++) {
			for (int xpos = 0; xpos < getSize().x; xpos++) {
				if (pixelIndex >= id.getValueCount()) {
					updateTexture = true;
					return; 
				}

				const ID::IntType value = id[pixelIndex];

				setPixel(xpos, ypos, colorPalettes[static_cast<int>(colorPalette)]
					[(ID::Segment::segmentBits / id.getValuesPerSegment()) - 1][value]);
				pixelIndex++; 
			}
		} 

		updateTexture = true; 
	}
	ID Image::generateID(gs::Vec2i size) const {
		const int valueCount = size == gs::Vec2i(-1, -1)
			? getSize().x * getSize().y : size.x * size.y;
		const gs::Vec2f scalar = gs::Vec2f(
			getSize().x / static_cast<float>(size.x),
			getSize().y / static_cast<float>(size.y)
		);

		ID generatedID(valueCount, imageColorValues);
		int pixelIndex = 0; 

		for (int ypos = 0; ypos < size.y; ypos++) {
			for (int xpos = 0; xpos < size.x; xpos++) {
				const gs::Vec2u scaledPosition = gs::Vec2u(xpos * scalar.x, ypos * scalar.y); 
				const gs::Color pixelColor = getPixel(scaledPosition.x, scaledPosition.y);
				const ID::IntType pixelIDValue = convertColorToIDValue(pixelColor); 

				generatedID.setValue(pixelIndex, pixelIDValue);
				pixelIndex++; 
			}
		}

		generatedID.size = size; 
		generatedID.paletteIndex = static_cast<int>(colorPalette); 

		return generatedID; 
	}

	const sf::Texture& Image::getTexture() {
		if (updateTexture) {
			texture.loadFromImage(*this);
			updateTexture = false;
		}

		return texture; 
	}

	const std::string Image::colorPaletteStrings[static_cast<int>(ColorPalette::End)] = {
		"Gray Scale", "Color"
	};
	gs::Color Image::colorPalettes[static_cast<int>(Image::ColorPalette::End)]
		[ID::maxValuesPerSegment][maxColorValueCount]; 

	void Image::initColorPalettes() {
		for (int colorPalette = 0; colorPalette < static_cast<int>(ColorPalette::End); 
			colorPalette++)
		{
			for (int expIndex = 0; expIndex < ID::maxValuesPerSegment; expIndex++) {
				const int colorValueCount = std::pow(2, expIndex + 1); 

				for (int colorIndex = 0; colorIndex < colorValueCount; colorIndex++) {
					gs::Color& color = colorPalettes[colorPalette][expIndex][colorIndex]; 

					switch (static_cast<ColorPalette>(colorPalette)) {
					case ColorPalette::Grayscale: 
					{
						const float colorScalar = 255.0f / static_cast<float>(colorValueCount);
						const sf::Uint8 colorComponent = colorIndex * colorScalar;

						color = gs::Color(colorComponent, colorComponent, colorComponent); 
					}
						break;
					case ColorPalette::Color:
					{
						const int numOfShades = expIndex < ID::maxValuesPerSegment - 1 ? 4 : 50; 
						const int numOfTints = expIndex < ID::maxValuesPerSegment - 1 ? 3 : 20; 
						const float angularScaler = 360.0f / colorValueCount;
						const float hue = colorIndex * angularScaler; 
						const int modValue = colorIndex % (1 + numOfShades + numOfTints); 

						if (modValue == 0)
							color = hsvToRgb(hue, 100.0f, 100.0f);
						else if (modValue < 1 + numOfShades) 
							color = hsvToRgb(hue, 100.0f, modValue * (100.0f / (numOfShades + 1))); 
						else 
							color = hsvToRgb(hue, (modValue - numOfShades) 
								* (100.0f / (numOfTints + 1)), 100.0f); 
					}
						break; 
					}
				}
			}
		}
	}

	ID::IntType Image::convertColorToIDValue(gs::Color color) const {
		const int paletteIndex = (ID::Segment::segmentBits / colorValues) - 1; 
		const int colorValueCount = std::pow(2, paletteIndex + 1) - 1; 
		
		auto locateNearestColorValue = [&](gs::Color color) -> ID::IntType {
			auto calculateComponentDelta = [](sf::Uint8 value1, sf::Uint8 value2) -> int {
				return std::abs(static_cast<int>(value1) - static_cast<int>(value2)); 
			}; 

			ID::IntType bestMatch = 0; 
			int lowestDelta = UINT16_MAX * 3;
			int colorIndex = 0; 

			do {
				const gs::Color currentColor = colorPalettes[static_cast<int>(colorPalette)]
					[paletteIndex][colorIndex]; 
				const int delta = calculateComponentDelta(currentColor.r, color.r)
					+ calculateComponentDelta(currentColor.g, color.g)
					+ calculateComponentDelta(currentColor.b, color.b);
				
				if (delta < lowestDelta) {
					lowestDelta = delta; 
					bestMatch = colorIndex; 
				}

				colorIndex++; 
			} 
			while (colorIndex < colorValueCount); 
	
			return bestMatch; 
		};

		switch (colorPalette) {
		case ColorPalette::Grayscale:
			return (((0.299f * color.r) + (0.587f * color.g) + (0.114f * color.b)))
				/ (255.0f / static_cast<float>(colorValueCount));
		case ColorPalette::Color:
			return locateNearestColorValue(color); 
		}

		return 0; 
	}

	const gs::Vec2i maxImageSize = gs::Vec2i(1280, 720);

	Image sourceImage;
	std::string sourceFilename; 
	Image image;
	std::string imageFilename;
	ID imageID;
	gs::Vec2i imageSize = gs::Vec2i(320, 180);
	int imageColorValues = 2; 
	bool resizeImage = true;
	bool recolorImage = true; 
	bool revalueImage = true; 

	gs::Color hsvToRgb(float h, float s, float v) {
		// This function is inspired by this website page. 
		// https://www.codespeedy.com/hsv-to-rgb-in-cpp/

		gs::Color color;

		h = gs::util::mod(h, 360.0f);

		s /= 100.0f;
		v /= 100.0f;

		float C = s * v;
		float X = C * (1.0f - std::abs(std::fmod(h / 60.0, 2.0f) - 1.0f));
		float m = v - C;
		float r, g, b;

		if (h >= 0.0f && h < 60.0f)
			r = C, g = X, b = 0.0f;
		else if (h >= 60.0f && h < 120.0f)
			r = X, g = C, b = 0.0f;
		else if (h >= 120.0f && h < 180.0f)
			r = 0, g = C, b = X;
		else if (h >= 180.0f && h < 240.0f)
			r = 0, g = X, b = C;
		else if (h >= 240 && h < 300.0f)
			r = X, g = 0.0f, b = C;
		else
			r = C, g = 0.0f, b = X;

		color.r = (r + m) * 255;
		color.g = (g + m) * 255;
		color.b = (b + m) * 255;

		return color;
	}
	void updateFromSourceImage() {
		sourceImage.colorValues = imageColorValues; 
		imageID = sourceImage.generateID(imageSize); 
		
		if (image.getSize() != gs::Vec2u(imageSize)) 
			image.create(imageSize.x, imageSize.y); 

		image.colorValues = imageColorValues; 
		image.createFromID(imageID); 
	}
}
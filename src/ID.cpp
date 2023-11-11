#include "../hdr/ID.hpp"

namespace engine {
	ID::Segment::Segment() : value(0) {
	}

	void ID::Segment::setSubValue(int bitOffset, int valueBits, IntType value) {
		const IntType mask = std::pow(2, bitOffset + valueBits) - std::pow(2, bitOffset);

		this->value &= static_cast<IntType>(std::pow(2, segmentBits) - 1) - mask;
		this->value |= (value << bitOffset); 
	}

	ID::IntType ID::Segment::getSubValue(int bitOffset, int valueBits) const {
		IntType parsedInteger = value;

		const IntType mask = std::pow(2, bitOffset + valueBits) - 1; 
		parsedInteger &= mask; 
		parsedInteger >>= bitOffset; 

		return parsedInteger;
	}

	ID::ID() : paletteIndex(0), valueCount(0), valuesPerSegment(2), updateString(true) {
	}
	ID::ID(int valuesPerSegment) : ID() {
		this->valuesPerSegment = valuesPerSegment; 
	}
	ID::ID(int valueCount, int valuesPerSegment) : ID() {
		segments.resize(1 + valueCount / valuesPerSegment); 
		this->valueCount = valueCount; 
		this->valuesPerSegment = valuesPerSegment; 
	}

	int ID::getSegmentCount() const {
		return segments.size();
	}
	ID::IntType ID::getSegmentValue(int index) const {
		return segments[index].value; 
	}
	int ID::getValueCount() const {
		return valueCount; 
	}
	int ID::getValuesPerSegment() const {
		return valuesPerSegment; 
	}

	void ID::loadFromFile(const std::string& filename) {
		std::wifstream ifile(filename); 
		ifile.imbue(std::locale(charEncoding)); 
		
		std::wstring string; 
		std::wstring nextLine; 

		while (std::getline(ifile, nextLine))
			string += nextLine; 
		
		ifile.close();
		setFromString(string); 
		updateString = true; 
	}
	void ID::saveToFile(const std::string& filename) const {
		std::wofstream ofile(filename); 
		ofile.imbue(std::locale(charEncoding));
		std::wcout.imbue(std::locale(charEncoding)); 

		ofile << toString(); 
		ofile.close(); 
	}
	void ID::generateRandomID() {
		std::random_device rdev; 
		std::mt19937 rng(rdev()); 
		std::uniform_int_distribution<std::mt19937::result_type> 
			dist(0, std::pow(2, Segment::segmentBits) - 1); 

		for (Segment& segment : segments) 
			segment.value = dist(rng); 
	}

	void ID::setValue(int index, IntType value) {
		const int segmentIndex = getSegmentIndex(index);
		const int valueBits = Segment::segmentBits / valuesPerSegment;

		segments[segmentIndex].setSubValue(
			(index % valuesPerSegment) * valueBits,
			valueBits, value
		); 
		updateString = true; 
	}
	void ID::setFromString(const std::wstring& string) {
		size.x = static_cast<int>(string[0]) - Segment::validLowerBound;
		size.y = static_cast<int>(string[1]) - Segment::validLowerBound;
		valuesPerSegment = static_cast<int>(string[2]) - Segment::validLowerBound;
		paletteIndex = static_cast<int>(string[3]) - Segment::validLowerBound; 

		segments.resize(string.size() - 4); 
		valueCount = segments.size() * valuesPerSegment; 

		for (int charIndex = 0; charIndex < string.size() - 4; charIndex++) {
			const wchar_t chr = string[charIndex + 4]; 
			segments[charIndex].value = static_cast<IntType>(chr) - Segment::validLowerBound;
		}

		updateString = true; 
	}

	const std::wstring& ID::toString() const {
		static std::wstring stringRepresentation; 

		if (updateString) {
			stringRepresentation.clear();

			stringRepresentation += static_cast<wchar_t>(size.x + Segment::validLowerBound); 
			stringRepresentation += static_cast<wchar_t>(size.y + Segment::validLowerBound); 
			stringRepresentation += static_cast<wchar_t>(
				valuesPerSegment + Segment::validLowerBound
			); 
			stringRepresentation += static_cast<wchar_t>(paletteIndex + Segment::validLowerBound); 

			for (int segmentIndex = 0; segmentIndex < segments.size(); segmentIndex++) {
				const Segment& segment = segments[segmentIndex];
				stringRepresentation += static_cast<wchar_t>(
					segment.value + Segment::validLowerBound
				);
			}

			updateString = false;	 
		}

		return stringRepresentation; 
	}

	ID::IntType ID::operator[](int index) {
		const int segmentIndex = getSegmentIndex(index); 
		const int valueBits = Segment::segmentBits / valuesPerSegment; 
		return segments[segmentIndex].getSubValue(
			(index % valuesPerSegment) * valueBits,
			valueBits
		); 
	}

	int ID::getSegmentIndex(int valueIndex) {
		return valueIndex / valuesPerSegment; 
	}
}
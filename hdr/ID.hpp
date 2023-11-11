#pragma once

// Dependencies
#include "Include.hpp"

namespace engine {
	class ID {
	public:
		using IntType = uint16_t; 

		struct Segment {
			IntType value; 

			Segment(); 
			~Segment() = default; 

			void setSubValue(int bitOffset, int valueBits, IntType value); 

			IntType getSubValue(int bitOffset, int valueBits) const;
			
			static constexpr int segmentBits = (sizeof(IntType) * 8) - 1;
			static constexpr int validLowerBound = static_cast<int>(' '); 
		};

		gs::Vec2i size; 
		int paletteIndex; 

		ID(); 
		ID(int valuesPerSegment); 
		ID(int valueCount, int valuesPerSegment); 
		~ID() = default;

		void loadFromFile(const std::string& filename); 
		void saveToFile(const std::string& filename) const; 
		void generateRandomID(); 

		void setValue(int index, IntType value); 
		void setFromString(const std::wstring& string); 

		int getSegmentCount() const;
		IntType getSegmentValue(int index) const; 
		int getValueCount() const; 
		int getValuesPerSegment() const; 
		
		const std::wstring& toString() const; 

		IntType operator[](int index); 

		static constexpr int maxValuesPerSegment = Segment::segmentBits; 
		static constexpr const char* charEncoding = "en_US.UTF8"; 
	private:
		std::vector<Segment> segments; 
		int valueCount; 
		int valuesPerSegment; 
		mutable bool updateString; 

		int getSegmentIndex(int valueIndex); 
	};
}
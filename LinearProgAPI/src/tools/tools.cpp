/*
 * Tools.cpp
 *
 *  Created on: 26 juin 2014
 *      Author: valentin
 */

#include "tools.h"

namespace tool {
	std::string
	charToString(const char iString) {
		return std::string(sizeof(char), iString);
	}

	unsigned int
	stringToInteger(const std::string iString) {
		unsigned int lResult;
		std::istringstream lConvert(iString);
		lConvert >> lResult;
		return lResult;
	}

	std::string
	integerToString(const int iInteger) {
		std::stringstream lResult;
		lResult << iInteger;
		return lResult.str();
	}

	tyr::vector_string_type
	splitLine(const std::string iLine) {
		  std::istringstream lStringSteam(iLine);
		  tyr::stream_string_type lFirst(lStringSteam);
		  tyr::stream_string_type lLast;
		  return tyr::vector_string_type (lFirst, lLast);
	}

	double
	euclidianDistance(double iXa, double iYa, double iXb, double iYb) {
		return sqrt(pow(iXb - iXa, 2) + pow(iYb - iYa, 2));
	}
}

/*
 * Tools.h
 *
 *  Created on: 26 juin 2014
 *      Author: valentin
 */

#ifndef TOOLS_H_
# define TOOLS_H_

# include "../header/all.h"

namespace tool {
		/**
		 * Minimal element between two arguments
		 */
		template <typename Type>
		static Type min(const Type iA, const Type iB);

		/**
		 * Minimal element between three arguments
		 */
		template <typename Type>
		static Type min(const Type iA, const Type iB, const Type iC);

		/**
		 * Minimal element between four arguments
		 */
		template <typename Type>
		static Type min(const Type iA, const Type iB, const Type iC, const Type iD);

		/**
		 * Maximal element between two arguments
		 */
		template <typename Type>
		static Type max(const Type iA, const Type iB);

		/**
		 * Maximal element between three arguments
		 */
		template <typename Type>
		static Type max(const Type iA, const Type iB, const Type iC);

		/**
		 * Maximal element between four arguments
		 */
		template <typename Type>
		static Type max(const Type iA, const Type iB, const Type iC, const Type iD);

		/**
		 * Build a new array with all the elements
		 * from the input array
		 */
		template <typename Type>
		static Type* arrayBuilder(const Type* iSrcArray, uint8_t iSize);

		/**
		 * Char to String conversion
		 */
		std::string charToString(const char iString);

		/**
		 * String to unsigned integer conversion
		 */
		unsigned int stringToInteger(const std::string iString);

		/**
		 * Integer to String conversion
		 */
		std::string integerToString(const int iInteger);

		/**
		 * Split a string input a string vector
		 * that contain separate words by " "
		 */
		tyr::vector_string_type splitLine(const std::string iLine);

		/**
		 * Calculus the distance between two points
		 */
		double euclidianDistance(double iXa, double iYa, double iXb, double iYb);

		/**
		 * Big M
		 */
		static const unsigned int sBigM = UINT_MAX;
}

# include "tools.hxx"

#endif /* TOOLS_H_ */

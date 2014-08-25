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
		 * \brief Minimal element between two arguments
		 * \param iA the first element
		 * \param iB the second element
		 */
		template <typename Type>
		static Type min(const Type iA, const Type iB);

		/**
		 * \brief Minimal element between three arguments
		 * \param iA the first element
		 * \param iB the second element
		 * \param iC the third element
		 */
		template <typename Type>
		static Type min(const Type iA, const Type iB, const Type iC);

		/**
		 * \brief Minimal element between four arguments
		 * \param iA the first element
		 * \param iB the second element
		 * \param iC the third element
		 * \param iD the fourth element
		 */
		template <typename Type>
		static Type min(const Type iA, const Type iB, const Type iC, const Type iD);

		/**
		 * \brief Maximal element between four arguments
		 * \param iA the first element
		 * \param iB the second element
		 * \param iC the third element
		 * \param iD the fourth element
		 */
		template <typename Type>
		static Type max(const Type iA, const Type iB);

		/**
		 * \brief Maximal element between four arguments
		 * \param iA the first element
		 * \param iB the second element
		 * \param iC the third element
		 * \param iD the fourth element
		 */
		template <typename Type>
		static Type max(const Type iA, const Type iB, const Type iC);

		/**
		 * \brief Maximal element between four arguments
		 * \param iA the first element
		 * \param iB the second element
		 * \param iC the third element
		 * \param iD the fourth element
		 */
		template <typename Type>
		static Type max(const Type iA, const Type iB, const Type iC, const Type iD);

		/**
		 * \biref Build a new array with all the elements
		 * from the input array
		 * \param iSrcArray the original array
		 * \param iSize the size of the input array
		 */
		template <typename Type>
		static Type* arrayBuilder(const Type* iSrcArray, uint8_t iSize);

		/**
		 * \brief Char to String conversion
		 * \param iChar the char to convert
		 */
		std::string charToString(const char iString);

		/**
		 * \brief String to unsigned integer conversion
		 * \param iString the string to convert
		 */
		unsigned int stringToInteger(const std::string iString);

		/**
		 * \brief Integer to String conversion
		 * \param iInteger the integer to convert
		 */
		std::string integerToString(const int iInteger);

		/**
		 * \brief Split a string input a string vector
		 * that contain separate words by " "
		 * \param iLine the string to split
		 */
		tyr::vector_string_type splitLine(const std::string iLine);

		/**
		 * \brief Calculus the distance between two points
		 * \param iXa the first X coordinate
		 * \param iYa the first Y coordinate
		 * \param iXb the second X coordinate
		 * \param iYb the second Y coordinate
		 */
		double euclidianDistance(double iXa, double iYa, double iXb, double iYb);
}

# include "tools.hxx"

#endif /* TOOLS_H_ */

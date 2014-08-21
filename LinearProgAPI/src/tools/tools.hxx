/*
 * Tools.hxx
 *
 *  Created on: 26 juin 2014
 *      Author: valentin
 */

namespace tool {
	template <typename Type>
	Type*
	arrayBuilder(const Type* iSrcArray, uint8_t iSize) {
		Type* lNewArray = new Type[iSize];
		for (uint8_t i = 0; i < iSize; i++) {
			lNewArray[i] = iSrcArray[i];
		}
		return lNewArray;
	}

	template <typename Type>
	Type
	min(const Type iA, const Type iB) {
		return (iA < iB ? iA : iB);
	}

	template <typename Type>
	Type
	min(const Type iA, const Type iB, const Type iC) {
		return (iA < iB ? min(iA, iC) : min(iB, iC));
	}

	template <typename Type>
	Type
	min(const Type iA, const Type iB, const Type iC, const Type iD) {
		return (iA < iB ? min(iA, iC, iD) : min(iB, iC, iD));
	}

	template <typename Type>
	Type
	max(const Type iA, const Type iB) {
		return (iA > iB ? iA : iB);
	}

	template <typename Type>
	Type
	max(const Type iA, const Type iB, const Type iC) {
		return (iA > iB ? max(iA, iC) : max(iB, iC));
	}

	template <typename Type>
	Type
	max(const Type iA, const Type iB, const Type iC, const Type iD) {
		return (iA > iB ? max(iA, iC, iD) : max(iB, iC, iD));
	}
}

/*
 * variable.hxx
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

inline std::string
Variable::getName() {
	return mName;
}

inline void
Variable::setLowerLimit(int iLowerLimit) {
	assert(iLowerLimit >= 0);
	assert((mIsBinary && iLowerLimit == 0) || !mIsBinary);
	mLowerLimit = iLowerLimit;
}

inline void
Variable::setUpperLimit(int iUpperLimit) {
	assert(iUpperLimit >= 0);
	assert((mIsBinary && iUpperLimit == 1) || !mIsBinary);
	mUpperLimit = iUpperLimit;
}

inline void
Variable::setLimits(int iLowerLimit, int iUpperLimit) {
	assert(iLowerLimit >= 0 && iUpperLimit >= 0);
	assert(iLowerLimit <= iUpperLimit);
	assert((mIsBinary && iLowerLimit == 0) || !mIsBinary);
	assert((mIsBinary && iUpperLimit == 1) || !mIsBinary);
	mLowerLimit = iLowerLimit;
	mUpperLimit = iUpperLimit;
}

inline int
Variable::getLowerLimit() {
	return mLowerLimit;
}

inline int
Variable::getUpperLimit() {
	return mUpperLimit;
}

inline bool
Variable::isBinary() {
	return mIsBinary;
}

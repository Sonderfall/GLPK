/*
 * constraint.hxx
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

inline void
Constraint::addVariableInConstraint(double iCoefficient, Variable iVariable) {
	mVariables.push_back(std::make_pair(iCoefficient, iVariable));
}

inline void
Constraint::addConstantInConstraint(double iConstant) {
	mConstants.push_back(iConstant);
}

inline void
Constraint::setLowerLimit(int iLowerLimit) {
	mLowerLimit = iLowerLimit;
}

inline void
Constraint::setUpperLimit(int iUpperLimit) {
	mUpperLimit = iUpperLimit;
}

inline void
Constraint::setLimits(int iLowerLimit, int iUpperLimit) {
	assert(iLowerLimit <= iUpperLimit);
	mLowerLimit = iLowerLimit;
	mUpperLimit = iUpperLimit;
}

inline int
Constraint::getLowerLimit() {
	return mLowerLimit;
}

inline int
Constraint::getUpperLimit() {
	return mUpperLimit;
}

inline std::vector<double>
Constraint::getConstants() {
	return mConstants;
}

inline std::vector<std::pair<double, Variable>>
Constraint::getVariables() {
	return mVariables;
}

inline std::string
Constraint::getName() {
	return mName;
}

inline void
Constraint::operator()(double iConstant) {
	mConstants.push_back(iConstant);
}

inline void
Constraint::operator()(double iCoefficient, Variable iVariable) {
	mVariables.push_back(std::make_pair(iCoefficient, iVariable));
}

inline void
Constraint::operator()(Variable iVariable) {
	mVariables.push_back(std::make_pair(1, iVariable));
}

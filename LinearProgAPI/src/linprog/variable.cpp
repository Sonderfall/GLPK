/*
 * variable.cpp
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

# include "variable.h"

Variable::Variable()
	: mName ("UnNamed Variable")
	, mIsBinary (false)
	, mLowerLimit (0)
	, mUpperLimit (pInf) {}

Variable::Variable(std::string iName)
	: mName (iName)
	, mIsBinary (false)
	, mLowerLimit (0)
	, mUpperLimit (pInf) {}

Variable::Variable(std::string iName, bool iIsBinary)
	: mName (iName)
	, mIsBinary (iIsBinary)
	, mLowerLimit (0)
	, mUpperLimit (iIsBinary ? 1 : pInf) {}

Variable::Variable(bool iIsBinary)
	: mName ("UnNamed Variable")
	, mIsBinary (iIsBinary)
	, mLowerLimit (0)
	, mUpperLimit (iIsBinary ? 1 : pInf) {}

Variable::Variable(const Variable& iVariable)
	: mName (iVariable.mName)
	, mIsBinary (iVariable.mIsBinary)
	, mLowerLimit (iVariable.mLowerLimit)
	, mUpperLimit (iVariable.mUpperLimit) {}

Variable::~Variable() {}

bool
Variable::operator<(const Variable iRightVariable) const {
	return true;
}

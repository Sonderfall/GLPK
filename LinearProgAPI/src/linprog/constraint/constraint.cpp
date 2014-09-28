/*
 * constraint.cpp
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

#include "constraint.h"

Constraint::Constraint()
	: mName ("UnNamed Constraint")
	, mLowerLimit (MINF)
	, mUpperLimit (PINF) {}

Constraint::Constraint(std::string iName)
	: mName (iName)
	, mLowerLimit (MINF)
	, mUpperLimit (PINF) {}

Constraint::Constraint(const Constraint& iConstraint)
	: mName (iConstraint.mName)
	, mLowerLimit (iConstraint.mLowerLimit)
	, mUpperLimit (iConstraint.mUpperLimit)
	, mConstants (iConstraint.mConstants)
	, mVariables (iConstraint.mVariables) {}

Constraint::~Constraint() {}


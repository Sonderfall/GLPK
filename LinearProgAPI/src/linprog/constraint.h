/*
 * constraint.h
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

#ifndef CONSTRAINT_H_
# define CONSTRAINT_H_

# include "../header/all.h"
# include "variable.h"

class Constraint {
public:
	Constraint();
	Constraint(std::string iName);
	Constraint(const Constraint& iConstraint);
	virtual ~Constraint();

public:
	void addVariableInConstraint(double iCoefficient, Variable iVariable);
	void addConstantInConstraint(double iConstant);
	void setLowerLimit(int iLowerLimit);
	void setUpperLimit(int iUpperLimit);
	void setLimits(int iLowerLimit, int iUpperLimit);

	std::string getName();
	int getLowerLimit();
	int getUpperLimit();
	std::vector<double> getConstants();
	std::vector<std::pair<double, Variable>> getVariables();

private:
	std::string mName;
	int mLowerLimit;
	int mUpperLimit;
	std::vector<double> mConstants;
	std::vector<std::pair<double, Variable>> mVariables;
};

# include "constraint.hxx"

#endif /* CONSTRAINT_H_ */

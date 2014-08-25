/*
 * variable.h
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

#ifndef VARIABLE_H_
# define VARIABLE_H_

# include "../header/all.h"

class Variable {
public:
	Variable(std::string iName);
	Variable(std::string iName, bool iIsBinary);
	Variable(const Variable& iVariable);
	virtual ~Variable();

public:
	void setLowerLimit(int iLowerLimit);
	void setUpperLimit(int iUpperLimit);
	void setLimits(int iLowerLimit, int iUpperLimit);

	std::string getName();
	int getLowerLimit();
	int getUpperLimit();
	bool isBinary();

	bool operator<(const Variable iRightVariable) const;

private:
	std::string mName;
	bool mIsBinary;
	int mLowerLimit;
	int mUpperLimit;
};

# include "variable.hxx"

#endif /* VARIABLE_H_ */

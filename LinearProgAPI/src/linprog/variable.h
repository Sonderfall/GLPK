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
	/**
	 * Constructor
	 * \param iName the name of the variable
	 */
	Variable(std::string iName);

	/**
	 * Constructor
	 * \param iName the name of the variable
	 * \param iIsBinary set if the it's a binary variable
	 */
	Variable(std::string iName, bool iIsBinary);

	/**
	 * Constructor
	 * \param iVariable a variable to copy
	 */
	Variable(const Variable& iVariable);

	/**
	 * Destructor
	 */
	virtual ~Variable();

public:
	/**
	 * \brief Set the lower bound of the variable
	 * By default set to 0
	 * \param iLowerLimit the new lower bound of the variable
	 */
	void setLowerLimit(int iLowerLimit);

	/**
	 * \brief Set the upper bound of the variable
	 * By default set to +infinity
	 * \param iUpperLimit the new upper bound of the variable
	 */
	void setUpperLimit(int iUpperLimit);

	/**
	 * \brief Set the both lower and upper bounds of the variable
	 * By default set to 0 and +infinity
	 * \param iLowerLimit the new lower bound of the variable
	 * \param iUpperLimit the new upper bound of the variable
	 */
	void setLimits(int iLowerLimit, int iUpperLimit);

	/**
	 * Getters
	 */
	std::string getName();
	int getLowerLimit();
	int getUpperLimit();
	bool isBinary();

	bool operator<(const Variable iRightVariable) const;

private:
	/**
	 * \brief The name of the variable
	 */
	std::string mName;

	/**
	 * \brief Describe if it's a binary variable
	 * True : it's a binary variable
	 * False : it's not a binary viriable
	 */
	bool mIsBinary;

	/**
	 * \brief The lower bound of the variable
	 * By default set to 0
	 */
	int mLowerLimit;

	/**
	 * \brief The upper bound of the variable
	 * By default set to +infinity
	 */
	int mUpperLimit;
};

# include "variable.hxx"

#endif /* VARIABLE_H_ */

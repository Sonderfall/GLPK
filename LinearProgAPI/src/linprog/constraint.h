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
	/**
	 * Constructor
	 */
	Constraint();

	/**
	 * Constructor
	 * \param iName the name of the constraint
	 */
	Constraint(std::string iName);

	/**
	 * Constructor
	 * \param iConstraint a constraint to copy
	 */
	Constraint(const Constraint& iConstraint);

	/**
	 * Destructor
	 */
	virtual ~Constraint();

public:
	/**
	 * \brief Add a new variable to the constraint
	 * By default it's an addition
	 * If you are expecting a subtraction, specify a negative Coefficient
	 * \param iCoefficient the coefficient of the variable
	 * \param iVariable the variable to add
	 */
	void addVariableInConstraint(double iCoefficient, Variable iVariable);

	/**
	 * \brief Add a new constant to the constraint
	 * By default it's an addition
	 * If you are expecting a subtraction, specify a negative constant
	 * \param iConstant the constant to add
	 */
	void addConstantInConstraint(double iConstant);

	/**
	 * \brief Set the lower bound of the constraint
	 * By default set to -infinty
	 * \param iLowerLimit the new lower bound of the constraint
	 */
	void setLowerLimit(int iLowerLimit);

	/**
	 * \brief Set the upper bound of the constraint
	 * By default set to +infinity
	 * \param iUpperLimit the new upper bound of the constraint
	 */
	void setUpperLimit(int iUpperLimit);

	/**
	 * \brief Set the both lower and upper bounds of the constraint
	 * By default set to -infinity and +infinity
	 * \param iLowerLimit the new lower bound of the constraint
	 * \param iUpperLimit the new upper bound of the constraint
	 */
	void setLimits(int iLowerLimit, int iUpperLimit);

	/**
	 * \brief Function Operator
	 * \brief Add a new constant to the constraint
	 * By default it's an addition
	 * If you are expecting a subtraction, specify a negative constant
	 * \param iConstant the constant to add
	 */
	void operator()(double iConstant);

	/**
	 * \brief Function Operator
	 * \brief Add a new variable to the constraint
	 * By default it's an addition
	 * If you are expecting a subtraction, specify a negative Coefficient
	 * \param iCoefficient the coefficient of the variable
	 * \param iVariable the variable to add
	 */
	void operator()(double iCoefficient, Variable iVariable);

	/**
	 * \brief Function Operator
	 * \brief Add a new variable to the constraint
	 * By default it's an addition
	 * If you are expecting a subtraction, specify a negative Coefficient
	 * \param iVariable the variable to add
	 */
	void operator()(Variable iVariable);

	/**
	 * Getters
	 */
	std::string getName();
	int getLowerLimit();
	int getUpperLimit();
	std::vector<double> getConstants();
	std::vector<std::pair<double, Variable>> getVariables();

private:
	/**
	 * \brief The name of the constraint
	 */
	std::string mName;

	/**
	 * \brief The lower bound of the constraint
	 * By default set to -infinty
	 */
	int mLowerLimit;

	/**
	 * \brief The upper bound of the constraint
	 * By default set to +infinity
	 */
	int mUpperLimit;

	/**
	 * \brief All constants of the constraint
	 */
	std::vector<double> mConstants;

	/**
	 * \brief All variables of the constraint
	 */
	std::vector<std::pair<double, Variable>> mVariables;
};

# include "constraint.hxx"

#endif /* CONSTRAINT_H_ */

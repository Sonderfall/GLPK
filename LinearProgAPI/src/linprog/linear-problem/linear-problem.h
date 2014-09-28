/*
 * linear-problem.h
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

#ifndef LINEAR_PROBLEM_H_
# define LINEAR_PROBLEM_H_

# include "../../header/all.h"
# include "../../tools/tools.h"
# include "../variable/variable.h"
# include "../constraint/constraint.h"

/**
 * \enum ProblemObjective
 */
enum ProblemObjective {
	min,
	max
};

/**
 * \enum ProblemKind
 */
enum ProblemKind {
	lp,
	ilp
};

class LinearProblem {
public:
	/**
	 * Constructor
	 * \brief Set as a classic linear problem (non integer variable)
	 * \param iName the name of the problem
	 * \param iObj the objective of the problem [min, max]
	 */
	LinearProblem(std::string iName, ProblemObjective iObj);

	/**
	 * Constructor
	 * \param iName the name of the problem
	 * \param iObj the objective of the problem [min, max]
	 * \param iKind specify the kind of the problem [pl, plne]
	 */
	LinearProblem(std::string iName, ProblemObjective iObj, ProblemKind iKind);

	/**
	 * Destructor
	 * \brief Free and delete the problem
	 */
	virtual ~LinearProblem();

public:
	/**
	 * \brief Solve the current linear problem
	 * Final call after all variable and constraint settings
	 */
	void solve();

	/**
	 * \brief Print on the standart output all variable (with value)
	 * and the objective value
	 */
	void printResults();

public:
	/**
	 * \brief Add a new constraint to the problem
	 * \param iConstraint the constraint to add
	 */
	void addConstraint(Constraint iConstraint);

	/**
	 * \brief Add a new Variable in the objective function
	 * \param iCoefficient the coefficient of the variable
	 * \param iVariable the variable to add
	 */
	void addVariableInObjectiveFunction(double iCoefficient, Variable iVariable);


	/**
	 * \brief Function Operator
	 * \brief Add a new constraint to the problem
	 * \param iConstraint the constraint to add
	 */
	LinearProblem& operator()(Constraint iConstraint);

	/**
	 * \brief Function Operator
	 * \brief Add a new Variable in the objective function
	 * \param iCoefficient the coefficient of the variable
	 * \param iVariable the variable to add
	 */
	LinearProblem& operator()(double iCoefficient, Variable iVariable);

	/**
	 * \brief Function Operator
	 * \brief Add a new Variable in the objective function
	 * \param iVariable the variable to add
	 */
	LinearProblem& operator()(Variable iVariable);

	/**
	 * Getters
	 */
	std::vector<Constraint> getConstraints();
	std::vector<std::pair<double, Variable>> getObjectiveFunctionVariables();
	std::map<std::string, double> getResults();

private:
	/**
	 * \brief Init all basic settings of the linear problem
	 */
	void initLinearProblem();

	/**
	 * \brief Init all variables set in the objective function
	 */
	void processObjectiveFunction();

	/**
	 * \brief Init all constraints add in the linear problem
	 */
	void processConstraints();

	/**
	 * \brief Add constraint in problem
	 */
	void processConstraintsAdd();

	/**
	 * \brief Add variables and constant in each constraint in the
	 * linear problem
	 */
	void processConstraintsVarAndConstant();

	/**
	 * \brief Process the resolution of the linear problem
	 */
	void processSimplex();

private:
	/**
	 * \brief GLPK linear problem
	 */
	glp_prob* mLinearProb;

	/**
	 * \brief The name of the linear problem
	 */
	std::string mName;

	/**
	 * \brief The kind of the problem
	 * Can be a classic linear problem
	 * or an integer linear problem
	 */
	ProblemKind mProblemKind;

	/**
	 * \brief The objective of the problem
	 * Can be a maximization or a
	 * minimization
	 */
	ProblemObjective mProblemObjective;

	/**
	 * \brief Variables of the objective function
	 */
	std::vector<std::pair<double, Variable>> mObjectiveFunctionVariables;

	/**
	 * \brief All the constraint of the linear problem
	 */
	std::vector<Constraint> mConstraints;

	/**
	 * \brief Content the result of the solution
	 * Empty before solve() call
	 */
	std::map<std::string, double> mResults;

	/**
	 * \brief Integer array of a line
	 * Each line represents a constraint
	 */
	int mMatrixLines[1 + 1000];

	/**
	 * \brief Integer array of a column
	 * Each column represents a variable / constant
	 */
	int mMatrixColumns[1 + 1000];

	/**
	 * \brief Content the value of the coefficient of each variable
	 */
	double mMatrixValues[1 + 1000];

	/**
	 * \brief Iterates over all non-zero values
	 */
	unsigned int mMatrixIterator;
};

# include "linear-problem.hxx"

#endif /* LINEAR_PROBLEM_H_ */

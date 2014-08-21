/*
 * linear-problem.h
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

#ifndef LINEAR_PROBLEM_H_
# define LINEAR_PROBLEM_H_

# include "../header/all.h"
# include "../tools/tools.h"
# include "variable.h"
# include "constraint.h"

enum ProblemObjective {
	min,
	max
};

enum ProblemKind {
	pl,
	plne
};

class LinearProblem {
public:
	LinearProblem(std::string iName, ProblemObjective iObj);
	LinearProblem(std::string iName, ProblemObjective iObj, ProblemKind iKind);
	virtual ~LinearProblem();

public:
	void solve();
	void printResults();

public:
	void addConstraint(Constraint iConstraint);
	void addVariableInObjectiveFunction(double iCoefficient, Variable iVariable);

	std::vector<Constraint> getConstraints();
	std::vector<std::pair<double, Variable>> getObjectiveFunctionVariables();
	std::map<std::string, double> getResults();

private:
	void init();
	void processObjectiveFunction();
	void processConstraints();
	void processSimplex();

private:
	glp_prob* mLinearProb;

	std::string mName;
	ProblemKind mProblemKind;
	ProblemObjective mProblemObjective;

	std::vector<std::pair<double, Variable>> mObjectiveFunctionVariables;
	std::vector<Constraint> mConstraints;
	std::map<std::string, double> mResults;

	int mMatrixLines[1 + 1000];
	int mMatrixColumns[1 + 1000];
	double mMatrixValues[1 + 1000];
	unsigned int mMatrixIterator;
};

# include "linear-problem.hxx"

#endif /* LINEAR_PROBLEM_H_ */

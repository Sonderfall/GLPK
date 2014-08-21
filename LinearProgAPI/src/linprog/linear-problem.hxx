/*
 * linear-problem.hxx
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

inline void
LinearProblem::addVariableInObjectiveFunction(double iCoefficient, Variable iVariable) {
	mObjectiveFunctionVariables.push_back(std::make_pair(iCoefficient, iVariable));
}

inline std::vector<std::pair<double, Variable>>
LinearProblem::getObjectiveFunctionVariables() {
	return mObjectiveFunctionVariables;
}

inline void
LinearProblem::addConstraint(Constraint iConstraint) {
	mConstraints.push_back(iConstraint);
}

inline std::vector<Constraint>
LinearProblem::getConstraints() {
	return mConstraints;
}

inline std::map<std::string, double>
LinearProblem::getResults() {
	return mResults;
}

/*
 * linear-problem.cpp
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

# include "linear-problem.h"

LinearProblem::LinearProblem(std::string iName, ProblemObjective iObj)
: mName (iName)
, mProblemKind (lp)
, mProblemObjective (iObj)
, mMatrixIterator (0) {
	initLinearProblem();
}

LinearProblem::LinearProblem(std::string iName, ProblemObjective iObj, ProblemKind iKind)
: mName (iName)
, mProblemKind (iKind)
, mProblemObjective (iObj)
, mMatrixIterator (0) {
	initLinearProblem();
}

LinearProblem::~LinearProblem() {
	glp_delete_prob(mLinearProb);
}

void
LinearProblem::initLinearProblem() {
	mLinearProb = glp_create_prob();
	glp_set_prob_name(mLinearProb, mName.c_str());
	std::transform(mName.begin(), mName.end(), mName.begin(), toupper);

	switch (mProblemObjective) {
		case max:
			glp_set_obj_dir(mLinearProb, GLP_MAX);
			break;
		case min:
			glp_set_obj_dir(mLinearProb, GLP_MIN);
			break;
		default:
			assert(mProblemObjective == max || mProblemObjective == min);
			break;
	}
}

void
LinearProblem::solve() {
	processObjectiveFunction();
	processConstraints();
	processSimplex();
}

void
LinearProblem::processObjectiveFunction() {
	glp_add_cols(mLinearProb, mObjectiveFunctionVariables.size());
	unsigned int lVariablePosition = 1;
	for (std::pair<double, Variable> lPair : mObjectiveFunctionVariables) {
		double lCoefficient = lPair.first;
		Variable lVariable(lPair.second);
		assert(lVariable.getLowerLimit() <= lVariable.getUpperLimit());
		glp_set_col_name(mLinearProb, lVariablePosition, lVariable.getName().c_str());
		glp_set_obj_coef(mLinearProb, lVariablePosition, lCoefficient);
		glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_DB, lVariable.getLowerLimit(), lVariable.getUpperLimit());

		if (mProblemKind == ilp) {
			glp_set_col_kind(mLinearProb, lVariablePosition, GLP_IV);
		}

		if (lVariable.isBinary()) {
			glp_set_col_kind(mLinearProb, lVariablePosition, GLP_BV);
		}
		++lVariablePosition;
	}
}

void
LinearProblem::processConstraints() {
	processConstraintsAdd();
	processConstraintsVarAndConstant();
}

void
LinearProblem::processConstraintsAdd() {
	glp_add_rows(mLinearProb, mConstraints.size());
	unsigned int lConstraintPosition = 1;
	for (Constraint lConstraint : mConstraints) {
		glp_set_row_name(mLinearProb, lConstraintPosition, lConstraint.getName().c_str());
		if (lConstraint.getLowerLimit() == lConstraint.getUpperLimit()) {
			glp_set_row_bnds(mLinearProb, lConstraintPosition, GLP_FX, lConstraint.getLowerLimit(), lConstraint.getUpperLimit());
		} else {
			glp_set_row_bnds(mLinearProb, lConstraintPosition, GLP_DB, lConstraint.getLowerLimit(), lConstraint.getUpperLimit());
		}
		++lConstraintPosition;
	}
}

void
LinearProblem::processConstraintsVarAndConstant() {
	int lLineIterator = 1;
	for (Constraint lConstraint : mConstraints) {
		std::vector<std::pair<double, Variable>> lVariables = lConstraint.getVariables();
		for (std::pair<double, Variable> lPair : lVariables) {
			++mMatrixIterator;
			Variable lVariable(lPair.second);
			assert(lVariable.getLowerLimit() <= lVariable.getUpperLimit());
			bool lFind = false;
			for (int lColIterator = 1; lColIterator <= glp_get_num_cols(mLinearProb); ++lColIterator) {
				const char* lColName = glp_get_col_name(mLinearProb, lColIterator);
				if (strcmp(lVariable.getName().c_str(), lColName) == 0) {
					mMatrixLines[mMatrixIterator] = lLineIterator;
					mMatrixColumns[mMatrixIterator] = lColIterator;
					mMatrixValues[mMatrixIterator] = lPair.first;
					lFind = true;
					break;
				}
			}
			if (!lFind) {
				glp_add_cols(mLinearProb, 1);
				int lVariablePosition = glp_get_num_cols(mLinearProb);
				glp_set_col_name(mLinearProb, lVariablePosition, lVariable.getName().c_str());
				glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_DB, lVariable.getLowerLimit(), lVariable.getUpperLimit());
				if (mProblemKind == ilp) {
					glp_set_col_kind(mLinearProb, lVariablePosition, GLP_IV);
				}

				if (lVariable.isBinary()) {
					glp_set_col_kind(mLinearProb, lVariablePosition, GLP_BV);
				}
				mMatrixLines[mMatrixIterator] = lLineIterator;
				mMatrixColumns[mMatrixIterator] = lVariablePosition;
				mMatrixValues[mMatrixIterator] = lPair.first;
			}
		}
		std::vector<double> lConstants = lConstraint.getConstants();
		for (double lConstant : lConstants) {
			++mMatrixIterator;
			std::string lConstantName = "Constant " + tool::integerToString(lConstant);
			if (lConstant == PBIGM) {
				lConstantName = "Constant pBigM";
			} else if (lConstant == MBIGM) {
				lConstantName = "Constant mBigM";
			}
			glp_add_cols(mLinearProb, 1);
			int lConstantPosition = glp_get_num_cols(mLinearProb);
			glp_set_col_name(mLinearProb, lConstantPosition, lConstantName.c_str());
			glp_set_col_bnds(mLinearProb, lConstantPosition, GLP_FX, lConstant, lConstant);
			mMatrixLines[mMatrixIterator] = lLineIterator;
			mMatrixColumns[mMatrixIterator] = lConstantPosition;
			mMatrixValues[mMatrixIterator] = 1;
		}
		++lLineIterator;
	}
}

void
LinearProblem::processSimplex() {
	glp_load_matrix(mLinearProb, mMatrixIterator, mMatrixLines, mMatrixColumns, mMatrixValues);
	glp_simplex(mLinearProb, nullptr);
	unsigned int i = 1;
	unsigned int j = 1;

	switch (mProblemKind) {
		case ilp:
			glp_intopt(mLinearProb, nullptr);
			mResults.insert(std::make_pair("Z", glp_mip_obj_val(mLinearProb)));
			for (std::pair<double, Variable> lPair : mObjectiveFunctionVariables) {
				mResults.insert(std::make_pair(lPair.second.getName(), glp_mip_col_val(mLinearProb, i++)));
			}
			break;
		case lp:
			mResults.insert(std::make_pair("Z", glp_get_obj_val(mLinearProb)));
			for (std::pair<double, Variable> lPair : mObjectiveFunctionVariables) {
				mResults.insert(std::make_pair(lPair.second.getName(), glp_get_col_prim(mLinearProb, j++)));
			}
			break;
		default:
			assert(mProblemKind == ilp || mProblemKind == lp);
			break;
	}
}

void
LinearProblem::printResults() {
	if (mProblemObjective == max) {
		std::cout << std::endl << "MAXIMIZATION ";
	} else {
		std::cout << std::endl << "MINIMIZATION ";
	}
	std::cout << "OF THE LINEAR PROBLEM " <<  mName << std::endl << std::endl;
	for (std::pair<std::string, double> lPair : mResults) {
		std::string lName = lPair.first;
		double lValue = lPair.second;
		std::cout << lName << " = " << lValue << std::endl;
	}
	std::cout << std::endl;
}

/*
 * linear-problem.cpp
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

# include "linear-problem.h"

LinearProblem::LinearProblem(std::string iName, ProblemObjective iObj)
: mName (iName)
, mProblemKind (pl)
, mProblemObjective (iObj)
, mMatrixIterator (0) {
	init();
}

LinearProblem::LinearProblem(std::string iName, ProblemObjective iObj, ProblemKind iKind)
: mName (iName)
, mProblemKind (iKind)
, mProblemObjective (iObj)
, mMatrixIterator (0) {
	init();
}

LinearProblem::~LinearProblem() {
	glp_delete_prob(mLinearProb);
}

void
LinearProblem::init() {
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
		glp_set_col_name(mLinearProb, lVariablePosition, lVariable.getName().c_str());
		glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_LO, lVariable.getLowerLimit(), 0.0);
		glp_set_obj_coef(mLinearProb, lVariablePosition, lCoefficient);

		if (lVariable.getUpperLimit() != pInf) {
			assert(lVariable.getLowerLimit() <= lVariable.getUpperLimit());
			//glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_UP, 0.0, lVariable.getUpperLimit());
			glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_DB, lVariable.getLowerLimit(), lVariable.getUpperLimit());
		}

		if (mProblemKind == plne) {
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
	  glp_add_rows(mLinearProb, mConstraints.size());
	  unsigned int lConstraintPosition = 1;
	  for (Constraint lConstraint : mConstraints) {
		  glp_set_row_name(mLinearProb, lConstraintPosition, lConstraint.getName().c_str());
		  if (lConstraint.getLowerLimit() != mInf) {
			  glp_set_row_bnds(mLinearProb, lConstraintPosition, GLP_LO, lConstraint.getLowerLimit(), 0.0);
		  }

		  if (lConstraint.getUpperLimit() != pInf) {
			  glp_set_row_bnds(mLinearProb, lConstraintPosition, GLP_DB, lConstraint.getLowerLimit(), lConstraint.getUpperLimit());
			  //glp_set_row_bnds(mLinearProb, lConstraintPosition, GLP_UP, 0.0, lConstraint.getUpperLimit());
		  }
		  ++lConstraintPosition;
	  }
	  int lLineIterator = 1;
	  for (Constraint lConstraint : mConstraints) {
		  std::vector<std::pair<double, Variable>> lVariables = lConstraint.getVariables();
		  for (std::pair<double, Variable> lPair : lVariables) {
			  ++mMatrixIterator;
			  Variable lVariable(lPair.second);
			  bool lFind = false;
			  for (int lColIterator = 1; lColIterator <= glp_get_num_cols(mLinearProb); ++lColIterator) {
				  const char* lColName = glp_get_col_name(mLinearProb, lColIterator);
				  if (strcmp(lVariable.getName().c_str(), lColName) == 0) {
					  std::cout << "Modify var in constraint : " << lVariable.getName() << " with " << lPair.first << std::endl;

					  mMatrixLines[mMatrixIterator] = lLineIterator,
					  mMatrixColumns[mMatrixIterator] = lColIterator;

					  if (lPair.first == pBigM) {
						  mMatrixValues[mMatrixIterator] = tool::sBigM;
					  } else if (lPair.first == mBigM) {
						  mMatrixValues[mMatrixIterator] = -tool::sBigM;
					  } else {
						  mMatrixValues[mMatrixIterator] = lPair.first;
					  }

					  lFind = true;
					  break;
				  }
			  }
			  if (!lFind) {
				  glp_add_cols(mLinearProb, 1);
				  int lVariablePosition = glp_get_num_cols(mLinearProb);
				  glp_set_col_name(mLinearProb, lVariablePosition, lVariable.getName().c_str());
				  glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_LO, lVariable.getLowerLimit(), 0.0);

				  if (lVariable.getUpperLimit() != pInf) {
					  assert(lVariable.getLowerLimit() <= lVariable.getUpperLimit());
					  //glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_UP, 0.0, lVariable.getUpperLimit());
					  glp_set_col_bnds(mLinearProb, lVariablePosition, GLP_DB, lVariable.getLowerLimit(), lVariable.getUpperLimit());
				  }

				  if (mProblemKind == plne) {
					  glp_set_col_kind(mLinearProb, lVariablePosition, GLP_IV);
				  }

				  if (lVariable.isBinary()) {
					  glp_set_col_kind(mLinearProb, lVariablePosition, GLP_BV);
				  }
				  mMatrixLines[mMatrixIterator] = lLineIterator,
				  mMatrixColumns[mMatrixIterator] = lVariablePosition,
				  mMatrixValues[mMatrixIterator] = lPair.first;

				  std::cout << "Create var in constraint : " << lVariable.getName() << " with " << lPair.first << std::endl;
			  }
		  }
		  std::vector<double> lConstants = lConstraint.getConstants();
		  for (double lConstant : lConstants) {
			  ++mMatrixIterator;
			  std::string lColName = "Constant " + tool::integerToString(lConstant);
			  if (lConstant == pBigM) {
				  lConstant = tool::sBigM;
				  lColName = "Constant pBigM";
			  } else if (lConstant == mBigM) {
				  lConstant = -tool::sBigM;
				  lColName = "Constant mBigM";
			  }

			  std::cout << "ColName " << lColName << std::endl;

			  glp_add_cols(mLinearProb, 1);
			  int lConstantPosition = glp_get_num_cols(mLinearProb);
			  glp_set_col_name(mLinearProb, lConstantPosition, lColName.c_str());
			  glp_set_col_bnds(mLinearProb, lConstantPosition, GLP_FX, lConstant, lConstant);
//			  glp_set_col_bnds(mLinearProb, lConstantPosition, GLP_LO, lConstant, 0.0);
//			  glp_set_col_bnds(mLinearProb, lConstantPosition, GLP_UP, 0.0, lConstant);

//			  std::cout << "lowerbound : " << glp_get_col_ub(mLinearProb, lConstantPosition) << std::endl;

			  mMatrixLines[mMatrixIterator] = lLineIterator,
			  mMatrixColumns[mMatrixIterator] = lConstantPosition,
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
		case plne:
			glp_intopt(mLinearProb, nullptr);
			mResults.insert(std::make_pair("Z", glp_mip_obj_val(mLinearProb)));
			for (std::pair<double, Variable> lPair : mObjectiveFunctionVariables) {
				mResults.insert(std::make_pair(lPair.second.getName(), glp_mip_col_val(mLinearProb, i++)));
			}
			break;
		case pl:
			mResults.insert(std::make_pair("Z", glp_get_obj_val(mLinearProb)));
			for (std::pair<double, Variable> lPair : mObjectiveFunctionVariables) {
				mResults.insert(std::make_pair(lPair.second.getName(), glp_get_col_prim(mLinearProb, j++)));
			}
			break;
		default:
			assert(mProblemKind == plne || mProblemKind == pl);
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

# include "../data/data-base.h"
# include "../linprog/variable.h"
# include "../linprog/constraint.h"
# include "../linprog/linear-problem.h"

void
test() {
	  glp_prob *lp;
	  int ia[1 + 1000], ja[1 + 1000];
	  double ar[1 + 1000], z, x1, x2, x3;

	  lp = glp_create_prob();
	  glp_set_prob_name(lp, "sample");
	  glp_set_obj_dir(lp, GLP_MAX);

	  //

	  glp_add_rows(lp, 3);

	  glp_set_row_name(lp, 1, "p");
	  glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 100.0);

	  glp_set_row_name(lp, 2, "q");
	  glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 600.0);

	  glp_set_row_name(lp, 3, "r");
	  glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 300.0);

	  //

	  glp_add_cols(lp, 4);

	  glp_set_col_name(lp, 1, "x1");
	  glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
	  glp_set_obj_coef(lp, 1, 10.0);
	  glp_set_col_kind(lp, 1, GLP_IV);

	  glp_set_col_name(lp, 2, "x2");
	  glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
	  glp_set_obj_coef(lp, 2, 6.0);
	  glp_set_col_kind(lp, 2, GLP_IV);

	  glp_set_col_name(lp, 3, "x3");
	  glp_set_col_bnds(lp, 3, GLP_LO, 0.0, 0.0);
	  glp_set_obj_coef(lp, 3, 4.0);
	  glp_set_col_kind(lp, 3, GLP_IV);

	  //

	  ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] = 1 */
	  ia[2] = 1, ja[2] = 2, ar[2] = 1.0; /* a[1,2] = 1 */
	  ia[3] = 1, ja[3] = 3, ar[3] = 1.0; /* a[1,3] = 1 */
	  ia[4] = 2, ja[4] = 1, ar[4] = 10.0; /* a[2,1] = 10 */
	  ia[5] = 3, ja[5] = 1, ar[5] = 2.0; /* a[3,1] = 2 */

	  ia[6] = 2, ja[6] = 2, ar[6] = 4.0; /* a[2,2] = 4 */
	  ia[7] = 3, ja[7] = 2, ar[7] = 2.0; /* a[3,2] = 2 */
 	  ia[8] = 2, ja[8] = 3, ar[8] = 5.0; /* a[2,3] = 5 */
	  ia[9] = 3, ja[9] = 3, ar[9] = 6.0; /* a[3,3] = 6 */
	  ia[10] = 1, ja[10] = 4, ar[10] = 6.0; /* a[1,4] = 6 */

	  glp_load_matrix(lp, 10, ia, ja, ar);
	  glp_simplex(lp, NULL);
	  glp_intopt(lp, NULL);

	  z = glp_mip_obj_val(lp);
	  x1 = glp_mip_col_val(lp, 1);
	  x2 = glp_mip_col_val(lp, 2);
	  x3 = glp_mip_col_val(lp, 3);

	  printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3);
	  glp_delete_prob(lp);
}

int
main(int argc, char** argv) {
	DataBase* lDataBase = DataBase::getInstance();
	lDataBase->readFile(argv[1]);

	LinearProblem lLinearProblem("Warehouse stock", max, plne);

	std::vector<Variable> lVariablesInObjectiveFunction;

	for (Site lSite : lDataBase->getSites()) {
		Variable lVariable(lSite.mName, true);
		lLinearProblem.addVariableInObjectiveFunction(lSite.mStock, lVariable);
		lVariablesInObjectiveFunction.push_back(lVariable);
	}

	Constraint lConstraintNbMaxWarehouse("NbMaxWarehouses");
	lConstraintNbMaxWarehouse.setLimits(1, lDataBase->getNbWareHouseToBuild());

	for (Variable lVariable : lVariablesInObjectiveFunction) {
		lConstraintNbMaxWarehouse.addVariableInConstraint(1, lVariable);
	}

	lLinearProblem.addConstraint(lConstraintNbMaxWarehouse);

	std::map<Variable, Variable> lConstraintMapping;
	for (Variable lFirstVariable : lVariablesInObjectiveFunction) {
		for (Variable lSecondVariable : lVariablesInObjectiveFunction) {
			if (lFirstVariable.getName() != lSecondVariable.getName()) {
				bool lExist = false;
				for (std::pair<Variable, Variable> lPair : lConstraintMapping) {
					if (lSecondVariable.getName() == lPair.first.getName()
						&& lFirstVariable.getName() == lPair.second.getName()) {
						lExist = true;
						break;
					}
				}

				if (!lExist) {
					lConstraintMapping.insert(std::make_pair(lFirstVariable, lSecondVariable));

					std::string lVariableBinaryName("VariableBinary ");
					lVariableBinaryName.append(lFirstVariable.getName());
					lVariableBinaryName.append(" and ");
					lVariableBinaryName.append(lSecondVariable.getName());
					Variable lVariableBinary(lVariableBinaryName.c_str(), true);

					std::string lConstraintDistanceName("ConstraintDistance ");
					lConstraintDistanceName.append(lFirstVariable.getName());
					lConstraintDistanceName.append(" and ");
					lConstraintDistanceName.append(lSecondVariable.getName());

					Constraint lConstraintDistance(lConstraintDistanceName.c_str());
					lConstraintDistance.setLimits(mInf, 50);
					std::pair<int, int> lFirstPair = lDataBase->getCoordinates(lFirstVariable.getName());
					std::pair<int, int> lSecondPair = lDataBase->getCoordinates(lSecondVariable.getName());
					lConstraintDistance.addConstantInConstraint(tool::euclidianDistance(lFirstPair.first,
																						lFirstPair.second,
																						lSecondPair.first,
																						lSecondPair.second));
					lConstraintDistance.addConstantInConstraint(mBigM);
					lConstraintDistance.addVariableInConstraint(pBigM, lVariableBinary);
					lConstraintDistance.setLimits(mInf, 50);

					std::string lConstraintFirstVariableName("ConstraintImpl ");
					lConstraintFirstVariableName.append(lFirstVariable.getName());
					lConstraintFirstVariableName.append(" with ");
					lConstraintFirstVariableName.append(lSecondVariable.getName());

					Constraint lConstraintFirstVariable(lConstraintFirstVariableName.c_str());
					lConstraintFirstVariable.addVariableInConstraint(1, lFirstVariable);
					lConstraintFirstVariable.addVariableInConstraint(mBigM, lVariableBinary);
					lConstraintFirstVariable.addConstantInConstraint(pBigM);
					lConstraintFirstVariable.setLimits(0, pInf);

					std::string lConstraintSecondVariableName("ConstraintImpl ");
					lConstraintSecondVariableName.append(lSecondVariable.getName());
					lConstraintSecondVariableName.append(" with ");
					lConstraintSecondVariableName.append(lFirstVariable.getName());

					Constraint lConstraintSecondVariable(lConstraintSecondVariableName.c_str());
					lConstraintSecondVariable.addVariableInConstraint(1, lSecondVariable);
					lConstraintSecondVariable.addVariableInConstraint(mBigM, lVariableBinary);
					lConstraintSecondVariable.addConstantInConstraint(pBigM);
					lConstraintSecondVariable.setLimits(0, pInf);

//					std::cout << lConstraintDistanceName << std::endl;
//					std::cout << lVariableBinaryName << std::endl;
//					std::cout << lConstraintFirstVariableName << std::endl;
//					std::cout << lConstraintSecondVariableName << std::endl;
//					std::cout << "Distance : " << tool::euclidianDistance(lFirstPair.first, lFirstPair.second,
//							lSecondPair.first,
//							lSecondPair.second) << std::endl << std::endl;

					lLinearProblem.addConstraint(lConstraintDistance);
					lLinearProblem.addConstraint(lConstraintFirstVariable);
					lLinearProblem.addConstraint(lConstraintSecondVariable);
				}
			}
		}
	}

	lLinearProblem.solve();
	lLinearProblem.printResults();
	return 0;
}

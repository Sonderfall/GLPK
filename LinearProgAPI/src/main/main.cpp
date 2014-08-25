# include "../data/data-base.h"
# include "../linprog/variable.h"
# include "../linprog/constraint.h"
# include "../linprog/linear-problem.h"

void
implemOne() {
	DataBase* lDataBase = DataBase::getInstance();
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

					std::pair<int, int> lFirstPair = lDataBase->getCoordinates(lFirstVariable.getName());
					std::pair<int, int> lSecondPair = lDataBase->getCoordinates(lSecondVariable.getName());

					Constraint lConstraintDistance(lConstraintDistanceName.c_str());
					lConstraintDistance.addConstantInConstraint(50);
					lConstraintDistance.addConstantInConstraint(PBIGM);
					lConstraintDistance.addVariableInConstraint(MBIGM, lVariableBinary);
					lConstraintDistance.setLimits(tool::euclidianDistance(lFirstPair.first, lFirstPair.second,
							 	 	 	 	 	 	 	 	 	 	 	  lSecondPair.first, lSecondPair.second), PINF);

					std::string lConstraintChooseName("ConstraintChoose ");
					lConstraintChooseName.append(lSecondVariable.getName());
					lConstraintChooseName.append(" with ");
					lConstraintChooseName.append(lFirstVariable.getName());

					Constraint lConstraintChoose(lConstraintChooseName.c_str());
					lConstraintChoose.addVariableInConstraint(1, lFirstVariable);
					lConstraintChoose.addVariableInConstraint(1, lSecondVariable);
					lConstraintChoose.addVariableInConstraint(-1, lVariableBinary);
					lConstraintChoose.setLimits(0, 1);

					lLinearProblem.addConstraint(lConstraintDistance);
					lLinearProblem.addConstraint(lConstraintChoose);
				}
			}
		}
	}

	lLinearProblem.solve();
	lLinearProblem.printResults();
	lDataBase->outputResult(lLinearProblem.getResults(), "results.txt");
}

void
implemTwo() {
	DataBase* lDataBase = DataBase::getInstance();
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

					std::string lConstraintDistanceName("ConstraintDistance ");
					lConstraintDistanceName.append(lFirstVariable.getName());
					lConstraintDistanceName.append(" and ");
					lConstraintDistanceName.append(lSecondVariable.getName());

					std::pair<int, int> lFirstPair = lDataBase->getCoordinates(lFirstVariable.getName());
					std::pair<int, int> lSecondPair = lDataBase->getCoordinates(lSecondVariable.getName());

					Constraint lConstraintDistance(lConstraintDistanceName.c_str());
					lConstraintDistance.addVariableInConstraint(tool::euclidianDistance(lFirstPair.first, lFirstPair.second,
	 	 	 	 	 	 	 	  lSecondPair.first, lSecondPair.second), lFirstVariable);
					lConstraintDistance.addVariableInConstraint(PBIGM, lSecondVariable);
					lConstraintDistance.addConstantInConstraint(MBIGM);
					lConstraintDistance.setLimits(MINF, 50);

					lLinearProblem.addConstraint(lConstraintDistance);
				}
			}
		}
	}

	lLinearProblem.solve();
	lLinearProblem.printResults();
	lDataBase->outputResult(lLinearProblem.getResults(), "results.txt");
}

void
implemThree() {
	LinearProblem lLinearProblem("GLPK Example", max, plne);

	Variable lVariableX1("X1");
	Variable lVariableX2("X2");
	Variable lVariableX3("X3");

	lLinearProblem.addVariableInObjectiveFunction(10, lVariableX1);
	lLinearProblem.addVariableInObjectiveFunction(6, lVariableX2);
	lLinearProblem.addVariableInObjectiveFunction(4, lVariableX3);

	Constraint lConstraintP("P");
	lConstraintP.addVariableInConstraint(1, lVariableX1);
	lConstraintP.addVariableInConstraint(1, lVariableX2);
	lConstraintP.addVariableInConstraint(1, lVariableX3);
	lConstraintP.setLimits(MINF, 100);

	Constraint lConstraintQ("Q");
	lConstraintQ.addVariableInConstraint(10, lVariableX1);
	lConstraintQ.addVariableInConstraint(4, lVariableX2);
	lConstraintQ.addVariableInConstraint(5, lVariableX3);
	lConstraintQ.setLimits(MINF, 600);

	Constraint lConstraintR("R");
	lConstraintR.addVariableInConstraint(2, lVariableX1);
	lConstraintR.addVariableInConstraint(2, lVariableX2);
	lConstraintR.addVariableInConstraint(6, lVariableX3);
	lConstraintR.setLimits(MINF, 300);

	lLinearProblem.addConstraint(lConstraintP);
	lLinearProblem.addConstraint(lConstraintQ);
	lLinearProblem.addConstraint(lConstraintR);

	lLinearProblem.solve();
	lLinearProblem.printResults();
}

int
main(int argc, char** argv) {
	DataBase* lDataBase = DataBase::getInstance();
	lDataBase->readFile(argv[1]);

	implemOne();

//	implemTwo();

//	implemThree();

	return 0;
}

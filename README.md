# README #

### Authors ###

* Valentin 'Valtyr' Macheret

### Overview ###

This project contains a C++ (with only STL) API for the GNU Linear Programmation Kit, GLPK.
It allows to establish basic and advanced linear problem through an object oriented interface.

### Features ###

There are three main new class in this C++ API :
* LinearProblem : The problem it self, easy to set parameters (maximization/minimization and if it's an integer problem).
* Variable : Can be a decision varable and / or modelisation variable.
* Constraint : Contains variable and potential constant.

### Usecase ###

#### Modelisation ####

Maximize : z = 10x1 + 6x2 + 4x3
subject to :
* x1 + x2 + x3 ≤ 100
* 10x1 + 4x2 + 5x3 ≤ 600
* 2x1 + 2x2 + 6x3 ≤ 300
where all variables are non-negative : x1 ≥ 0, x2 ≥ 0, x3 ≥ 0

#### Implementation ####

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
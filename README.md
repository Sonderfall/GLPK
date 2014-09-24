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
* Constraint : Contains variables and potential constants.

### Usecase ###

#### Modelisation ####

Maximize : z = 10x1 + 6x2 + 4x3
subject to :

* x1 + x2 + x3 ≤ 100
* 10x1 + 4x2 + 5x3 ≤ 600
* 2x1 + 2x2 + 6x3 ≤ 300

where all variables are non-negative : x1 ≥ 0, x2 ≥ 0, x3 ≥ 0

#### Implementation ####

	/* Problem declaration, specify its name, the objective and if it's an integer problem */
	LinearProblem lLinearProblem("GLPK Example", max, plne);

	/* Variables declaration */
	Variable lVariableX1("X1");
	Variable lVariableX2("X2");
	Variable lVariableX3("X3");

	/* Add variables to the objective function of the linear problem */
	lLinearProblem(10, lVariableX1);
	lLinearProblem(6, lVariableX2);
	lLinearProblem(4, lVariableX3);

	/* Declaration of a constraint P and add variables in this constraint */
	Constraint lConstraintP("P");
	lConstraintP(lVariableX1);
	lConstraintP(lVariableX2);
	lConstraintP(lVariableX3);
	lConstraintP.setLimits(MINF, 100);

	/* Declaration of a constraint Q and add variables in this constraint */
	Constraint lConstraintQ("Q");
	lConstraintQ(10, lVariableX1);
	lConstraintQ(4, lVariableX2);
	lConstraintQ(5, lVariableX3);
	lConstraintQ.setLimits(MINF, 600);

	/* Declaration of a constraint R and add variables in this constraint */
	Constraint lConstraintR("R");
	lConstraintR(2, lVariableX1);
	lConstraintR(2, lVariableX2);
	lConstraintR(6, lVariableX3);
	lConstraintR.setLimits(MINF, 300);

	/* Add constraints to the linear problem */
	lLinearProblem(lConstraintP);
	lLinearProblem(lConstraintQ);
	lLinearProblem(lConstraintR);

	/* Solve the problem with the simplex algorithm */
	lLinearProblem.solve();
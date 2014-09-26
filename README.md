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

	/* Problem declaration, specify its name, the objective and if it's a integer problem */
	LinearProblem lLinearProblem("GLPK Example", max, plne);

	/* Variables declaration */
	Variable lX1("X1");
	Variable lX2("X2");
	Variable lX3("X3");

	/* Add variables to the objective function of the linear problem */
	lLinearProblem(10, lX1)(6, lX2)(4, lX3);

	/* Declaration of a constraint P and add variables in this constraint */
	Constraint lConstraintP("P");
	lConstraintP(lX1)(lX2)(lX3);
	lConstraintP.setLimits(MINF, 100);

	/* Declaration of a constraint Q and add variables in this constraint */
	Constraint lConstraintQ("Q");
	lConstraintQ(10, lX1)(4, lX2)(5, lX3);
	lConstraintQ.setLimits(MINF, 600);

	/* Declaration of a constraint R and add variables in this constraint */
	Constraint lConstraintR("R");
	lConstraintR(2, lX1)(2, lX2)(6, lX3);
	lConstraintR.setLimits(MINF, 300);

	/* Add constraints to the linear problem */
	lLinearProblem(lConstraintP);
	lLinearProblem(lConstraintQ);
	lLinearProblem(lConstraintR);

	/* Solve the problem with the simplex algorithm */
	lLinearProblem.solve();

	/* Show results */
	lLinearProblem.printResults();
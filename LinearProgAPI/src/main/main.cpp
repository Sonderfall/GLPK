# include "../linprog/linprog.h"

void
implemGLPK() {
	/* Problem declaration, specify its name, the objective and if it's a integer problem */
	LinearProblem lLinearProblem("GLPK Example", max, ilp);

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
	lLinearProblem
	(lConstraintP)
	(lConstraintQ)
	(lConstraintR);

	/* Solve the problem with the simplex algorithm */
	lLinearProblem.solve();

	/* Show results */
	lLinearProblem.printResults();
}

int
main(int argc, char** argv) {
	implemGLPK();
	return 0;
}

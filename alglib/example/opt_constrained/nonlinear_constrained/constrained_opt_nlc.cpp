#include <linalg.h>
#include <optimization.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * min f(x0,x1) = x0+x1
 * s.t.
 *      x0^2 + x1^2 - 1 <= 0
 *      x2-exp(x0) = 0
 */

/**
 * calculates
 * f0(x0,x1,x2) = x0+x1
 * f1(x0,x1,x2) = x2-exp(x0)
 * f2(x0,x1,x2) = x0^2+x1^2-1
 * and Jacobian matrix J = [dfi/dxj]
 */
void nlcfunc2_jac(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr) {
    fi[0] = x[0] + x[1];
    fi[1] = x[2] - exp(x[0]);
    fi[2] = x[0] * x[0] + x[1] * x[1] - 1.0;
    jac[0][0] = 1.0;
    jac[0][1] = 1.0;
    jac[0][2] = 0.0;
    jac[1][0] = -exp(x[0]);
    jac[1][1] = 0.0;
    jac[1][2] = 1.0;
    jac[2][0] = 2 * x[0];
    jac[2][1] = 2 * x[1];
    jac[2][2] = 0.0;
}

/**
 * SLP - successive linear programming NLP solver
 * SLP is the most robust solver provided by ALGLIB: it can solve both convex and nonconvex optimization problems,
 * it respects box and linear constraints (after you find feasible point it won't move away from the feasible area)
 * and tries to respect nonlinear constraints as much as possible. It also usually needs less function evaluations
 * to converge than AUL. However, it solves LP subproblems at each iterations which adds significant overhead to
 * its running time. Sometimes it can be as much as 7x times slower than AUL.
 * We recommend you to use SLP at least for early prototyping stages
 */
void slp() {
    real_1d_array x0 = "[0,0,0]";  // init point
    real_1d_array s = "[1,1,1]";   // unit scale
    double epsx = 0.000001;        // stopping condition for inner iterations
    ae_int_t maxits = 0;
    minnlcstate state;
    minnlcreport rep;
    real_1d_array x1;

    minnlccreate(3, x0, state);
    minnlcsetcond(state, epsx, maxits);
    minnlcsetscale(state, s);
    minnlcsetstpmax(state, 10.0);  // step length to avoid probing locations where exp() is large

    minnlcsetalgoslp(state);

    /**
     * Set constraints:
     * only constraint counts are passed:
     * first parameter is number of equality constraints, second one is number of inequality constraints.
     * As for constraining functions - these functions are passed as part of problem Jacobian
     * it supports arbitrary combination of boundary, check minnlcsetbc() and minnlcsetlc()
     */
    minnlcsetnlc(state, 1, 1);

    minnlcoptguardsmoothness(state);
    minnlcoptguardgradient(state, 0.001);

    /**
     * Optimizer object accepts vector function and its Jacobian, with first component being target function,
     * and next components being nonlinear equality and inequality constraints
     * our vector function has form {f0,f1,f2} = { x0+x1 , x2-exp(x0) , x0^2+x1^2-1 }
     * equality ones always being first, inequality ones being last
     */
    alglib::minnlcoptimize(state, nlcfunc2_jac);
    minnlcresults(state, x1, rep);
    cout << "slp result: " << x1.tostring(x1.length()) << endl;  // expected: [-0.70710,-0.70710,0.49306]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    minnlcoptguardresults(state, ogrep);
    cout << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << "," << ogrep.badgradsuspected << endl;
}

/**
 * AUL - augmented Lagrangian NLP solver
 * AUL solver is less robust than SLP - it can violate box and linear constraints at any moment,
 * and it is intended for convex optimization problems (although in many cases it can deal with nonconvex ones too).
 * Also, unlike SLP it needs some tuning (penalty factor and number of outer iterations).
 * However, it is often much faster than the current version of SLP
 *
 */
void aul() {
    real_1d_array x0 = "[0,0,0]";  // init point
    real_1d_array s = "[1,1,1]";   // unit scale
    double epsx = 0.000001;        // stopping condition for inner iterations
    ae_int_t maxits = 0;
    minnlcstate state;
    minnlcreport rep;
    real_1d_array x1;

    minnlccreate(3, x0, state);
    minnlcsetcond(state, epsx, maxits);
    minnlcsetscale(state, s);
    minnlcsetstpmax(state, 10.0);  // step length to avoid probing locations where exp() is large

    double rho = 1000.0;
    ae_int_t outerits = 5;
    minnlcsetalgoaul(state, rho, outerits);

    /**
     * Set constraints:
     * only constraint counts are passed:
     * first parameter is number of equality constraints, second one is number of inequality constraints.
     * As for constraining functions - these functions are passed as part of problem Jacobian
     * it supports arbitrary combination of boundary, check minnlcsetbc() and minnlcsetlc()
     */
    minnlcsetnlc(state, 1, 1);

    minnlcoptguardsmoothness(state);
    minnlcoptguardgradient(state, 0.001);

    /**
     * Optimizer object accepts vector function and its Jacobian, with first component being target function,
     * and next components being nonlinear equality and inequality constraints
     * our vector function has form {f0,f1,f2} = { x0+x1 , x2-exp(x0) , x0^2+x1^2-1 }
     * equality ones always being first, inequality ones being last
     */
    alglib::minnlcoptimize(state, nlcfunc2_jac);
    minnlcresults(state, x1, rep);
    cout << "aul result: " << x1.tostring(x1.length()) << endl;  // expected: [-0.70710,-0.70710,0.49306]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    minnlcoptguardresults(state, ogrep);
    cout << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << "," << ogrep.badgradsuspected << endl;
}

int main() {
    slp();
    aul();
}

#include <linalg.h>
#include <optimization.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * min f(x0,x1) = 2*|x0|+|x1|
 * s.t.
 *      1 <= x0 < +INF
 *      -INF <= x1 < +INF
 */

void nsfunc1_jac(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr) {
    // this callback calculates f0(x0,x1) = 2*|x0|+x1 and Jacobian matrix J = [df0/dx0 df0/dx1]
    fi[0] = 2 * fabs(double(x[0])) + fabs(double(x[1]));
    jac[0][0] = 2 * alglib::sign(x[0]);
    jac[0][1] = alglib::sign(x[1]);
}

int main() {
    real_1d_array x0 = "[1,1]";
    real_1d_array s = "[1,1]";  // unit scale
    real_1d_array bndl = "[1,-inf]";
    real_1d_array bndu = "[+inf,+inf]";
    double epsx = 0.00001;  // stopping conditions
    double radius = 0.1;    // search radius, initial value, will be automatically decreased later
    double rho = 0.0;       // penalty coefficient for nonlinear constraints; 0 because we do not have such constraints
    ae_int_t maxits = 0;
    minnsstate state;
    minnsreport rep;
    real_1d_array x1;

    minnscreate(2, x0, state);
    minnssetalgoags(state, radius, rho);
    minnssetcond(state, epsx, maxits);
    minnssetscale(state, s);

    /**
     * Set box constraints
     * General linear constraints are set in similar way (see minnssetlc() for more information)
     * You may combine box, linear and nonlinear constraints in one optimization problem
     */
    minnssetbc(state, bndl, bndu);

    /**
     * If do not have nonlinear constraints, then you will have one-component function vector and 1xN Jacobian matrix
     * AGS solver used by us can handle nonsmooth and nonconvex optimization problems. It has convergence guarantees
     */
    alglib::minnsoptimize(state, nsfunc1_jac);
    minnsresults(state, x1, rep);
    cout << x1.tostring(x1.length()) << endl;  // expected: [1.0000,0.0000]
}

#include <linalg.h>
#include <optimization.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * min f(x0,x1) = 2*|x0|+|x1|
 */

void nsfunc1_fvec(const real_1d_array &x, real_1d_array &fi, void *ptr) {
    // this callback calculates f0(x0,x1) = 2*|x0|+|x1|
    fi[0] = 2 * fabs(double(x[0])) + fabs(double(x[1]));
}

int main() {
    real_1d_array x0 = "[1,1]";
    real_1d_array s = "[1,1]";  // unit scale
    double epsx = 0.00001;      // stopping conditions
    double radius = 0.1;        // search radius, initial value, will be automatically decreased later
    double rho = 0.0;  // penalty coefficient for nonlinear constraints; 0 because we do not have such constraints
    double diffstep = 0.000001;
    ae_int_t maxits = 0;
    minnsstate state;
    minnsreport rep;
    real_1d_array x1;

    minnscreatef(2, x0, diffstep, state);
    minnssetalgoags(state, radius, rho);
    minnssetcond(state, epsx, maxits);
    minnssetscale(state, s);

    /**
     * If do not have nonlinear constraints, then you will have one-component function vector
     */
    alglib::minnsoptimize(state, nsfunc1_fvec);
    minnsresults(state, x1, rep);
    cout << x1.tostring(x1.length()) << endl;  // expected: [0.0000,0.0000]
}

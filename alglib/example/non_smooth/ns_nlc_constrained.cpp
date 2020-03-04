#include <linalg.h>
#include <optimization.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * min f(x0,x1) = 2*|x0|+|x1|
 * s.t.
 *      x0  =  1
 *      x1 >= -1
 * Although these constraints are linear, we treat them as general nonlinear constraints in order to
 * demonstrate nonlinearly constrained optimization setup
 */

/**
 * calculates function vector
 * f0(x0,x1) = 2*|x0|+|x1|
 * f1(x0,x1) = x0-1
 * f2(x0,x1) = -x1-1
 * and Jacobian matrix J = [dfi/dxj]
 *          [ 2*sign(x0)   sign(x1) ]
 *      J = [     1           0     ]
 *          [     0          -1     ]
 */
void nsfunc2_jac(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr) {
    fi[0] = 2 * fabs(double(x[0])) + fabs(double(x[1]));
    jac[0][0] = 2 * alglib::sign(x[0]);
    jac[0][1] = alglib::sign(x[1]);
    fi[1] = x[0] - 1;
    jac[1][0] = 1;
    jac[1][1] = 0;
    fi[2] = -x[1] - 1;
    jac[2][0] = 0;
    jac[2][1] = -1;
}

/**
 * AGS algorithm
 * it can handle nonsmooth and nonconvex optimization problems. It has convergence guarantees, i.e. it will converge to
 * stationary point of the function after running for some time.
 * However, it is important to remember that "stationary point" is not equal to "solution".
 * If your problem is convex, everything is OK.
 * But nonconvex optimization problems may have "flat spots" - large areas where gradient is exactly zero,
 * but function value is far away from optimal. Such areas are stationary points too, and optimizer may be trapped here
 * "Flat spots" are nonsmooth equivalent of the saddle points, but with orders of magnitude worse properties -
 * they may be quite large and hard to avoid. All nonsmooth optimizers are prone to this kind of the problem,
 * because it is impossible to automatically distinguish "flat spot" from true solution.
 * Visual inspection of results is essential.
 */
void nonsmooth_nonlinear() {
    real_1d_array x0 = "[1,1]";
    real_1d_array s = "[1,1]";  // unit scale
    double epsx = 0.00001;      // stopping conditions
    double radius = 0.1;        // good initial value; will be automatically decreased later
    /**
     * penalty coefficient for nonlinear constraints, choose good one, large enough that it enforces constraints,
     * but small enough in order to avoid extreme slowdown due to ill-conditioning
     */
    double rho = 50.0;
    ae_int_t maxits = 0;
    minnsstate state;
    minnsreport rep;
    real_1d_array x1;

    minnscreate(2, x0, state);
    minnssetalgoags(state, radius, rho);
    minnssetcond(state, epsx, maxits);
    minnssetscale(state, s);

    /**
     * Set constraints:
     * only constraint counts are passed:
     * first parameter is number of equality constraints, second one is number of inequality constraints.
     * As for constraining functions - these functions are passed as part of problem Jacobian
     * it supports arbitrary combination of boundary, check minnlcsetlc()
     */
    minnssetnlc(state, 1, 1);

    /**
     * Nonlinear equality constraints have form Gi(x)=0, inequality ones have form Hi(x)<=0,
     * so we may have to "normalize" constraints prior to passing them to optimizer
     */
    alglib::minnsoptimize(state, nsfunc2_jac);
    minnsresults(state, x1, rep);
    cout << "ns result: " << x1.tostring(x1.length()) << endl;  // expected: [1.0000,0.0000]
}

int main() { nonsmooth_nonlinear(); }

#include <linalg.h>
#include <optimization.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * min [ f1^2 + f2^2 + ... + fm^2 ], with fi =fi(x1 ,...,xn)
 * example:
 *      f0(x0,x1) = 100*(x0+3)^4
 *      f1(x0,x1) = (x1-3)^4
 */

void function1_fvec(const real_1d_array &x, real_1d_array &fi, void *ptr) {
    fi[0] = 10 * pow(x[0] + 3, 2);
    fi[1] = pow(x[1] - 3, 2);
}

void function1_jac(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr) {
    // Jacobian matrix J = [dfi/dxj]
    fi[0] = 10 * pow(x[0] + 3, 2);
    fi[1] = pow(x[1] - 3, 2);
    jac[0][0] = 20 * (x[0] + 3);
    jac[0][1] = 0;
    jac[1][0] = 0;
    jac[1][1] = 2 * (x[1] - 3);
}

void function1_func(const real_1d_array &x, double &func, void *ptr) {
    // this callback calculates f(x0,x1) = 100*(x0+3)^4 + (x1-3)^4
    func = 100 * pow(x[0] + 3, 4) + pow(x[1] - 3, 4);
}
void function1_grad(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr) {
    // this callback calculates f(x0,x1) = 100*(x0+3)^4 + (x1-3)^4 and its derivatives df/d0 and df/dx1
    func = 100 * pow(x[0] + 3, 4) + pow(x[1] - 3, 4);
    grad[0] = 400 * pow(x[0] + 3, 3);
    grad[1] = 4 * pow(x[1] - 3, 3);
}
void function1_hess(const real_1d_array &x, double &func, real_1d_array &grad, real_2d_array &hess, void *ptr) {
    // this callback calculates f(x0,x1) = 100*(x0+3)^4 + (x1-3)^4 its derivatives df/d0 and df/dx1 and its Hessian.
    func = 100 * pow(x[0] + 3, 4) + pow(x[1] - 3, 4);
    grad[0] = 400 * pow(x[0] + 3, 3);
    grad[1] = 4 * pow(x[1] - 3, 3);
    hess[0][0] = 1200 * pow(x[0] + 3, 2);
    hess[0][1] = 0;
    hess[1][0] = 0;
    hess[1][1] = 12 * pow(x[1] - 3, 2);
}

/**
 * No other information (Jacobian, gradient, etc.) is needed
 */
void linear_ls_fit() {
    real_1d_array x = "[0,0]";   // initial point
    real_1d_array s = "[1,1]";   // initial unit scale
    double epsx = 0.0000000001;  // stop after short enough step (less than epsx)
    double diffstep = 0.0001;    // use numerical differentiation with step equal to 0.0001
    ae_int_t maxits = 0;
    minlmstate state;
    minlmreport rep;

    minlmcreatev(2, x, diffstep, state);
    minlmsetcond(state, epsx, maxits);
    minlmsetscale(state, s);

    // Optimize
    alglib::minlmoptimize(state, function1_fvec);

    // because we use numerical differentiation, we do not verify Jacobian correctness
    minlmresults(state, x, rep);
    cout << x.tostring(x.length()) << endl;  // expected: [-3,3]
}

void lm_with_Jacobian() {
    real_1d_array x = "[0,0]";   // initial point
    real_1d_array s = "[1,1]";   // initial unit scale
    double epsx = 0.0000000001;  // stop after short enough step (less than epsx)
    ae_int_t maxits = 0;
    minlmstate state;
    minlmreport rep;

    minlmcreatevj(2, x, state);
    minlmsetcond(state, epsx, maxits);
    minlmsetscale(state, s);

    // Activate OptGuard integrity checking
    minlmoptguardgradient(state, 0.001);

    // Optimize
    alglib::minlmoptimize(state, function1_fvec, function1_jac);

    // because we use numerical differentiation, we do not verify Jacobian correctness
    minlmresults(state, x, rep);
    cout << x.tostring(x.length()) << endl;  // expected: [-3,3]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    minlmoptguardresults(state, ogrep);
    cout << ogrep.badgradsuspected << endl;
}

/**
 * Optimization algorithm uses:
 *      function value F(x0,x1)
 *      gradient G={dF/dxi}
 *      Hessian H={d2F/(dxi*dxj)}
 */
void lm_with_gradient_hessian() {
    real_1d_array x = "[0,0]";   // initial point
    double epsx = 0.0000000001;  // stop after short enough step (less than epsx)
    ae_int_t maxits = 0;
    minlmstate state;
    minlmreport rep;

    minlmcreatefgh(x, state);
    minlmsetcond(state, epsx, maxits);
    alglib::minlmoptimize(state, function1_func, function1_grad, function1_hess);
    minlmresults(state, x, rep);
    cout << x.tostring(x.length()) << endl;  // expected: [-3,3]
}

int main() {
    linear_ls_fit();
    lm_with_Jacobian();
    lm_with_gradient_hessian();
}

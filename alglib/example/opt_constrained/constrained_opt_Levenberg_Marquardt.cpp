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
 *      -1 <= x0 <= +1
 *      -1 <= x1 <= +1
 */

void function1_fvec(const real_1d_array &x, real_1d_array &fi, void *ptr) {
    fi[0] = 10 * pow(x[0] + 3, 2);
    fi[1] = pow(x[1] - 3, 2);
}

/**
 * No other information (Jacobian, gradient, etc.) is needed
 */
void linear_ls_fit() {
    real_1d_array x = "[0,0]";  // initial point
    real_1d_array s = "[1,1]";  // initial unit scale
    real_1d_array bndl = "[-1,-1]";
    real_1d_array bndu = "[+1,+1]";
    double epsx = 0.0000000001;  // stop after short enough step (less than epsx)
    double diffstep = 0.0001;    // use numerical differentiation with step equal to 0.0001
    ae_int_t maxits = 0;
    minlmstate state;
    minlmreport rep;

    minlmcreatev(2, x, diffstep, state);
    minlmsetbc(state, bndl, bndu);
    minlmsetcond(state, epsx, maxits);
    minlmsetscale(state, s);

    // Optimize
    alglib::minlmoptimize(state, function1_fvec);

    // because we use numerical differentiation, we do not verify Jacobian correctness
    minlmresults(state, x, rep);
    cout << x.tostring(x.length()) << endl;  // expected: [-1,+1]
}

int main() { linear_ls_fit(); }

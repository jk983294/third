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

void function1_grad(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr) {
    // this callback calculates f(x0,x1) = 100*(x0+3)^4 + (x1-3)^4 and its derivatives df/d0 and df/dx1
    func = 100 * pow(x[0] + 3, 4) + pow(x[1] - 3, 4);
    grad[0] = 400 * pow(x[0] + 3, 3);
    grad[1] = 4 * pow(x[1] - 3, 3);
}

void function1_func(const real_1d_array &x, double &func, void *ptr) {
    func = 100 * pow(x[0] + 3, 4) + pow(x[1] - 3, 4);
}

void box_constrained_linear_opt() {
    real_1d_array x = "[0,0]";  // initial point
    real_1d_array s = "[1,1]";  // initial unit scale
    // subject to box constraints:
    real_1d_array bndl = "[-1,-1]";
    real_1d_array bndu = "[+1,+1]";
    double epsg = 0;
    double epsf = 0;
    double epsx = 0.000001;  // stop after short enough step (less than epsx)
    ae_int_t maxits = 0;
    minbleicstate state;
    minbleiccreate(x, state);
    minbleicsetbc(state, bndl, bndu);                  // set box constraints
    minbleicsetscale(state, s);                        // set variable scales
    minbleicsetcond(state, epsg, epsf, epsx, maxits);  // set stopping criteria

    // Then we activate OptGuard integrity checking.
    minbleicoptguardsmoothness(state);
    minbleicoptguardgradient(state, 0.001);

    // Optimize and evaluate results
    minbleicreport rep;
    alglib::minbleicoptimize(state, function1_grad);
    minbleicresults(state, x, rep);
    cout << "achieve min at " << x.tostring(x.length()) << endl;  // expected: [-1,+1]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    minbleicoptguardresults(state, ogrep);
    cout << ogrep.badgradsuspected << "," << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << endl;
}

void box_constrained_linear_opt_num_diff() {
    real_1d_array x = "[0,0]";  // initial point
    real_1d_array s = "[1,1]";  // initial unit scale
    // subject to box constraints:
    real_1d_array bndl = "[-1,-1]";
    real_1d_array bndu = "[+1,+1]";
    double epsg = 0;
    double epsf = 0;
    double epsx = 0.000001;  // stop after short enough step (less than epsx)
    double diffstep = 1.0e-6;
    ae_int_t maxits = 0;
    minbleicstate state;

    minbleiccreatef(x, diffstep, state);
    minbleicsetbc(state, bndl, bndu);                  // set box constraints
    minbleicsetscale(state, s);                        // set variable scales
    minbleicsetcond(state, epsg, epsf, epsx, maxits);  // set stopping criteria

    // Then we activate OptGuard integrity checking.
    minbleicoptguardsmoothness(state);

    // Optimize and evaluate results
    minbleicreport rep;
    alglib::minbleicoptimize(state, function1_func);
    minbleicresults(state, x, rep);
    cout << "achieve min at " << x.tostring(x.length()) << endl;  // expected: [-1,+1]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    minbleicoptguardresults(state, ogrep);
    cout << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << endl;
}

/**
 * min f(x,y) = 100*(x+3)^4+(y-3)^4
 * s.t. x>=2 (posed as general linear constraint)
 *      x+y>=6
 */
void inequality_constrained_linear_opt() {
    real_1d_array x = "[5,5]";              // initial point
    real_1d_array s = "[1,1]";              // initial unit scale
    real_2d_array c = "[[1,0,2],[1,1,6]]";  // x + 0*y ct 2; x + y ct 6
    integer_1d_array ct = "[1,1]";          // constraint type: 0(=), 1(>=), -1(<=)
    minbleicstate state;
    double epsg = 0;
    double epsf = 0;
    double epsx = 0.000001;  // stop after short enough step (less than epsx)
    ae_int_t maxits = 0;

    minbleiccreate(x, state);
    minbleicsetlc(state, c, ct);                       // set linear constraints
    minbleicsetscale(state, s);                        // set variable scales
    minbleicsetcond(state, epsg, epsf, epsx, maxits);  // set stopping criteria

    // Then we activate OptGuard integrity checking.
    minbleicoptguardsmoothness(state);
    minbleicoptguardgradient(state, 0.001);

    // Optimize and evaluate results
    minbleicreport rep;
    alglib::minbleicoptimize(state, function1_grad);
    minbleicresults(state, x, rep);
    cout << "achieve min at " << x.tostring(x.length()) << endl;  // expected: [2,4]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    minbleicoptguardresults(state, ogrep);
    cout << ogrep.badgradsuspected << "," << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << endl;
}

int main() {
    box_constrained_linear_opt();
    box_constrained_linear_opt_num_diff();
    inequality_constrained_linear_opt();
}

#include <linalg.h>
#include <optimization.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * min f(x,y) = 100*(x+3)^4+(y-3)^4
 */

void function1_func(const real_1d_array &x, double &func, void *ptr) {
    func = 100 * pow(x[0] + 3, 4) + pow(x[1] - 3, 4);
}

void function1_grad(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr) {
    // this callback calculates f(x0,x1) = 100*(x0+3)^4 + (x1-3)^4 and its derivatives df/x0 and df/dx1
    func = 100 * pow(x[0] + 3, 4) + pow(x[1] - 3, 4);
    grad[0] = 400 * pow(x[0] + 3, 3);
    grad[1] = 4 * pow(x[1] - 3, 3);
}

void bfgs_method1() {
    real_1d_array x = "[0,0]";   // initial point
    real_1d_array s = "[1,1]";   // init to unit scale
    double epsg = 0;             // stop if |v|<EpsG, v is scaled gradient vector, v[i]=g[i]*s[i]
    double epsf = 0;             // stop if |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
    double epsx = 0.0000000001;  // stop if |v|<=EpsX, v is scaled step vector, v[i]=dx[i]/s[i]
    ae_int_t maxits = 0;         // maximum number of iterations
    mincgstate state;
    mincgcreate(x, state);
    mincgsetcond(state, epsg, epsf, epsx, maxits);
    mincgsetscale(state, s);

    /**
     * Activate OptGuard integrity checking
     * OptGuard helps to catch issues, like: discontinuity of the target function,
     * non-smoothness of the target function, erroneous analytic gradient
     *
     * GRADIENT VERIFICATION IS PERFORMED BY MEANS OF NUMERICAL DIFFERENTIATION. DO NOT USE IT IN PRODUCTION CODE!!!
     */
    mincgoptguardsmoothness(state);
    mincgoptguardgradient(state, 0.001);

    // Optimize and evaluate results
    mincgreport rep;
    alglib::mincgoptimize(state, function1_grad);
    mincgresults(state, x, rep);
    cout << x.tostring(x.length()) << endl;  // expected: [-3,3]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    mincgoptguardresults(state, ogrep);
    cout << ogrep.badgradsuspected << "," << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << endl;
}

/**
 * demo of below
 * 1. upper limit on step size
 * 2. restart from new point
 */
void bfgs_method2() {
    real_1d_array x = "[0,0]";   // initial point
    real_1d_array s = "[1,1]";   // init to unit scale
    double epsg = 0;             // stop if |v|<EpsG, v is scaled gradient vector, v[i]=g[i]*s[i]
    double epsf = 0;             // stop if |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
    double epsx = 0.0000000001;  // stop if |v|<=EpsX, v is scaled step vector, v[i]=dx[i]/s[i]
    double stpmax = 0.1;         // upper limit on step size
    ae_int_t maxits = 0;         // maximum number of iterations
    mincgstate state;
    mincgreport rep;

    // create and tune optimizer
    mincgcreate(x, state);
    mincgsetscale(state, s);
    mincgsetcond(state, epsg, epsf, epsx, maxits);
    mincgsetstpmax(state, stpmax);

    // Activate OptGuard integrity checking
    mincgoptguardsmoothness(state);
    mincgoptguardgradient(state, 0.001);

    // first run
    alglib::mincgoptimize(state, function1_grad);
    mincgresults(state, x, rep);
    cout << "first run result: " << x.tostring(x.length()) << endl;  // expected: [-3,3]

    // second run - algorithm is restarted with mincgrestartfrom()
    x = "[10,10]";
    mincgrestartfrom(state, x);
    alglib::mincgoptimize(state, function1_grad);
    mincgresults(state, x, rep);
    cout << "second run result: " << x.tostring(x.length()) << endl;  // expected: [-3,3]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    mincgoptguardresults(state, ogrep);
    cout << ogrep.badgradsuspected << "," << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << endl;
}

void bfgs_numdiff() {
    real_1d_array x = "[0,0]";   // initial point
    real_1d_array s = "[1,1]";   // init to unit scale
    double epsg = 0;             // stop if |v|<EpsG, v is scaled gradient vector, v[i]=g[i]*s[i]
    double epsf = 0;             // stop if |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
    double epsx = 0.0000000001;  // stop if |v|<=EpsX, v is scaled step vector, v[i]=dx[i]/s[i]
    double diffstep = 1.0e-6;
    ae_int_t maxits = 0;  // maximum number of iterations
    mincgstate state;
    mincgcreatef(x, diffstep, state);
    mincgsetcond(state, epsg, epsf, epsx, maxits);
    mincgsetscale(state, s);

    // Activate OptGuard integrity checking, Numerical differentiation always produces "correct" gradient
    mincgoptguardsmoothness(state);

    // run the optimization
    mincgreport rep;
    alglib::mincgoptimize(state, function1_func);
    mincgresults(state, x, rep);
    cout << "numerical differentiation result: " << x.tostring(x.length()) << endl;  // expected: [-3,3]

    // Check that OptGuard did not report errors, expect all false
    optguardreport ogrep;
    mincgoptguardresults(state, ogrep);
    cout << ogrep.nonc0suspected << "," << ogrep.nonc1suspected << endl;
}

int main() {
    bfgs_method1();
    bfgs_method2();
    bfgs_numdiff();
}

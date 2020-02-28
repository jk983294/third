#include <interpolation.h>
#include <linalg.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * penalized spline fitting of noisy data
 */
void linear_ls_fit() {
    real_1d_array x = "[0.00,0.10,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90]";  // abscissas
    real_1d_array y = "[0.10,0.00,0.30,0.40,0.30,0.40,0.62,0.68,0.75,0.95]";  // straight line with small noise
    ae_int_t info;
    spline1dinterpolant s;
    spline1dfitreport rep;

    /**
     * Fit with very small amount of smoothing (rho = -5.0) and large number of basis functions (M=50).
     * With such small regularization penalized spline almost fully reproduces function values
     */
    double rho = -5.0;  // amount of smoothing
    int m = 50;         // number of basis functions
    spline1dfitpenalized(x, y, m, rho, info, s, rep);
    double test_x = 0.0;
    double new_y = spline1dcalc(s, test_x);
    cout << "f(" << test_x << ") = " << new_y << endl;  // expected: 0.10

    /**
     * Fit with VERY large amount of smoothing (rho = 10.0) and large number of basis functions (M=50)
     * spline should become close to the straight line fit.
     */
    rho = +10.0;
    spline1dfitpenalized(x, y, m, rho, info, s, rep);
    test_x = 1.0;
    new_y = spline1dcalc(s, test_x);
    cout << "f(" << test_x << ") = " << new_y << endl;  // expected: 0.969

    // In real life applications you may need some moderate degree of fitting, so try to fit once more with rho=3.0.
    rho = +3.0;
    spline1dfitpenalized(x, y, m, rho, info, s, rep);
    new_y = spline1dcalc(s, test_x);
    cout << "f(" << test_x << ") = " << new_y << endl;  // expected: 1.08079
}

int main() { linear_ls_fit(); }

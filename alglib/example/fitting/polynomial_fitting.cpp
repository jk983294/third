#include <interpolation.h>
#include <linalg.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * Fitting order 1 (M=2) polynomial, f0 = 1, f1 = x
 * it just a linear fit; more complex polynomials may be used (e.g. parabolas with M=3, cubic with M=4)
 */
void linear_ls_fit() {
    real_1d_array x = "[0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0]";
    real_1d_array y = "[0.00,0.05,0.26,0.32,0.33,0.43,0.60,0.60,0.77,0.98,1.02]";
    ae_int_t m = 2;
    ae_int_t info;
    barycentricinterpolant p;
    polynomialfitreport rep;
    double new_x = 2;

    polynomialfit(x, y, m, info, p, rep);              // train model
    double new_y = barycentriccalc(p, new_x);          // use model to predict
    cout << "f(" << new_x << ") = " << new_y << endl;  // expected: 2.011

    // demonstrate weighted fitting, where second point has more weight than other ones.
    real_1d_array w = "[1,1.414213562,1,1,1,1,1,1,1,1,1]";
    real_1d_array xc = "[]";
    real_1d_array yc = "[]";
    integer_1d_array dc = "[]";
    polynomialfitwc(x, y, w, xc, yc, dc, m, info, p, rep);  // train model
    new_y = barycentriccalc(p, new_x);                      // use model to predict
    cout << "f(" << new_x << ") = " << new_y << endl;       // expected: 2.023
}

int main() { linear_ls_fit(); }

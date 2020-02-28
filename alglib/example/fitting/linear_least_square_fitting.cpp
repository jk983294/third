#include <interpolation.h>
#include <linalg.h>
#include <iostream>

using namespace alglib;
using namespace std;

/**
 * linear fitting by f(x|a) = a*x
 * fmatrix -  matrix of basis functions calculated at sample points,
 *            Actually, we have only one basis function F0 = x
 */
void linear_ls_fit() {
    real_2d_array fmatrix =
        "[[0.606531],[0.670320],[0.740818],[0.818731],[0.904837],[1.000000],[1.105171],[1.221403],[1.349859],[1.491825]"
        ",[1.648721]]";
    real_1d_array y =
        "[1.133719, 1.306522, 1.504604, 1.554663, 1.884638, 2.072436, 2.257285, 2.534068, 2.622017, 2.897713, "
        "3.219371]";
    ae_int_t info;
    real_1d_array c;  // coefficients
    lsfitreport rep;

    // Linear fitting without weights
    lsfitlinear(y, fmatrix, info, c, rep);
    cout << "status: " << info << endl;
    cout << "coefficients: " << c.tostring(c.length()) << endl;
}

/**
 * linear fitting by Ax=b
 */
void linear_ls_fit1() {
    real_2d_array A = "[[0.3,0.1],[0.4,0.2],[0.3,0.7]]";
    real_1d_array b = "[5,3,4]";
    ae_int_t info;
    real_1d_array x;  // coefficients
    lsfitreport rep;

    lsfitlinear(b, A, info, x, rep);
    cout << "status: " << info << endl;
    cout << "coefficients: " << x.tostring(x.length()) << endl;
}

int main() {
    linear_ls_fit();
    linear_ls_fit1();
}

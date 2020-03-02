#include <dataanalysis.h>
#include <iostream>

using namespace std;
using namespace alglib;

/**
 * Y = A(0)*X[0] + ... + A(N-1)*X[N-1] + A(N)
 * train data generated from y= 2*x[0] + x[1] -1
 */

int main() {
    real_2d_array XY("[[0,0,-1],[1,0,1],[2,0,3],[0,1,0],[0,2,1],[1,1,2],[1,2,3],[2,1,4],[2,2,5]]");
    ae_int_t n_points = XY.rows();
    ae_int_t n_vars = XY.cols() - 1;
    ae_int_t info;
    linearmodel lm;
    lrreport ar;

    lrbuild(XY, n_points, n_vars, info, lm, ar);
    if (info > 0) {
        real_1d_array coefficients;
        lrunpack(lm, coefficients, n_vars);
        cout << coefficients.tostring(coefficients.length()) << endl;  // [2.000,1.000,-1.000]
        cout << "intercept=" << coefficients[n_vars] << endl;          // -1
    } else {
        cout << "build lr model failed, code=" << info << endl;
    }
    return 0;
}

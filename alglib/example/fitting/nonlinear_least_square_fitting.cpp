#include <interpolation.h>
#include <linalg.h>
#include <iostream>

using namespace alglib;
using namespace std;

void function_cx_1_func(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr) {
    // this callback calculates f(c,x)=exp(-c0*sqr(x0))
    func = exp(-c[0] * pow(x[0], 2));
}

void function_cx_1_grad(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad, void *ptr) {
    // this callback calculates f(c,x)=exp(-c0*sqr(x0)) and gradient G={df/dc[i]}
    // IMPORTANT: gradient is calculated with respect to C, not to X
    func = exp(-c[0] * pow(x[0], 2));
    grad[0] = -pow(x[0], 2) * func;
}

void function_cx_1_hess(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad,
                        real_2d_array &hess, void *ptr) {
    // this callback calculates f(c,x)=exp(-c0*sqr(x0)), gradient G={df/dc[i]} and Hessian H={d2f/(dc[i]*dc[j])}
    // IMPORTANT: gradient/Hessian are calculated with respect to C, not to X
    func = exp(-c[0] * pow(x[0], 2));
    grad[0] = -pow(x[0], 2) * func;
    hess[0][0] = pow(x[0], 4) * func;
}

/**
 * exponential fitting f(x) = exp(-c*x^2)
 * using function value only, no gradient/hessian
 * Gradient is estimated using combination of numerical differences and secant updates
 */
void nonlinear_ls_fit_function_only() {
    real_2d_array x = "[[-1],[-0.8],[-0.6],[-0.4],[-0.2],[0],[0.2],[0.4],[0.6],[0.8],[1.0]]";
    real_1d_array y =
        "[0.223130, 0.382893, 0.582748, 0.786628, 0.941765, 1.000000, 0.941765, 0.786628, 0.582748, 0.382893, "
        "0.223130]";
    real_1d_array c = "[0.3]";
    double epsx = 0.000001;
    ae_int_t maxits = 0;
    ae_int_t info;
    lsfitstate state;
    lsfitreport rep;
    double diffstep = 0.0001;  // differentiation step for numerical gradient estimate

    // Fitting without weights
    lsfitcreatef(x, y, c, diffstep, state);
    lsfitsetcond(state, epsx, maxits);
    alglib::lsfitfit(state, function_cx_1_func);
    lsfitresults(state, info, c, rep);
    cout << "coefficients: " << c.tostring(c.length()) << endl;  // expected: [1.5]

    // Fitting with weights
    real_1d_array w = "[1,1,1,1,1,1,1,1,1,2,3]";
    lsfitcreatewf(x, y, w, c, diffstep, state);
    lsfitsetcond(state, epsx, maxits);
    alglib::lsfitfit(state, function_cx_1_func);
    lsfitresults(state, info, c, rep);
    cout << "fit with weight coefficients: " << c.tostring(c.length()) << endl;
}

/**
 * subject to bound constraints 0.0 <= c <= 1.0
 */
void constrained_nonlinear_ls_fit_function_only() {
    real_2d_array x = "[[-1],[-0.8],[-0.6],[-0.4],[-0.2],[0],[0.2],[0.4],[0.6],[0.8],[1.0]]";
    real_1d_array y =
        "[0.223130, 0.382893, 0.582748, 0.786628, 0.941765, 1.000000, 0.941765, 0.786628, 0.582748, 0.382893, "
        "0.223130]";
    real_1d_array c = "[0.3]";
    real_1d_array bndl = "[0.0]";
    real_1d_array bndu = "[1.0]";
    double epsx = 0.000001;
    ae_int_t maxits = 0;
    ae_int_t info;
    lsfitstate state;
    lsfitreport rep;
    double diffstep = 0.0001;  // differentiation step for numerical gradient estimate

    // Fitting without weights
    lsfitcreatef(x, y, c, diffstep, state);
    lsfitsetbc(state, bndl, bndu);
    lsfitsetcond(state, epsx, maxits);
    alglib::lsfitfit(state, function_cx_1_func);
    lsfitresults(state, info, c, rep);
    cout << "constrained coefficients: " << c.tostring(c.length()) << endl;  // expected: [1.0]
}

/**
 * exponential fitting f(x) = exp(-c*x^2)
 * using function value and gradient, no hessian
 */
void nonlinear_ls_fit_function_and_gradient() {
    real_2d_array x = "[[-1],[-0.8],[-0.6],[-0.4],[-0.2],[0],[0.2],[0.4],[0.6],[0.8],[1.0]]";
    real_1d_array y =
        "[0.223130, 0.382893, 0.582748, 0.786628, 0.941765, 1.000000, 0.941765, 0.786628, 0.582748, 0.382893, "
        "0.223130]";
    real_1d_array c = "[0.3]";
    double epsx = 0.000001;
    ae_int_t maxits = 0;
    ae_int_t info;
    lsfitstate state;
    lsfitreport rep;

    // Fitting without weights
    lsfitcreatefg(x, y, c, true, state);
    lsfitsetcond(state, epsx, maxits);
    alglib::lsfitfit(state, function_cx_1_func, function_cx_1_grad);
    lsfitresults(state, info, c, rep);
    cout << "FG mode coefficients: " << c.tostring(c.length()) << endl;  // expected: [1.5]
}

/**
 * exponential fitting f(x) = exp(-c*x^2)
 * using function value and gradient, no hessian
 */
void nonlinear_ls_fit_function_gradient_hessian() {
    real_2d_array x = "[[-1],[-0.8],[-0.6],[-0.4],[-0.2],[0],[0.2],[0.4],[0.6],[0.8],[1.0]]";
    real_1d_array y =
        "[0.223130, 0.382893, 0.582748, 0.786628, 0.941765, 1.000000, 0.941765, 0.786628, 0.582748, 0.382893, "
        "0.223130]";
    real_1d_array c = "[0.3]";
    double epsx = 0.000001;
    ae_int_t maxits = 0;
    ae_int_t info;
    lsfitstate state;
    lsfitreport rep;

    // Fitting without weights
    lsfitcreatefgh(x, y, c, state);
    lsfitsetcond(state, epsx, maxits);
    alglib::lsfitfit(state, function_cx_1_func, function_cx_1_grad, function_cx_1_hess);
    lsfitresults(state, info, c, rep);
    cout << "FGH mode coefficients: " << c.tostring(c.length()) << endl;  // expected: [1.5]
}

void function_debt_func(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr) {
    // this callback calculates f(c,x)=c[0]*(1+c[1]*(pow(x[0]-1999,c[2])-1))
    func = c[0] * (1 + c[1] * (pow(x[0] - 1999, c[2]) - 1));
}
/**
 * f(x) = c[0]*(1+c[1]*((x-1999)^c[2]-1))
 * our variables are badly scaled, such problem is difficult to solve without some kind of scaling
 * set scale of our variables to [1.0E12, 1, 1], which allows us to easily solve this problem
 * try commenting out lsfitsetscale() call - and you will see that algorithm will fail to converge
 */
void badly_scaled_fitting() {
    real_2d_array x = "[[2000],[2001],[2002],[2003],[2004],[2005],[2006],[2007],[2008]]";
    real_1d_array y =
        "[4323239600000.0, 4560913100000.0, 5564091500000.0, 6743189300000.0, 7284064600000.0, 7050129600000.0, "
        "7092221500000.0, 8483907600000.0, 8625804400000.0]";
    real_1d_array c = "[1.0e+13, 1, 1]";
    double epsx = 1.0e-5;
    // subject to bound constraints:
    real_1d_array bndl = "[-inf, -10, 0.1]";
    real_1d_array bndu = "[+inf, +10, 2.0]";
    real_1d_array s = "[1.0e+12, 1, 1]";
    ae_int_t maxits = 0;
    ae_int_t info;
    lsfitstate state;
    lsfitreport rep;
    double diffstep = 1.0e-5;

    lsfitcreatef(x, y, c, diffstep, state);
    lsfitsetcond(state, epsx, maxits);
    lsfitsetbc(state, bndl, bndu);
    lsfitsetscale(state, s);
    alglib::lsfitfit(state, function_debt_func);
    lsfitresults(state, info, c, rep);
    cout << "badly_scaled coefficients: " << c.tostring(c.length()) << endl;  // expected: [1.5]
}

int main() {
    nonlinear_ls_fit_function_only();
    nonlinear_ls_fit_function_and_gradient();
    nonlinear_ls_fit_function_gradient_hessian();
    constrained_nonlinear_ls_fit_function_only();
    badly_scaled_fitting();
}

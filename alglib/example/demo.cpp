#include <linalg.h>
#include <iostream>

using namespace std;

void array_creation();
void matrix_op();

int main() {
    array_creation();
    matrix_op();
    return 0;
}

void array_creation() {
    alglib::real_2d_array r2("[[2,3],[3,4]]");
    alglib::real_2d_array r2_1("[[]]");
    r2_1 = r2;
    alglib::real_2d_array r2_2(r2);
    cout << r2[1][1] << "," << r2_1[1][1] << "," << r2_2[1][1] << endl;

    double _content[] = {11, 12, 13, 21, 22, 23};
    alglib::real_1d_array _r1;
    alglib::real_2d_array _r2;
    _r1.setcontent(6, _content);
    _r2.setcontent(2, 3, _content);
    cout << _r1[1] << "," << _r2[1][1] << endl;

    _r1.attach_to_ptr(6, _content);
    _r2.attach_to_ptr(2, 3, _content);
    cout << _r1[1] << "," << _r2[1][1] << endl;
}

void matrix_op() {
    alglib::real_2d_array a, b, c;
    int n = 3;

    // Initialize arrays
    a.setlength(n, n);
    b.setlength(n, n);
    c.setlength(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = alglib::randomreal() - 0.5;
            b[i][j] = alglib::randomreal() - 0.5;
            c[i][j] = 0.0;
        }
    }

    // Perform matrix-matrix product.
    alglib::rmatrixgemm(n, n, n, 1.0, a, 0, 0, 0, b, 0, 0, 1, 0.0, c, 0, 0);

    for (auto i = 0; i < c.rows(); i++) {
        for (auto j = 0; j < c.cols(); j++) {
            cout << c[i][j] << ",";
        }
        cout << endl;
    }
}

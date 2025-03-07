#include <printemps/printemps.h>
#include <chrono>

int main(void) {
    /**
     * This program solves the following simple binary integer optimization
     * problem:
     * (P):  minimize  f_1 + f_2
     *          x,y
     *      subject to x_1 + x_2 + x_3              >= 2,
     *                                   y_1 + y_2   = 1,
     *                 x_1             + y_1         = 1,
     *                 x_1, x_2, x_3, y_1, y_2 \in {0, 1},
     *
     *        where    f_1 = 2 x_1 + 7 x_2 + 9 x_3 + 1,
     *                 f_2 = 5 y_1 + 6 y_2.
     */
    printemps::model::IPModel model;

    auto& x = model.create_variables("x", 3, 0, 1);
    auto& y = model.create_variables("y", 2, 0, 1);
    auto& g = model.create_constraints("g", 3);
    auto& f = model.create_expressions("f", 2);

    std::vector<int> c = {2, 7, 9};
    std::vector<int> d = {5, 6};

    f(0) = x.dot(c) + 1;
    f(1) = y.dot(d);
    g(0) = x.sum() >= 2;
    g(1) = y.selection();
    g(2) = x(0) + y(0) == 1;

    model.minimize(f.sum());

    auto t0 = std::chrono::system_clock::now();
    auto result = printemps::solver::solve(&model);
    auto t1 = std::chrono::system_clock::now();
    auto& solution = result.solution;

    if (solution.is_feasible()) {
        auto& x_vars = solution.variables("x").flat_indexed_values();
        printf("x values: %d,%d,%d\n", x_vars[0], x_vars[1], x_vars[2]);
        auto& y_vars = solution.variables("y").flat_indexed_values();
        printf("y values: %d,%d\n", y_vars[0], y_vars[1]);
        printf("objective = %f\n", solution.objective());
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
        std::cout << "time: " << duration.count() << " us\n";
        // solution.print_variable_values();
        // solution.print_expression_values();
        // solution.print_constraint_values();
        // solution.print_violation_values();
    } else {
        printf("infeasible\n");
    }

    return 0;
}
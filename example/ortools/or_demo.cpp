#include <ortools/linear_solver/linear_solver.h>
#include <chrono>

using namespace operations_research;

std::string to_string_or_variables(MPSolver* solver) {
    std::string str;
    auto& vs = solver->variables();
    for (size_t j = 0; j < vs.size(); ++j) {
        std::string tmp;
        auto* pvar = vs[j];
        tmp += "x" + std::to_string(j) + " n='" + pvar->name() + "', lb=";
        double lb_ = pvar->lb();
        if (std::isfinite(lb_)) tmp += std::to_string(std::lround(lb_));
        else tmp += std::to_string(lb_);
        tmp += ", ub=";
        double ub_ = pvar->ub();
        if (std::isfinite(ub_)) tmp += std::to_string(std::lround(ub_));
        else tmp += std::to_string(ub_);

        str += tmp;
        if (j + 1 != vs.size()) str += "\n";
    }
    return str;
}
std::string to_string_or_constraint(MPSolver* solver) {
    std::string str;
    auto& vs = solver->variables();
    auto& cs = solver->constraints();
    for (size_t i = 0; i < cs.size(); ++i) {
        std::string tmp;
        const MPConstraint* cons = cs[i];
        double lb_ = cons->lb();
        if (std::isfinite(lb_)) tmp += std::to_string(std::lround(lb_));
        else tmp += std::to_string(lb_);
        tmp += " <= ";
        for (size_t j = 0; j < vs.size(); ++j) {
            double coef = cons->GetCoefficient(vs[j]);
            tmp += std::to_string(std::lround(coef)) + " * x" + std::to_string(j);
            if (j + 1 != vs.size()) tmp += " + ";
        }
        tmp += " <= ";
        double ub_ = cons->ub();
        if (std::isfinite(ub_)) tmp += std::to_string(std::lround(ub_));
        else tmp += std::to_string(ub_);
        str += tmp;
        if (i + 1 != cs.size()) str += "\n";
    }
    return str;
}
std::string to_string_or_objective(MPSolver* solver) {
    std::string str;
    auto& vs = solver->variables();
    auto& o = solver->Objective();
    auto& terms = o.terms();
    for (size_t i = 0; i < vs.size(); ++i) {
        auto itr = terms.find(vs[i]);
        str += std::to_string(std::lround(itr->second)) + " * x" + std::to_string(i);
        if (i + 1 != vs.size()) str += " + ";
    }
    return str;
}
std::string to_string_or_result(MPSolver* solver) {
    std::string str;
    auto& vs = solver->variables();
    auto& o = solver->Objective();
    auto& terms = o.terms();
    for (size_t i = 0; i < vs.size(); ++i) {
        auto itr = terms.find(vs[i]);
        str += std::to_string(std::lround(itr->second)) + " * x" + std::to_string(i);
        if (i + 1 != vs.size()) str += " + ";
    }
    return str;
}

int main() {
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
    std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));
    const double infinity = solver->infinity();
    MPVariable* const x1 = solver->MakeIntVar(0.0, infinity, "x1");
    MPVariable* const x2 = solver->MakeIntVar(0.0, infinity, "x2");
    MPVariable* const x3 = solver->MakeIntVar(0.0, infinity, "x3");
    MPVariable* const y1 = solver->MakeIntVar(0.0, infinity, "y1");
    MPVariable* const y2 = solver->MakeIntVar(0.0, infinity, "y2");

    MPConstraint* const c0 = solver->MakeRowConstraint(-infinity, -2, "c0");
    c0->SetCoefficient(x1, -1);
    c0->SetCoefficient(x2, -1);
    c0->SetCoefficient(x3, -1);
    MPConstraint* const c1 = solver->MakeRowConstraint(1, 1, "c1");
    c1->SetCoefficient(y1, 1);
    c1->SetCoefficient(y2, 1);
    MPConstraint* const c2 = solver->MakeRowConstraint(1, 1, "c2");
    c2->SetCoefficient(x1, 1);
    c2->SetCoefficient(y1, 1);
    MPConstraint* const c3 = solver->MakeRowConstraint(0, 1, "c3");
    c3->SetCoefficient(x1, 1);
    MPConstraint* const c4 = solver->MakeRowConstraint(0, 1, "c4");
    c4->SetCoefficient(x2, 1);
    MPConstraint* const c5 = solver->MakeRowConstraint(0, 1, "c5");
    c5->SetCoefficient(x3, 1);
    MPConstraint* const c6 = solver->MakeRowConstraint(0, 1, "c6");
    c6->SetCoefficient(y1, 1);
    MPConstraint* const c7 = solver->MakeRowConstraint(0, 1, "c7");
    c7->SetCoefficient(y2, 1);

    MPObjective* const objective = solver->MutableObjective();
    objective->SetCoefficient(x1, 2);
    objective->SetCoefficient(x2, 7);
    objective->SetCoefficient(x3, 9);
    objective->SetCoefficient(y1, 5);
    objective->SetCoefficient(y2, 6);
    objective->SetMinimization();

    std::cout << "vars:\n" << to_string_or_variables(solver.get()) << std::endl;
    std::cout << "obj: " << to_string_or_objective(solver.get()) << std::endl;
    std::cout << "cons:\n" << to_string_or_constraint(solver.get()) << std::endl;

    auto t0 = std::chrono::system_clock::now();
    const MPSolver::ResultStatus result_status = solver->Solve();
    auto t1 = std::chrono::system_clock::now();
    // Check that the problem has an optimal solution.
    if (result_status != MPSolver::OPTIMAL) {
        LOG(FATAL) << "The problem does not have an optimal solution!";
    }

    if (result_status == MPSolver::INFEASIBLE || result_status == MPSolver::NOT_SOLVED) {
        printf("infeasible\n");
    } else {
        printf("Objective value = %f\n", objective->Value());
        printf("x = %f,%f,%f y=%f,%f\n", x1->solution_value(), x2->solution_value(), x3->solution_value(), 
            y1->solution_value(), y2->solution_value());
        printf("Problem solved in %ld ms\n", solver->wall_time());
        printf("Problem solved in %ld iterations\n", solver->iterations());
        printf("Problem solved in %ld branch-and-bound nodes\n", solver->nodes());
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
        std::cout << "time: " << duration.count() << " us\n";
    }
    return 0;
}
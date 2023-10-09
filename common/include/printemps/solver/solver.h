/*****************************************************************************/
// Copyright (c) 2020-2023 Yuji KOGUMA
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php
/*****************************************************************************/
#ifndef PRINTEMPS_SOLVER_H__
#define PRINTEMPS_SOLVER_H__

#include "memory.h"
#include "status.h"
#include "result.h"

#include "pdlp/controller/pdlp_controller.h"
#include "lagrange_dual/controller/lagrange_dual_controller.h"
#include "local_search/controller/local_search_controller.h"
#include "tabu_search/controller/tabu_search_controller.h"

namespace printemps::solver {
/*****************************************************************************/
template <class T_Variable, class T_Expression>
class Solver {
   private:
    model::Model<T_Variable, T_Expression>*             m_model_ptr;
    solution::IncumbentHolder<T_Variable, T_Expression> m_incumbent_holder;
    solution::DenseSolution<T_Variable, T_Expression>   m_current_solution;
    Memory<T_Variable, T_Expression>                    m_memory;
    utility::TimeKeeper                                 m_time_keeper;

    option::Option m_option_original;
    option::Option m_option;

    solution::SolutionArchive<T_Variable, T_Expression> m_solution_archive;

    std::string m_start_date_time;
    std::string m_finish_date_time;

    pdlp::controller::PDLPController<T_Variable, T_Expression>
        m_pdlp_controller;
    lagrange_dual::controller::LagrangeDualController<T_Variable, T_Expression>
        m_lagrange_dual_controller;
    local_search::controller::LocalSearchController<T_Variable, T_Expression>
        m_local_search_controller;
    tabu_search::controller::TabuSearchController<T_Variable, T_Expression>
        m_tabu_search_controller;

    /*************************************************************************/
    inline void print_program_info(const bool a_IS_ENABLED_PRINT) {
        utility::print_single_line(m_option.output.verbose >=
                                   option::verbose::Outer);
        utility::print("PRINTEMPS " + constant::VERSION + " (" +
                           constant::PROJECT_URL + ")",
                       a_IS_ENABLED_PRINT);
        utility::print("running from " + m_start_date_time, a_IS_ENABLED_PRINT);
    }

    /*************************************************************************/
    inline void setup_target_objective(void) {
        /**
         * Set default target objective value if it is not defined by the user.
         * For minimization problems, the default target value is set as -1E100.
         * For maximization problems, the default target value is set as 1E100.
         * If there is no objective function definition, the default target
         * value is set as 0 and the algorithm will be terminated if a feasible
         * solution is found.
         */
        auto target_objective_changed_rate =
            m_option.general.target_objective_value /
                option::GeneralOptionConstant::DEFAULT_TARGET_OBJECTIVE_VALUE -
            1.0;

        if (fabs(target_objective_changed_rate) > constant::EPSILON) {
            m_option.general.target_objective_value *= m_model_ptr->sign();
        }

        if (fabs(target_objective_changed_rate) < constant::EPSILON) {
            if (!m_model_ptr->is_defined_objective()) {
                m_option.general.target_objective_value = 0.0;
            }
        }
    }

    /*************************************************************************/
    inline void enable_default_neighborhood(void) {
        auto& neighborhood = m_model_ptr->neighborhood();

        if (m_option.neighborhood.is_enabled_binary_move &&
            neighborhood.binary().moves().size() > 0) {
            neighborhood.binary().enable();
        }

        if (m_option.neighborhood.is_enabled_integer_move &&
            neighborhood.integer().moves().size() > 0) {
            neighborhood.integer().enable();
        }

        if (m_option.neighborhood.is_enabled_user_defined_move) {
            neighborhood.user_defined().enable();
        }

        if (m_option.neighborhood.selection_mode !=
                option::selection_mode::Off &&
            neighborhood.selection().moves().size() > 0) {
            neighborhood.selection().enable();
        }
    }

    /*************************************************************************/
    inline Result<T_Variable, T_Expression> postprocess(void) {
        /**
         * Get the finish time.
         */
        m_finish_date_time = utility::date_time();

        /**
         * If a feasible solution is found in optimization, the incumbent
         * solution is defined by the solution with the best objective function
         * value among the feasible solutions. If no feasible solution is found,
         * the incumbent solution is substituted by solution with the best
         * augmented solution which has smallest sum of the objective function
         * value and the penalty value.
         */
        auto incumbent =
            m_incumbent_holder.is_found_feasible_solution()
                ? m_incumbent_holder.feasible_incumbent_solution()
                : m_incumbent_holder.global_augmented_incumbent_solution();

        /**
         * All value of the expressions and the constraints are updated forcibly
         * to take into account the cases they are disabled.
         */
        m_model_ptr->import_variable_values(incumbent.variable_value_proxies);
        m_model_ptr->update();
        incumbent = m_model_ptr->export_solution();

        auto named_solution = m_model_ptr->convert_to_named_solution(incumbent);

        /**
         * Prepare the result object to return.
         */
        m_time_keeper.clock();
        Status<T_Variable, T_Expression> status(this);
        Result<T_Variable, T_Expression> result(  //
            named_solution, status, m_solution_archive);

        return result;
    }

    /*************************************************************************/
    inline void run_pdlp(void) {
        m_pdlp_controller.setup(m_model_ptr,          //
                                m_current_solution,   //
                                &m_incumbent_holder,  //
                                m_time_keeper,        //
                                m_option);
        m_pdlp_controller.run();
    }

    /*************************************************************************/
    inline void run_lagrange_dual(void) {
        m_lagrange_dual_controller.setup(m_model_ptr,          //
                                         m_current_solution,   //
                                         &m_incumbent_holder,  //
                                         &m_memory,            //
                                         &m_solution_archive,  //
                                         m_time_keeper,        //
                                         m_option);
        m_lagrange_dual_controller.run();
        m_current_solution =
            m_incumbent_holder.global_augmented_incumbent_solution();
    }

    /*************************************************************************/
    inline void run_local_search(void) {
        m_local_search_controller.setup(m_model_ptr,          //
                                        m_current_solution,   //
                                        &m_incumbent_holder,  //
                                        &m_memory,            //
                                        &m_solution_archive,  //
                                        m_time_keeper,        //
                                        m_option);
        m_local_search_controller.run();
        m_current_solution =
            m_incumbent_holder.global_augmented_incumbent_solution();
    }

    /*************************************************************************/
    inline void run_tabu_search(void) {
        m_tabu_search_controller.setup(m_model_ptr,          //
                                       m_current_solution,   //
                                       &m_incumbent_holder,  //
                                       &m_memory,            //
                                       &m_solution_archive,  //
                                       m_time_keeper,        //
                                       m_option);
        m_tabu_search_controller.run();
        m_current_solution =
            m_incumbent_holder.global_augmented_incumbent_solution();
    }

   public:
    /*************************************************************************/
    Solver(void) {
        this->initialize();
    }

    /*************************************************************************/
    Solver(model::Model<T_Variable, T_Expression>* a_model_ptr,  //
           const option::Option&                   a_OPTION) {
        this->setup(a_model_ptr, a_OPTION);
    }

    /*************************************************************************/
    Solver(model::Model<T_Variable, T_Expression>* a_model_ptr,  //
           const option::Option&                   a_OPTION,     //
           const utility::TimeKeeper&              a_TIME_KEEPER) {
        this->setup(a_model_ptr, a_OPTION, a_TIME_KEEPER);
    }

    /*************************************************************************/
    ~Solver(void) {
        /// nothing to do
    }

    /*************************************************************************/
    inline void initialize(void) {
        m_model_ptr = nullptr;
        m_incumbent_holder.initialize();
        m_current_solution.initialize();
        m_memory.initialize();
        m_time_keeper.initialize();
        m_option_original.initialize();
        m_option.initialize();
        m_solution_archive.initialize();

        m_start_date_time.clear();
        m_finish_date_time.clear();

        m_pdlp_controller.initialize();
        m_lagrange_dual_controller.initialize();
        m_local_search_controller.initialize();
        m_tabu_search_controller.initialize();
    }

    /*************************************************************************/
    inline void setup(model::Model<T_Variable, T_Expression>* a_model_ptr,  //
                      const option::Option&                   a_OPTION,     //
                      const utility::TimeKeeper&              a_TIME_KEEPER) {
        this->initialize();
        m_model_ptr       = a_model_ptr;
        m_option_original = a_OPTION;
        m_option          = a_OPTION;
        m_time_keeper     = a_TIME_KEEPER;
    }

    /*************************************************************************/
    inline void setup(model::Model<T_Variable, T_Expression>* a_model_ptr,  //
                      const option::Option&                   a_OPTION) {
        this->initialize();
        m_model_ptr       = a_model_ptr;
        m_option_original = a_OPTION;
        m_option          = a_OPTION;
    }

    /*************************************************************************/
    inline void preprocess(void) {
        /**
         * Start to measure computational time and get the starting time.
         */
        if (!m_time_keeper.is_started()) {
            m_time_keeper.set_start_time();
        }

        m_start_date_time = utility::date_time();

        /**
         * Print the program name, the project url, and the starting time.
         */
        this->print_program_info(  //
            m_option.output.verbose >= option::verbose::Outer);

        /**
         * The model can be solved only once.
         */
        if (m_model_ptr->is_solved()) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "This model has already been solved."));
        } else {
            m_model_ptr->set_is_solved(true);
        }

        this->setup_target_objective();

        /**
         * Print the option value.
         */
        if (m_option.output.verbose >= option::verbose::Outer) {
            m_option.print();
        }

        /**
         * Setup the model.
         */
        m_model_ptr->setup(m_option,
                           m_option.output.verbose >= option::verbose::Outer);

        /**
         * Print the problem size.
         */
        if (m_option.output.verbose >= option::verbose::Outer) {
            m_model_ptr->print_number_of_variables();
            m_model_ptr->print_number_of_constraints();
        }

        /**
         * Disable the Chain move for the problem with no zero one_coefficient
         * constraints (set partitioning, set packing, set covering,
         * cardinality, and invariant knapsack).
         */
        if (m_option.neighborhood.is_enabled_chain_move &&
            !m_model_ptr->has_chain_move_effective_constraints()) {
            m_option.neighborhood.is_enabled_chain_move = false;
            utility::print_warning(
                "Chain move was disabled because the problem does not include "
                "any zero-one coefficient constraints (set "
                "partitioning/packing/covering, cardinality, invariant "
                "knapsack, and multiple covering).",
                m_option.output.verbose >= option::verbose::Warning);
        }

        /**
         * Set the maximum number of threads for OpenMP.
         */

#ifdef _OPENMP
        int max_number_of_threads = 1;
#pragma omp parallel
        {
#pragma omp single
            max_number_of_threads = omp_get_max_threads();
        }

        if (m_option.parallel.number_of_threads_evaluation <= 0) {
            m_option.parallel.number_of_threads_evaluation =
                max_number_of_threads;
        }

        if (m_option.parallel.number_of_threads_neighborhood_update <= 0) {
            m_option.parallel.number_of_threads_neighborhood_update =
                max_number_of_threads;
        }
#else
        m_option.parallel.number_of_threads_evaluation          = 1;
        m_option.parallel.number_of_threads_neighborhood_update = 1;
#endif

        /**
         * Enables the default neighborhood moves. Special neighborhood moves
         * will be enabled when optimization stagnates.
         */
        this->enable_default_neighborhood();

        /**
         * Set local and global penalty coefficient for each constraint.
         */
        for (auto&& proxy : m_model_ptr->constraint_proxies()) {
            for (auto&& constraint : proxy.flat_indexed_constraints()) {
                constraint.reset_local_penalty_coefficient();
            }
        }

        /**
         * Compute the initial dual bound by naive method.
         */
        m_incumbent_holder.update_dual_bound(
            m_model_ptr->compute_naive_dual_bound());

        /**
         * Create memory which stores updating count for each variable.
         */
        m_memory.setup(m_model_ptr);

        /**
         * Prepare feasible solutions archive.
         */
        m_solution_archive.setup(
            m_option.output.feasible_solutions_capacity,  //
            m_model_ptr->is_minimization(),               //
            m_model_ptr->name(),                          //
            m_model_ptr->number_of_variables(),           //
            m_model_ptr->number_of_constraints());

        /**
         * Forcibly disable fast neighborhood evaluation by option. The fast
         * evaluation should not be disabled except for debugging and
         * performance evaluation.
         */
        if (!m_option.general.is_enabled_fast_evaluation) {
            m_model_ptr->disable_fast_evaluation();
        }

        /**
         * Compute the values of expressions, constraints, and the objective
         * function according to the initial solution.
         */
        m_model_ptr->update();

        /**
         * Update the state.
         */
        m_current_solution = m_model_ptr->export_solution();
        m_incumbent_holder.try_update_incumbent(m_current_solution,
                                                m_model_ptr->evaluate({}));
    }

    /*************************************************************************/
    inline Result<T_Variable, T_Expression> solve(void) {
        /**
         * Preprocessing; setup the model and the solver.
         */
        this->preprocess();

        /**
         * Start optimization.
         */
        utility::print_single_line(  //
            m_option.output.verbose >= option::verbose::Outer);

        utility::print_message(  //
            "Optimization starts.",
            m_option.output.verbose >= option::verbose::Outer);

        /**
         * Solve relaxed LP to obtain a dual bound (Optional).
         */
        if (m_option.pdlp.is_enabled) {
            this->run_pdlp();
        }

        /**
         * Solve Lagrange dual to obtain a better initial solution (Optional).
         */
        if (m_option.lagrange_dual.is_enabled) {
            this->run_lagrange_dual();
        }

        /**
         * Run a local search to improve the initial solution (optional).
         */
        if (m_option.local_search.is_enabled) {
            this->run_local_search();
        }

        /**
         * Run tabu searches to find better solutions.
         */
        this->run_tabu_search();

        /**
         * Postprocessing; create the result object.
         */
        auto result = this->postprocess();

        return result;
    }

    /*************************************************************************/
    inline std::unordered_map<std::string, multi_array::ValueProxy<double>>
    export_named_penalty_coefficients(void) {
        std::unordered_map<std::string, multi_array::ValueProxy<double>>
            named_penalty_coefficients;

        auto local_penalty_coefficient_proxies =
            m_model_ptr->export_local_penalty_coefficient_proxies();

        const int CONSTRAINT_PROXIES_SIZE =
            m_model_ptr->constraint_proxies().size();
        const auto& CONSTRAIN_NAMED = m_model_ptr->constraint_names();
        for (auto i = 0; i < CONSTRAINT_PROXIES_SIZE; i++) {
            named_penalty_coefficients[CONSTRAIN_NAMED[i]] =
                local_penalty_coefficient_proxies[i];
        }
        return named_penalty_coefficients;
    }

    /*************************************************************************/
    inline std::unordered_map<std::string, multi_array::ValueProxy<int>>
    export_named_update_counts(void) {
        std::unordered_map<std::string, multi_array::ValueProxy<int>>
                    named_update_counts;
        const int   PROXIES_SIZE   = m_model_ptr->variable_proxies().size();
        const auto& VARIABLE_NAMES = m_model_ptr->variable_names();
        const auto& COUNTS         = m_memory.update_counts();
        for (auto i = 0; i < PROXIES_SIZE; i++) {
            named_update_counts[VARIABLE_NAMES[i]] = COUNTS[i];
        }
        return named_update_counts;
    }

    /*************************************************************************/
    inline std::unordered_map<std::string, multi_array::ValueProxy<int>>
    export_named_violation_counts(void) {
        std::unordered_map<std::string, multi_array::ValueProxy<int>>
                    named_violation_counts;
        const int   PROXIES_SIZE     = m_model_ptr->constraint_proxies().size();
        const auto& CONSTRAINT_NAMES = m_model_ptr->constraint_names();
        const auto& COUNTS           = m_memory.violation_counts();
        for (auto i = 0; i < PROXIES_SIZE; i++) {
            named_violation_counts[CONSTRAINT_NAMES[i]] = COUNTS[i];
        }
        return named_violation_counts;
    }

    /*************************************************************************/
    inline model::Model<T_Variable, T_Expression>* model_ptr(void) {
        return m_model_ptr;
    }

    /*************************************************************************/
    inline const option::Option& option_original(void) const {
        return m_option_original;
    }

    /*************************************************************************/
    inline const option::Option& option(void) const {
        return m_option;
    }

    /*************************************************************************/
    inline const solution::IncumbentHolder<T_Variable, T_Expression>&
    incumbent_holder(void) const {
        return m_incumbent_holder;
    }

    /*************************************************************************/
    inline const solution::DenseSolution<T_Variable, T_Expression>&
    current_solution(void) const {
        return m_current_solution;
    }

    /*************************************************************************/
    inline const Memory<T_Variable, T_Expression>& memory(void) const {
        return m_memory;
    }

    /*************************************************************************/
    inline const utility::TimeKeeper& time_keeper(void) const {
        return m_time_keeper;
    }

    /*************************************************************************/
    inline const solution::SolutionArchive<T_Variable, T_Expression>&
    solution_archive(void) const {
        return m_solution_archive;
    }

    /*************************************************************************/
    inline const std::string& start_date_time(void) const {
        return m_start_date_time;
    }

    /*************************************************************************/
    inline const std::string& finish_date_time(void) const {
        return m_finish_date_time;
    }

    /*************************************************************************/
    inline const pdlp::controller::PDLPController<T_Variable, T_Expression>&
    pdlp_controller(void) const {
        return m_pdlp_controller;
    }

    /*************************************************************************/
    inline const lagrange_dual::controller::LagrangeDualController<
        T_Variable, T_Expression>&
    lagrange_dual_controller(void) const {
        return m_lagrange_dual_controller;
    }

    /*************************************************************************/
    inline const local_search::controller::LocalSearchController<T_Variable,
                                                                 T_Expression>&
    local_search_controller(void) const {
        return m_local_search_controller;
    }

    /*************************************************************************/
    inline const tabu_search::controller::TabuSearchController<T_Variable,
                                                               T_Expression>&
    tabu_search_controller(void) const {
        return m_tabu_search_controller;
    }
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
inline Result<T_Variable, T_Expression> solve(
    model::Model<T_Variable, T_Expression>* a_model_ptr,  //
    const option::Option&                   a_OPTION) {
    Solver<T_Variable, T_Expression> solver(a_model_ptr, a_OPTION);
    return solver.solve();
}

/*****************************************************************************/
template <class T_Variable, class T_Expression>
inline Result<T_Variable, T_Expression> solve(
    model::Model<T_Variable, T_Expression>* a_model_ptr) {
    option::Option option;
    return solve(a_model_ptr, option);
}
using IPSolver = Solver<int, double>;
}  // namespace printemps::solver

#endif
/*****************************************************************************/
// END
/*****************************************************************************/
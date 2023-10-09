/*****************************************************************************/
// Copyright (c) 2020-2023 Yuji KOGUMA
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php
/*****************************************************************************/
#ifndef PRINTEMPS_SOLVER_TABU_SEARCH_CORE_RESULT_H__
#define PRINTEMPS_SOLVER_TABU_SEARCH_CORE_RESULT_H__

namespace printemps::solver::tabu_search::core {
/*****************************************************************************/
template <class T_Variable, class T_Expression>
struct TabuSearchCoreResult {
    int    total_update_status;
    int    number_of_iterations;
    long   number_of_updated_moves;
    long   number_of_evaluated_moves;
    double elapsed_time;
    double elapsed_time_for_evaluating_moves;
    double elapsed_time_for_updating_moves;

    TabuSearchCoreTerminationStatus termination_status;

    int tabu_tenure;
    int last_local_augmented_incumbent_update_iteration;
    int last_global_augmented_incumbent_update_iteration;
    int last_feasible_incumbent_update_iteration;

    bool is_few_permissible_neighborhood;
    bool is_found_new_feasible_solution;

    double objective_constraint_rate;
    double global_augmented_objective_range;
    double performance;

    option::Option option;

    /*************************************************************************/
    TabuSearchCoreResult(void) {
        this->initialize();
    }

    /*************************************************************************/
    TabuSearchCoreResult(
        const TabuSearchCoreState<T_Variable, T_Expression> &a_STATE,
        const option::Option &                               a_OPTION) {
        this->setup(a_STATE, a_OPTION);
    }

    /*************************************************************************/
    inline void initialize(void) {
        this->total_update_status               = 0;
        this->number_of_iterations              = 0;
        this->number_of_updated_moves           = 0;
        this->number_of_evaluated_moves         = 0;
        this->elapsed_time                      = 0.0;
        this->elapsed_time_for_evaluating_moves = 0.0;
        this->elapsed_time_for_updating_moves   = 0.0;

        this->termination_status =
            TabuSearchCoreTerminationStatus::ITERATION_OVER;

        this->tabu_tenure                                      = 0;
        this->last_local_augmented_incumbent_update_iteration  = -1;
        this->last_global_augmented_incumbent_update_iteration = -1;
        this->last_feasible_incumbent_update_iteration         = -1;

        this->is_few_permissible_neighborhood = false;
        this->is_found_new_feasible_solution  = false;

        this->objective_constraint_rate        = 1.0;
        this->global_augmented_objective_range = 0.0;
        this->performance                      = 0.0;

        this->option.initialize();
    }

    /*************************************************************************/
    inline void setup(
        const TabuSearchCoreState<T_Variable, T_Expression> &a_STATE,
        const option::Option &                               a_OPTION) {
        this->total_update_status       = a_STATE.total_update_status;
        this->number_of_iterations      = a_STATE.iteration;
        this->number_of_updated_moves   = a_STATE.number_of_updated_moves;
        this->number_of_evaluated_moves = a_STATE.number_of_evaluated_moves;

        this->elapsed_time = a_STATE.elapsed_time;
        this->elapsed_time_for_updating_moves =
            a_STATE.elapsed_time_for_updating_moves;
        this->elapsed_time_for_evaluating_moves =
            a_STATE.elapsed_time_for_evaluating_moves;

        this->termination_status = a_STATE.termination_status;
        this->tabu_tenure        = a_STATE.tabu_tenure;
        this->last_local_augmented_incumbent_update_iteration =
            a_STATE.last_local_augmented_incumbent_update_iteration;
        this->last_global_augmented_incumbent_update_iteration =
            a_STATE.last_global_augmented_incumbent_update_iteration;
        this->last_feasible_incumbent_update_iteration =
            a_STATE.last_feasible_incumbent_update_iteration;
        this->is_few_permissible_neighborhood =
            a_STATE.is_few_permissible_neighborhood;
        this->is_found_new_feasible_solution =
            a_STATE.is_found_new_feasible_solution;

        const double OBJECTIVE_CONSTRAINT_RATE =
            std::max(1.0, std::max(a_STATE.objective_range.max_abs(),
                                   a_STATE.objective_range.range())) /
            std::max(1.0, a_STATE.local_penalty_range.min());

        const double PERFORMANCE =
            static_cast<double>(a_STATE.number_of_effective_updates) /
            a_STATE.iteration;

        this->objective_constraint_rate = OBJECTIVE_CONSTRAINT_RATE;
        this->global_augmented_objective_range =
            a_STATE.global_augmented_objective_range.range();
        this->performance = PERFORMANCE;

        this->option = a_OPTION;
    }
};
}  // namespace printemps::solver::tabu_search::core
#endif
/*****************************************************************************/
// END
/*****************************************************************************/
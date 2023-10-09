/*****************************************************************************/
// Copyright (c) 2020-2023 Yuji KOGUMA
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php
/*****************************************************************************/
#ifndef PRINTEMPS_OPTION_NEIGHBORHOOD_OPTION_H__
#define PRINTEMPS_OPTION_NEIGHBORHOOD_OPTION_H__

namespace printemps::option {
/*****************************************************************************/
struct NeighborhoodOptionConstant {
    static constexpr bool DEFAULT_IS_ENABLED_BINARY_MOVE                = true;
    static constexpr bool DEFAULT_IS_ENABLED_INTEGER_MOVE               = true;
    static constexpr bool DEFAULT_IS_ENABLED_EXCLUSIVE_OR_MOVE          = true;
    static constexpr bool DEFAULT_IS_ENABLED_EXCLUSIVE_NOR_MOVE         = true;
    static constexpr bool DEFAULT_IS_ENABLED_INVERTED_INTEGERS_MOVE     = true;
    static constexpr bool DEFAULT_IS_ENABLED_BALANCED_INTEGERS_MOVE     = true;
    static constexpr bool DEFAULT_IS_ENABLED_CONSTANT_SUM_INTEGERS_MOVE = true;
    static constexpr bool DEFAULT_IS_ENABLED_CONSTANT_DIFFERENCE_INTEGERS_MOVE =
        true;
    static constexpr bool DEFAULT_IS_ENABLED_CONSTANT_RATIO_INTEGERS_MOVE =
        true;
    static constexpr bool DEFAULT_IS_ENABLED_AGGREGATION_MOVE    = true;
    static constexpr bool DEFAULT_IS_ENABLED_PRECEDENCE_MOVE     = false;
    static constexpr bool DEFAULT_IS_ENABLED_VARIABLE_BOUND_MOVE = false;
    static constexpr bool DEFAULT_IS_ENABLED_TRINOMIAL_EXCLUSIVE_NOR_MOVE =
        false;
    static constexpr bool DEFAULT_IS_ENABLED_SOFT_SELECTION_MOVE = false;
    static constexpr bool DEFAULT_IS_ENABLED_CHAIN_MOVE          = true;
    static constexpr bool DEFAULT_IS_ENABLED_TWO_FLIP_MOVE       = false;
    static constexpr bool DEFAULT_IS_ENABLED_USER_DEFINED_MOVE   = false;
    static constexpr int  DEFAULT_CHAIN_MOVE_CAPACITY            = 100000;
    static constexpr chain_move_reduce_mode::ChainMoveReduceMode
        DEFAULT_CHAIN_MOVE_REDUCE_MODE = chain_move_reduce_mode::OverlapRate;

    static constexpr double DEFAULT_CHAIN_MOVE_OVERLAP_RATE_THRESHOLD = 0.2;

    static constexpr selection_mode::SelectionMode DEFAULT_SELECTION_MODE =
        selection_mode::Independent;

    static constexpr improvability_screening_mode::ImprovabilityScreeningMode
        DEFAULT_IMPROVABILITY_SCREENING_MODE =
            improvability_screening_mode::Automatic;
    static constexpr bool DEFAULT_IS_ENABLED_INTEGER_STEP_SIZE_ADJUSTER = false;
};

/*****************************************************************************/
struct NeighborhoodOption {
    bool is_enabled_binary_move;
    bool is_enabled_integer_move;
    bool is_enabled_exclusive_or_move;
    bool is_enabled_exclusive_nor_move;
    bool is_enabled_inverted_integers_move;
    bool is_enabled_balanced_integers_move;
    bool is_enabled_constant_sum_integers_move;
    bool is_enabled_constant_difference_integers_move;
    bool is_enabled_constant_ratio_integers_move;
    bool is_enabled_aggregation_move;
    bool is_enabled_precedence_move;
    bool is_enabled_variable_bound_move;
    bool is_enabled_trinomial_exclusive_nor_move;
    bool is_enabled_soft_selection_move;
    bool is_enabled_chain_move;
    bool is_enabled_two_flip_move;
    bool is_enabled_user_defined_move;

    int                                         chain_move_capacity;
    chain_move_reduce_mode::ChainMoveReduceMode chain_move_reduce_mode;
    double chain_move_overlap_rate_threshold;

    selection_mode::SelectionMode selection_mode;
    improvability_screening_mode::ImprovabilityScreeningMode
        improvability_screening_mode;

    bool is_enabled_integer_step_size_adjuster;

    /*************************************************************************/
    NeighborhoodOption(void) {
        this->initialize();
    }

    /*************************************************************************/
    NeighborhoodOption(const utility::json::JsonObject &a_OBJECT) {
        this->setup(a_OBJECT);
    }

    /*************************************************************************/
    void initialize(void) {
        this->is_enabled_binary_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_BINARY_MOVE;
        this->is_enabled_integer_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_INTEGER_MOVE;
        this->is_enabled_exclusive_or_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_EXCLUSIVE_OR_MOVE;
        this->is_enabled_exclusive_nor_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_EXCLUSIVE_NOR_MOVE;
        this->is_enabled_inverted_integers_move = NeighborhoodOptionConstant::
            DEFAULT_IS_ENABLED_INVERTED_INTEGERS_MOVE;
        this->is_enabled_balanced_integers_move = NeighborhoodOptionConstant::
            DEFAULT_IS_ENABLED_BALANCED_INTEGERS_MOVE;
        this->is_enabled_constant_sum_integers_move =
            NeighborhoodOptionConstant::
                DEFAULT_IS_ENABLED_CONSTANT_SUM_INTEGERS_MOVE;
        this->is_enabled_constant_difference_integers_move =
            NeighborhoodOptionConstant::
                DEFAULT_IS_ENABLED_CONSTANT_DIFFERENCE_INTEGERS_MOVE;
        this->is_enabled_constant_ratio_integers_move =
            NeighborhoodOptionConstant::
                DEFAULT_IS_ENABLED_CONSTANT_RATIO_INTEGERS_MOVE;
        this->is_enabled_aggregation_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_AGGREGATION_MOVE;
        this->is_enabled_precedence_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_PRECEDENCE_MOVE;
        this->is_enabled_variable_bound_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_VARIABLE_BOUND_MOVE;
        this->is_enabled_trinomial_exclusive_nor_move =
            NeighborhoodOptionConstant::
                DEFAULT_IS_ENABLED_TRINOMIAL_EXCLUSIVE_NOR_MOVE;
        this->is_enabled_soft_selection_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_SOFT_SELECTION_MOVE;
        this->is_enabled_chain_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_CHAIN_MOVE;
        this->is_enabled_two_flip_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_TWO_FLIP_MOVE;
        this->is_enabled_user_defined_move =
            NeighborhoodOptionConstant::DEFAULT_IS_ENABLED_USER_DEFINED_MOVE;
        this->chain_move_capacity =
            NeighborhoodOptionConstant::DEFAULT_CHAIN_MOVE_CAPACITY;
        this->chain_move_reduce_mode =
            NeighborhoodOptionConstant::DEFAULT_CHAIN_MOVE_REDUCE_MODE;
        this->chain_move_overlap_rate_threshold = NeighborhoodOptionConstant::
            DEFAULT_CHAIN_MOVE_OVERLAP_RATE_THRESHOLD;
        this->selection_mode =
            NeighborhoodOptionConstant::DEFAULT_SELECTION_MODE;
        this->improvability_screening_mode =
            NeighborhoodOptionConstant::DEFAULT_IMPROVABILITY_SCREENING_MODE;
        this->is_enabled_integer_step_size_adjuster =
            NeighborhoodOptionConstant::
                DEFAULT_IS_ENABLED_INTEGER_STEP_SIZE_ADJUSTER;
    }

    /*************************************************************************/
    void print(void) const {
        utility::print(                                    //
            " -- neighborhood.is_enabled_binary_move: " +  //
            utility::to_true_or_false(                     //
                this->is_enabled_binary_move));

        utility::print(                                     //
            " -- neighborhood.is_enabled_integer_move: " +  //
            utility::to_true_or_false(                      //
                this->is_enabled_integer_move));

        utility::print(                                          //
            " -- neighborhood.is_enabled_exclusive_or_move: " +  //
            utility::to_true_or_false(                           //
                this->is_enabled_exclusive_or_move));

        utility::print(                                           //
            " -- neighborhood.is_enabled_exclusive_nor_move: " +  //
            utility::to_true_or_false(                            //
                this->is_enabled_exclusive_nor_move));

        utility::print(                                               //
            " -- neighborhood.is_enabled_inverted_integers_move: " +  //
            utility::to_true_or_false(                                //
                this->is_enabled_inverted_integers_move));

        utility::print(                                               //
            " -- neighborhood.is_enabled_balanced_integers_move: " +  //
            utility::to_true_or_false(                                //
                this->is_enabled_balanced_integers_move));

        utility::print(                                                   //
            " -- neighborhood.is_enabled_constant_sum_integers_move: " +  //
            utility::to_true_or_false(                                    //
                this->is_enabled_constant_sum_integers_move));

        utility::print(  //
            " -- neighborhood.is_enabled_constant_difference_integers_move: " +  //
            utility::to_true_or_false(  //
                this->is_enabled_constant_difference_integers_move));

        utility::print(                                                     //
            " -- neighborhood.is_enabled_constant_ratio_integers_move: " +  //
            utility::to_true_or_false(                                      //
                this->is_enabled_constant_ratio_integers_move));

        utility::print(                                         //
            " -- neighborhood.is_enabled_aggregation_move: " +  //
            utility::to_true_or_false(                          //
                this->is_enabled_aggregation_move));

        utility::print(                                        //
            " -- neighborhood.is_enabled_precedence_move: " +  //
            utility::to_true_or_false(                         //
                this->is_enabled_precedence_move));

        utility::print(                                            //
            " -- neighborhood.is_enabled_variable_bound_move: " +  //
            utility::to_true_or_false(                             //
                this->is_enabled_variable_bound_move));

        utility::print(                                                     //
            " -- neighborhood.is_enabled_trinomial_exclusive_nor_move: " +  //
            utility::to_true_or_false(                                      //
                this->is_enabled_trinomial_exclusive_nor_move));

        utility::print(                                            //
            " -- neighborhood.is_enabled_soft_selection_move: " +  //
            utility::to_true_or_false(                             //
                this->is_enabled_soft_selection_move));

        utility::print(                                   //
            " -- neighborhood.is_enabled_chain_move: " +  //
            utility::to_true_or_false(                    //
                this->is_enabled_chain_move));

        utility::print(                                      //
            " -- neighborhood.is_enabled_two_flip_move: " +  //
            utility::to_true_or_false(                       //
                this->is_enabled_two_flip_move));

        utility::print(                                          //
            " -- neighborhood.is_enabled_user_defined_move: " +  //
            utility::to_true_or_false(                           //
                this->is_enabled_user_defined_move));

        utility::print(                                 //
            " -- neighborhood.chain_move_capacity: " +  //
            utility::to_string(                         //
                this->chain_move_capacity, "%d"));

        utility::print(                                    //
            " -- neighborhood.chain_move_reduce_mode: " +  //
            chain_move_reduce_mode::ChainMoveReduceModeInverseMap.at(
                this->chain_move_reduce_mode));

        utility::print(                                               //
            " -- neighborhood.chain_move_overlap_rate_threshold: " +  //
            utility::to_string(                                       //
                this->chain_move_overlap_rate_threshold, "%f"));

        utility::print(                            //
            " -- neighborhood.selection_mode: " +  //
            selection_mode::SelectionModeInverseMap.at(this->selection_mode));

        utility::print(                             //
            " -- improvability_screening_mode: " +  //
            improvability_screening_mode::ImprovabilityScreeningModeInverseMap
                .at(this->improvability_screening_mode));

        utility::print(                                      //
            " -- is_enabled_integer_step_size_adjuster: " +  //
            utility::to_true_or_false(                       //
                this->is_enabled_integer_step_size_adjuster));
    }

    /**************************************************************************/
    inline void setup(const utility::json::JsonObject &a_OBJECT) {
        this->initialize();

        read_json(                          //
            &this->is_enabled_binary_move,  //
            "is_enabled_binary_move", a_OBJECT);

        read_json(                           //
            &this->is_enabled_integer_move,  //
            "is_enabled_integer_move", a_OBJECT);

        read_json(                                //
            &this->is_enabled_exclusive_or_move,  //
            "is_enabled_exclusive_or_move", a_OBJECT);

        read_json(                                 //
            &this->is_enabled_exclusive_nor_move,  //
            "is_enabled_exclusive_nor_move", a_OBJECT);

        read_json(                                     //
            &this->is_enabled_inverted_integers_move,  //
            "is_enabled_inverted_integers_move", a_OBJECT);

        read_json(                                     //
            &this->is_enabled_balanced_integers_move,  //
            "is_enabled_balanced_integers_move", a_OBJECT);

        read_json(                                         //
            &this->is_enabled_constant_sum_integers_move,  //
            "is_enabled_constant_sum_integers_move", a_OBJECT);

        read_json(                                                //
            &this->is_enabled_constant_difference_integers_move,  //
            "is_enabled_constant_difference_integers_move", a_OBJECT);

        read_json(                                           //
            &this->is_enabled_constant_ratio_integers_move,  //
            "is_enabled_constant_ratio_integers_move", a_OBJECT);

        read_json(                               //
            &this->is_enabled_aggregation_move,  //
            "is_enabled_aggregation_move", a_OBJECT);

        read_json(                              //
            &this->is_enabled_precedence_move,  //
            "is_enabled_precedence_move", a_OBJECT);

        read_json(                                  //
            &this->is_enabled_variable_bound_move,  //
            "is_enabled_variable_bound_move", a_OBJECT);

        read_json(                                           //
            &this->is_enabled_trinomial_exclusive_nor_move,  //
            "is_enabled_trinomial_exclusive_nor_move", a_OBJECT);

        read_json(                                  //
            &this->is_enabled_soft_selection_move,  //
            "is_enabled_soft_selection_move", a_OBJECT);

        read_json(                         //
            &this->is_enabled_chain_move,  //
            "is_enabled_chain_move", a_OBJECT);

        read_json(                            //
            &this->is_enabled_two_flip_move,  //
            "is_enabled_two_flip_move", a_OBJECT);

        read_json(                                //
            &this->is_enabled_user_defined_move,  //
            "is_enabled_user_defined_move", a_OBJECT);

        read_json(                       //
            &this->chain_move_capacity,  //
            "chain_move_capacity", a_OBJECT);

        read_json(                          //
            &this->chain_move_reduce_mode,  //
            "chain_move_reduce_mode", a_OBJECT);

        read_json(                                     //
            &this->chain_move_overlap_rate_threshold,  //
            "chain_move_overlap_rate_threshold", a_OBJECT);

        read_json(                  //
            &this->selection_mode,  //
            "selection_mode", a_OBJECT);

        read_json(                                //
            &this->improvability_screening_mode,  //
            "improvability_screening_mode", a_OBJECT);

        read_json(                                         //
            &this->is_enabled_integer_step_size_adjuster,  //
            "is_enabled_integer_step_size_adjuster", a_OBJECT);
    }

    /**************************************************************************/
    inline utility::json::JsonObject to_json(void) const {
        utility::json::JsonObject obj;
        obj.emplace_back(              //
            "is_enabled_binary_move",  //
            this->is_enabled_binary_move);

        obj.emplace_back(               //
            "is_enabled_integer_move",  //
            this->is_enabled_integer_move);

        obj.emplace_back(                    //
            "is_enabled_exclusive_or_move",  //
            this->is_enabled_exclusive_or_move);

        obj.emplace_back(                     //
            "is_enabled_exclusive_nor_move",  //
            this->is_enabled_exclusive_nor_move);

        obj.emplace_back(                         //
            "is_enabled_inverted_integers_move",  //
            this->is_enabled_inverted_integers_move);

        obj.emplace_back(                         //
            "is_enabled_balanced_integers_move",  //
            this->is_enabled_balanced_integers_move);

        obj.emplace_back(                             //
            "is_enabled_constant_sum_integers_move",  //
            this->is_enabled_constant_sum_integers_move);

        obj.emplace_back(                                    //
            "is_enabled_constant_difference_integers_move",  //
            this->is_enabled_constant_difference_integers_move);

        obj.emplace_back(                               //
            "is_enabled_constant_ratio_integers_move",  //
            this->is_enabled_constant_ratio_integers_move);

        obj.emplace_back(                   //
            "is_enabled_aggregation_move",  //
            this->is_enabled_aggregation_move);

        obj.emplace_back(                  //
            "is_enabled_precedence_move",  //
            this->is_enabled_precedence_move);

        obj.emplace_back(                      //
            "is_enabled_variable_bound_move",  //
            this->is_enabled_variable_bound_move);

        obj.emplace_back(                               //
            "is_enabled_trinomial_exclusive_nor_move",  //
            this->is_enabled_trinomial_exclusive_nor_move);

        obj.emplace_back(                      //
            "is_enabled_soft_selection_move",  //
            this->is_enabled_soft_selection_move);

        obj.emplace_back(             //
            "is_enabled_chain_move",  //
            this->is_enabled_chain_move);

        obj.emplace_back(                //
            "is_enabled_two_flip_move",  //
            this->is_enabled_two_flip_move);

        obj.emplace_back(                    //
            "is_enabled_user_defined_move",  //
            this->is_enabled_user_defined_move);

        obj.emplace_back(           //
            "chain_move_capacity",  //
            this->chain_move_capacity);

        obj.emplace_back(              //
            "chain_move_reduce_mode",  //
            chain_move_reduce_mode::ChainMoveReduceModeInverseMap.at(
                this->chain_move_reduce_mode));

        obj.emplace_back(                         //
            "chain_move_overlap_rate_threshold",  //
            this->chain_move_overlap_rate_threshold);

        obj.emplace_back(      //
            "selection_mode",  //
            selection_mode::SelectionModeInverseMap.at(this->selection_mode));

        obj.emplace_back(                    //
            "improvability_screening_mode",  //
            improvability_screening_mode::ImprovabilityScreeningModeInverseMap
                .at(this->improvability_screening_mode));

        obj.emplace_back(                             //
            "is_enabled_integer_step_size_adjuster",  //
            this->is_enabled_integer_step_size_adjuster);

        return obj;
    }
};
}  // namespace printemps::option

#endif
/*****************************************************************************/
// END
/*****************************************************************************/
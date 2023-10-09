/*****************************************************************************/
// Copyright (c) 2020-2023 Yuji KOGUMA
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php
/*****************************************************************************/
#ifndef PRINTEMPS_NEIGHBORHOOD_MOVE_H__
#define PRINTEMPS_NEIGHBORHOOD_MOVE_H__

namespace printemps::neighborhood {
/*****************************************************************************/
template <class T_Variable, class T_Expression>
using Alteration =
    std::pair<model_component::Variable<T_Variable, T_Expression> *,
              T_Variable>;

/*****************************************************************************/
template <class T_Variable, class T_Expression>
struct Move {
    std::vector<Alteration<T_Variable, T_Expression>> alterations;
    MoveSense                                         sense;
    std::vector<model_component::Constraint<T_Variable, T_Expression> *>
        related_constraint_ptrs;

    /**
     * The following two members are for Chain moves.
     */
    std::uint_fast64_t hash;
    double             overlap_rate;

    bool is_univariable_move;
    bool is_selection_move;

    /**
     * The following two members are for special neighborhood moves.
     */
    bool is_special_neighborhood_move;
    bool is_available;

    /*************************************************************************/
    Move(void) {
        this->initialize();
    }

    /*************************************************************************/
    inline void initialize(void) {
        this->alterations.clear();
        this->related_constraint_ptrs.clear();
        this->sense                        = MoveSense::General;
        this->hash                         = 0;
        this->overlap_rate                 = 0.0;
        this->is_univariable_move          = false;
        this->is_selection_move            = false;
        this->is_special_neighborhood_move = false;
        this->is_available                 = true;
    }
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool has_fixed_variable(
    const Move<T_Variable, T_Expression> &a_MOVE) {
    for (const auto &alteration : a_MOVE.alterations) {
        if (alteration.first->is_fixed()) {
            return true;
        }
    }
    return false;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool has_selection_variable(
    const Move<T_Variable, T_Expression> &a_MOVE) {
    for (const auto &alteration : a_MOVE.alterations) {
        if (alteration.first->sense() ==
            model_component::VariableSense::Selection) {
            return true;
        }
    }
    return false;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool has_bound_violation(
    const Move<T_Variable, T_Expression> &a_MOVE) {
    for (const auto &alteration : a_MOVE.alterations) {
        if (alteration.second < alteration.first->lower_bound()) {
            return true;
        }
        if (alteration.second > alteration.first->upper_bound()) {
            return true;
        }
    }
    return false;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool has_objective_improvable_variable(
    const Move<T_Variable, T_Expression> &a_MOVE) {
    for (const auto &alteration : a_MOVE.alterations) {
        if (alteration.first->is_objective_improvable()) {
            return true;
        }
    }
    return false;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool has_feasibility_improvable_variable(
    const Move<T_Variable, T_Expression> &a_MOVE) {
    for (const auto &alteration : a_MOVE.alterations) {
        if (alteration.first->is_feasibility_improvable()) {
            return true;
        }
    }
    return false;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool has_feasibility_not_improvable_variable(
    const Move<T_Variable, T_Expression> &a_MOVE) {
    for (const auto &alteration : a_MOVE.alterations) {
        if (!alteration.first->is_feasibility_improvable()) {
            return true;
        }
    }
    return false;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool has_duplicate_variable(
    const neighborhood::Move<T_Variable, T_Expression> &a_MOVE) {
    auto &    alterations      = a_MOVE.alterations;
    const int ALTERATIONS_SIZE = alterations.size();
    for (auto i = 0; i < ALTERATIONS_SIZE; i++) {
        for (auto j = i + 1; j < ALTERATIONS_SIZE; j++) {
            if (alterations[i].first == alterations[j].first) {
                return true;
            }
        }
    }
    return false;
}

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr double compute_overlap_rate(
    const std::vector<Alteration<T_Variable, T_Expression>> &a_ALTERATIONS) {
    auto &union_ptrs_vector =
        a_ALTERATIONS.front()
            .first->related_binary_coefficient_constraint_ptrs();

    std::unordered_set<model_component::Constraint<T_Variable, T_Expression> *>
        union_ptrs(union_ptrs_vector.begin(), union_ptrs_vector.end());

    if (union_ptrs.size() == 0) {
        return 0.0;
    }

    auto intersection_ptrs = union_ptrs;

    const int ALTERATIONS_SIZE = a_ALTERATIONS.size();
    for (auto i = 1; i < ALTERATIONS_SIZE; i++) {
        auto &related_constraint_ptrs_vector =
            a_ALTERATIONS[i]
                .first->related_binary_coefficient_constraint_ptrs();
        std::unordered_set<
            model_component::Constraint<T_Variable, T_Expression> *>
            related_constraint_ptrs(related_constraint_ptrs_vector.begin(),
                                    related_constraint_ptrs_vector.end());

        utility::update_union_set(  //
            &union_ptrs, related_constraint_ptrs);
        utility::update_intersection_set(  //
            &intersection_ptrs, related_constraint_ptrs);
    }

    /**
     * If the union of related constraints is empty, the overlap rate is set 0.
     * Otherwise, the overlap rate is computed bu (#intersection / #union)
     * ^{1/(#alterations -1)}, where # denotes the number of elements in a set.
     */
    return pow(static_cast<double>(intersection_ptrs.size()) /
                   static_cast<double>(union_ptrs.size()),
               1.0 / (a_ALTERATIONS.size() - 1));
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr double compute_hash(
    const std::vector<Alteration<T_Variable, T_Expression>> &a_ALTERATIONS) {
    /**
     * NOTE: Chain moves will be sorted in descending order by overlap_ratio to
     * apply std::unique()in Neighborhood.deduplicate_chain_move().A hash is
     * calculated to check the necessary condition that two moves are identical.
     */

    std::uint_fast64_t hash = 0;
    for (const auto &alteration : a_ALTERATIONS) {
        hash = hash ^ reinterpret_cast<std::uint_fast64_t>(alteration.first);
    }
    return hash;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool is_binary_swap(const Move<T_Variable, T_Expression> &a_MOVE) {
    for (const auto &alteration : a_MOVE.alterations) {
        if (alteration.first->sense() !=
            model_component::VariableSense::Binary) {
            return false;
        }
    }
    return true;
}

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr std::vector<model_component::Variable<T_Variable, T_Expression> *>
related_variable_ptrs_vector(const Move<T_Variable, T_Expression> &a_MOVE) {
    std::vector<model_component::Variable<T_Variable, T_Expression> *> result;
    for (const auto &alteration : a_MOVE.alterations) {
        result.push_back(alteration.first);
    }
    return result;
}

/*****************************************************************************/
template <class T_Variable, class T_Expression>
void sort_and_unique_related_constraint_ptrs(
    Move<T_Variable, T_Expression> *a_move_ptr) {
    std::stable_sort(a_move_ptr->related_constraint_ptrs.begin(),
                     a_move_ptr->related_constraint_ptrs.end(),
                     [](const auto &a_FIRST, const auto &a_SECOND) {
                         return a_FIRST->name() < a_SECOND->name();
                     });

    a_move_ptr->related_constraint_ptrs.erase(
        std::unique(a_move_ptr->related_constraint_ptrs.begin(),  //
                    a_move_ptr->related_constraint_ptrs.end()),
        a_move_ptr->related_constraint_ptrs.end());
}

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr Move<T_Variable, T_Expression> operator+(
    const Move<T_Variable, T_Expression> &a_MOVE_FIRST,
    const Move<T_Variable, T_Expression> &a_MOVE_SECOND) {
    auto result = a_MOVE_FIRST;

    result.alterations.insert(result.alterations.end(),
                              a_MOVE_SECOND.alterations.begin(),
                              a_MOVE_SECOND.alterations.end());

    result.related_constraint_ptrs.insert(
        result.related_constraint_ptrs.end(),
        a_MOVE_SECOND.related_constraint_ptrs.begin(),
        a_MOVE_SECOND.related_constraint_ptrs.end());

    result.sense                        = MoveSense::Chain;
    result.is_univariable_move          = false;
    result.is_available                 = false;
    result.is_special_neighborhood_move = true;

    result.overlap_rate = compute_overlap_rate(result.alterations);
    result.hash         = compute_hash(result.alterations);

    sort_and_unique_related_constraint_ptrs(&result);

    return result;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool operator==(const Move<T_Variable, T_Expression> &a_MOVE_FIRST,
                          const Move<T_Variable, T_Expression> &a_MOVE_SECOND) {
    /**
     * If the numbers of alterations of two moves are different, they
     * must be different.
     */
    if (a_MOVE_FIRST.alterations.size() != a_MOVE_SECOND.alterations.size()) {
        return false;
    }

    /**
     * If the numbers of related constraints of two moves are different, they
     * must be different.
     */
    if (a_MOVE_FIRST.related_constraint_ptrs.size() !=
        a_MOVE_SECOND.related_constraint_ptrs.size()) {
        return false;
    }

    /**
     * If the hashes of two moves are different, they must be different.
     */
    if (a_MOVE_FIRST.hash != a_MOVE_SECOND.hash) {
        return false;
    }

    /**
     * If the overlap_rates including hashes of two moves are different, they
     * are likely to be different. See compute_hash() for detail.
     */
    if (fabs(a_MOVE_FIRST.overlap_rate - a_MOVE_SECOND.overlap_rate) >
        constant::EPSILON_10) {
        return false;
    }

    /**
     * Otherwise, check the variables included in two moves. Moves including
     * same variables but different in their order, are regarded as different
     * moves.
     */
    const int ALTERATIONS_SIZE = a_MOVE_FIRST.alterations.size();

    for (auto i = 0; i < ALTERATIONS_SIZE; i++) {
        if (a_MOVE_FIRST.alterations[i] != a_MOVE_SECOND.alterations[i]) {
            return false;
        }
    }

    return true;
};

/*****************************************************************************/
template <class T_Variable, class T_Expression>
constexpr bool operator!=(const Move<T_Variable, T_Expression> &a_MOVE_FIRST,
                          const Move<T_Variable, T_Expression> &a_MOVE_SECOND) {
    return !(a_MOVE_FIRST == a_MOVE_SECOND);
};

using IPMove = Move<int, double>;
}  // namespace printemps::neighborhood
#endif
/*****************************************************************************/
// END
/*****************************************************************************/
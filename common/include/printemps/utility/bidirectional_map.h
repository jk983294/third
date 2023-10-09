/*****************************************************************************/
// Copyright (c) 2020-2023 Yuji KOGUMA
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php
/*****************************************************************************/
#ifndef PRINTEMPS_UTILITY_BIDIRECTIONAL_MAP_H__
#define PRINTEMPS_UTILITY_BIDIRECTIONAL_MAP_H__

namespace printemps::utility {
/*****************************************************************************/
template <class T1, class T2>
class BidirectionalMap {
   private:
    std::unordered_map<T1, T2> m_forward;
    std::unordered_map<T2, T1> m_reverse;

   public:
    /*************************************************************************/
    BidirectionalMap(void) {
        this->initialize();
    }

    /*************************************************************************/
    inline void initialize(void) {
        m_forward.clear();
        m_reverse.clear();
    }

    /*************************************************************************/
    inline constexpr int size(void) const {
        return m_forward.size();
    }

    /*************************************************************************/
    inline constexpr bool empty(void) const {
        return m_forward.empty() && m_reverse.empty();
    }

    /*************************************************************************/
    inline constexpr void insert(const T1 &a_FIRST, const T2 &a_SECOND) {
        m_forward[a_FIRST]  = a_SECOND;
        m_reverse[a_SECOND] = a_FIRST;
    }

    /*************************************************************************/
    inline constexpr const T2 &forward_at(const T1 a_KEY) const {
        return m_forward.at(a_KEY);
    }

    /*************************************************************************/
    inline constexpr const T1 &reverse_at(const T2 a_KEY) const {
        return m_reverse.at(a_KEY);
    }

    /*************************************************************************/
    inline constexpr const std::unordered_map<T1, T2> &forward(void) const {
        return m_forward;
    }

    /*************************************************************************/
    inline constexpr const std::unordered_map<T2, T1> &reverse(void) const {
        return m_reverse;
    }
};
}  // namespace printemps::utility

#endif
/*****************************************************************************/
// END
/*****************************************************************************/
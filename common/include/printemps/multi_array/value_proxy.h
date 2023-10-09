/*****************************************************************************/
// Copyright (c) 2020-2023 Yuji KOGUMA
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php
/*****************************************************************************/

#ifndef PRINTEMPS_MULTI_ARRAY_VALUE_PROXY_H__
#define PRINTEMPS_MULTI_ARRAY_VALUE_PROXY_H__

#include "abstract_multi_array.h"

namespace printemps::multi_array {
/*****************************************************************************/
template <class T_Value>
class ValueProxy : public AbstractMultiArray {
   private:
    std::vector<T_Value>     m_values;
    std::vector<std::string> m_names;

   public:
    /*************************************************************************/
    ValueProxy(void) {
        /// nothing to do
    }

    /*************************************************************************/
    ValueProxy(const int a_ID) : AbstractMultiArray(a_ID) {
        m_values.resize(m_number_of_elements);
        m_names.resize(m_number_of_elements);
    }

    /*************************************************************************/
    ValueProxy(const int a_ID, const int a_NUMBER_OF_ELEMENTS)
        : AbstractMultiArray(a_ID, a_NUMBER_OF_ELEMENTS) {
        m_values.resize(m_number_of_elements);
        m_names.resize(m_number_of_elements);
    }

    /*************************************************************************/
    ValueProxy(const int a_ID, const std::vector<int> &a_SHAPE)
        : AbstractMultiArray(a_ID, a_SHAPE) {
        m_values.resize(m_number_of_elements);
        m_names.resize(m_number_of_elements);
    }

    /*************************************************************************/
    inline constexpr T_Value &flat_indexed_values(const int a_FLAT_INDEX) {
        return m_values[a_FLAT_INDEX];
    }

    /*************************************************************************/
    inline constexpr T_Value flat_indexed_values(const int a_FLAT_INDEX) const {
        return m_values[a_FLAT_INDEX];
    }

    /*************************************************************************/
    inline constexpr std::vector<T_Value> &flat_indexed_values(void) {
        return m_values;
    }

    /*************************************************************************/
    inline constexpr const std::vector<T_Value> &flat_indexed_values(
        void) const {
        return m_values;
    }

    /*************************************************************************/
    inline constexpr std::string &flat_indexed_names(const int a_FLAT_INDEX) {
        return m_names[a_FLAT_INDEX];
    }

    /*************************************************************************/
    inline constexpr const std::string &flat_indexed_names(
        const int a_FLAT_INDEX) const {
        return m_names[a_FLAT_INDEX];
    }

    /*************************************************************************/
    inline constexpr std::vector<std::string> &flat_indexed_names(void) {
        return m_names;
    }

    /*************************************************************************/
    inline constexpr const std::vector<std::string> &flat_indexed_names(
        void) const {
        return m_names;
    }

    /*************************************************************************/
    inline constexpr T_Value &value(void) {
        if (this->number_of_elements() != 1) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of elements is not one."));
        }
        return m_values[0];
    }

    /*************************************************************************/
    inline constexpr T_Value value(void) const {
        if (this->number_of_elements() != 1) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of elements is not one."));
        }
        return m_values[0];
    }

    /*************************************************************************/
    inline constexpr T_Value &values(
        const std::vector<int> &a_MULTI_DIMENSIONAL_INDEX) {
        int MULTI_DIMENSIONAL_INDEX_SIZE = a_MULTI_DIMENSIONAL_INDEX.size();
        if (this->number_of_dimensions() != MULTI_DIMENSIONAL_INDEX_SIZE) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of dimensions does not match."));
        }

        auto flat_index = std::inner_product(a_MULTI_DIMENSIONAL_INDEX.begin(),
                                             a_MULTI_DIMENSIONAL_INDEX.end(),
                                             m_strides.begin(), 0);
        return m_values[flat_index];
    }

    /*************************************************************************/
    inline constexpr T_Value values(
        const std::vector<int> &a_MULTI_DIMENSIONAL_INDEX) const {
        int MULTI_DIMENSIONAL_INDEX_SIZE = a_MULTI_DIMENSIONAL_INDEX.size();
        if (this->number_of_dimensions() != MULTI_DIMENSIONAL_INDEX_SIZE) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of dimensions does not match."));
        }

        auto flat_index = std::inner_product(a_MULTI_DIMENSIONAL_INDEX.begin(),
                                             a_MULTI_DIMENSIONAL_INDEX.end(),
                                             m_strides.begin(), 0);
        return m_values[flat_index];
    }

    /*************************************************************************/
    template <class... Args>
    inline constexpr T_Value &values(Args... args) {
        return this->values({args...});
    }

    /*************************************************************************/
    template <class... Args>
    inline constexpr T_Value values(Args... args) const {
        return this->values({args...});
    }

    /*************************************************************************/
    inline constexpr std::string &name(void) {
        if (this->number_of_elements() != 1) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of elements is not one."));
        }
        return m_names[0];
    }

    /*************************************************************************/
    inline constexpr const std::string &name(void) const {
        if (this->number_of_elements() != 1) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of elements is not one."));
        }
        return m_names[0];
    }

    /*************************************************************************/
    inline constexpr std::string &names(
        const std::vector<int> &a_MULTI_DIMENSIONAL_INDEX) {
        if (this->number_of_dimensions() != a_MULTI_DIMENSIONAL_INDEX.size()) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of dimensions does not match."));
        }

        auto flat_index = std::inner_product(a_MULTI_DIMENSIONAL_INDEX.begin(),
                                             a_MULTI_DIMENSIONAL_INDEX.end(),
                                             m_strides.begin(), 0);
        return m_names[flat_index];
    }

    /*************************************************************************/
    inline constexpr const std::string &names(
        const std::vector<int> &a_MULTI_DIMENSIONAL_INDEX) const {
        if (this->number_of_dimensions() != a_MULTI_DIMENSIONAL_INDEX.size()) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of dimensions does not match."));
        }

        auto flat_index = std::inner_product(a_MULTI_DIMENSIONAL_INDEX.begin(),
                                             a_MULTI_DIMENSIONAL_INDEX.end(),
                                             m_strides.begin(), 0);
        return m_names[flat_index];
    }

    /*************************************************************************/
    template <class... Args>
    inline constexpr std::string &names(Args... args) {
        return this->names({args...});
    }

    /*************************************************************************/
    template <class... Args>
    inline constexpr const std::string &names(Args... args) const {
        /// This method cannot be constexpr for Clang-6.
        return this->names({args...});
    }

    /*************************************************************************/
    inline constexpr void fill(const T_Value a_VALUE) {
        for (auto &&value : m_values) {
            value = a_VALUE;
        }
    }

    /*************************************************************************/
    inline constexpr ValueProxy<T_Value> operator=(const T_Value a_VALUE) {
        if (this->number_of_elements() != 1) {
            throw std::logic_error(utility::format_error_location(
                __FILE__, __LINE__, __func__,
                "The number of elements is not one."));
        }
        m_values[0] = a_VALUE;
        return *this;
    }

    /*************************************************************************/
    inline constexpr T_Value &operator[](const int a_FLAT_INDEX) {
        return m_values[a_FLAT_INDEX];
    }

    /*************************************************************************/
    inline constexpr T_Value operator[](const int a_FLAT_INDEX) const {
        return m_values[a_FLAT_INDEX];
    }

    /*************************************************************************/
    template <class... Args>
    inline constexpr T_Value &operator()(Args... args) {
        return this->values({args...});
    }

    /*************************************************************************/
    template <class... Args>
    inline constexpr T_Value operator()(Args... args) const {
        return this->values({args...});
    }
};

/*****************************************************************************/
template <class T_Value>
inline constexpr bool operator==(const ValueProxy<T_Value> &a_LEFT,
                                 const ValueProxy<T_Value> &a_RIGHT) {
    return a_LEFT.flat_indexed_values() == a_RIGHT.flat_indexed_values();
}

/*****************************************************************************/
template <class T_Value>
inline constexpr bool operator!=(const ValueProxy<T_Value> &a_LEFT,
                                 const ValueProxy<T_Value> &a_RIGHT) {
    return !(a_LEFT == a_RIGHT);
}

/*****************************************************************************/
template <class T_Value>
inline void print_values(
    const std::unordered_map<std::string, ValueProxy<T_Value>> a_VALUE_PROXIES,
    const std::string &                                        a_CATEGORY) {
    for (const auto &item : a_VALUE_PROXIES) {
        auto &proxy              = item.second;
        int   number_of_elements = proxy.number_of_elements();
        for (auto i = 0; i < number_of_elements; i++) {
            utility::print(a_CATEGORY + "." + proxy.flat_indexed_names(i) +
                           " = " +
                           std::to_string(proxy.flat_indexed_values(i)));
        }
    }
}

/*****************************************************************************/
template <class T_Value>
utility::json::JsonObject create_json_object(
    const std::unordered_map<std::string, ValueProxy<T_Value>>
        &a_VALUE_PROXIES) {
    utility::json::JsonObject object;

    for (const auto &item : a_VALUE_PROXIES) {
        auto &    proxy              = item.second;
        const int NUMBER_OF_ELEMENTS = proxy.number_of_elements();
        for (auto i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            object.emplace_back(proxy.flat_indexed_names(i),
                                proxy.flat_indexed_values(i));
        }
    }
    return object;
}

/*****************************************************************************/
template <class T_Value>
utility::json::JsonObject create_json_array(
    const std::unordered_map<std::string, ValueProxy<T_Value>>
        &a_VALUE_PROXIES) {
    /**
     * NOTE: This method creates a JSON object that contains the values in
     * a_VALUE_PROXY as arrays by following steps:
     * (1) Create a JSON-like format string.
     * (2) Parse the string with utility::json::parse_json_object().
     * In step (1), generated string is not
     * valid JSON, where the separators comma and colon are omitted.
     */
    std::string str = " { ";
    for (const auto &item : a_VALUE_PROXIES) {
        auto &    proxy                = item.second;
        const int NUMBER_OF_ELEMENTS   = proxy.number_of_elements();
        const int NUMBER_OF_DIMENSIONS = proxy.number_of_dimensions();
        int       dimension            = 0;
        str += "\"" + item.first + "\" ";
        str += "[ ";
        for (auto i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            const auto INDEX = proxy.multi_dimensional_index(i);
            for (auto j = dimension; j < NUMBER_OF_DIMENSIONS - 1; j++) {
                if (INDEX[j + 1] == 0) {
                    str += "[ ";
                    dimension++;
                } else {
                    break;
                }
            }

            str += std::to_string(proxy.flat_indexed_values(i)) + " ";

            for (auto j = dimension; j > 0; j--) {
                if (INDEX[j] == proxy.shape()[j] - 1) {
                    str += "] ";
                    dimension--;
                } else {
                    break;
                }
            }
        }
        str += "] ";
    }
    str += "}";
    return utility::json::parse_json_object(str);
}
}  // namespace printemps::multi_array
#endif

/*****************************************************************************/
// END
/*****************************************************************************/

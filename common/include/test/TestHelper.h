#pragma once

#include <cmath>
#include <string>
#include <vector>

constexpr double epsilon = 1e-6;
constexpr int default_least = 1;
constexpr double default_fill = NAN;

template <typename T>
bool IsValidData(T value) {
    return std::isfinite(value) && !std::isnan(value);
}

template <typename T1, typename T2>
bool FloatEqual(T1 a, T2 b) {
    if (IsValidData(a) && IsValidData(b)) {
        return std::fabs(a - b) < epsilon;
    } else if (std::isnan(a) && std::isnan(b)) {
        return true;
    } else if (!std::isfinite(a) && !std::isfinite(b)) {
        return true;
    } else {
        return false;
    }
}

template <typename T1, typename T2>
bool FloatEqual(const std::vector<T1>& a, const std::vector<T2>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (!FloatEqual(a[i], b[i])) return false;
    }
    return true;
}

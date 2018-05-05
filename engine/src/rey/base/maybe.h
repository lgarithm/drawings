#pragma once
#include <optional>

template <typename T> std::optional<T> nothing() { return {}; }

template <typename T> std::optional<T> just(const T &it) { return it; }

#define inject(m, f) (m.has_value() ? f(m.value()) : m)


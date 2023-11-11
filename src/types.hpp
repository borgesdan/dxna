#ifndef DXNA_TYPES_HPP
#define DXNA_TYPES_HPP

#include <vector>
#include <memory>

template <typename T>
using vectorptr = std::shared_ptr<std::vector<T>>;

#endif
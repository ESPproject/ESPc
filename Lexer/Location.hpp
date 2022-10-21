#pragma once

#include <cstddef>

namespace ESP {

struct Location {
    size_t offset_;
    size_t row_;
    size_t col_;

    Location() : offset_(0), row_(0), col_(0) {}
    Location(size_t offset, size_t row, size_t col) : offset_(offset), row_(row), col_(col) {}
};

}  // namespace ESP
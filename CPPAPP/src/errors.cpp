#include "../include/errors.hpp"
#include <cstdint>
#include <string>

StringException stringErrors::index_out_of_bounds(int64_t index, int64_t lb, int64_t ub)
{
    std::string msg = "Index out of bounds: " + std::to_string(index) + " not in [" + std::to_string(lb) + ", " + std::to_string(ub) + "]";
    return StringException(StringErrorCode::INDEX_OUT_OF_BOUNDS, msg.c_str());
}
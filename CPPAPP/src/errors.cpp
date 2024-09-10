#include "../include/errors.hpp"

StringException stringErrors::index_out_of_bounds(int64_t index, int64_t length)
{
    return StringException(StringErrorCode::INDEX_OUT_OF_BOUNDS, "Index out of bounds");
}
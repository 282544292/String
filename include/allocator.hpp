#pragma once
#include <cstddef>
#include <stdexcept>

namespace memory
{
template <typename T> T *zalloc(size_t count)
{
    // TODO
    void *ptr = calloc(count, sizeof(T));
    if (!ptr)
    {
        throw std::runtime_error("calloc failed");
    }

    return static_cast<T *>(ptr);
}

template <typename T> void memcpy(void *dst, void *src, size_t count)
{
    std::memcpy(dst, src, count * sizeof(T));
}
} // namespace memory
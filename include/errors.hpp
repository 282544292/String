#pragma once
#include <cstdint>
#include <exception>
#include <string>

enum class StringErrorCode {
  INDEX_OUT_OF_BOUNDS,
};

class StringException : public std::exception {
public:
  StringException(StringErrorCode code, const char *msg) : _code(code), _msg(std::string(msg)) {}
  const char *what() const noexcept override { return _msg.c_str(); }

private:
  StringErrorCode _code;
  std::string _msg;
};

namespace stringErrors {
    StringException index_out_of_bounds(int64_t index, int64_t lb, int64_t ub);
} // namespace stringErrors

#ifndef FORMATED_STRING_HPP_PIX
#define FORMATED_STRING_HPP_PIX

#include <stdarg.h>  // For va_start, etc.
#include <cstring> //strcpy
#include <vector>
#include <memory>    // For std::unique_ptr

std::string string_format(const std::string fmt_str, ...);

const std::vector<std::string> explode(const std::string& s, const char& c);

#endif // FORMATED_STRING_HPP_PIX
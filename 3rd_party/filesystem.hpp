#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
#include <sys/stat.h>


// Everything here is taken from kind souls at StackOverflow, didn't got the names when I had to.

std::vector<std::string> filesInDir(const std::string& folder, bool absolute = false);
std::vector<std::string> filesInDirFilter(const std::string& folder, const std::string& filter);

inline bool exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0);
}

std::string dirname_st(const std::string& path);
std::string basename_st(const std::string& path);

#endif //FILESYSTEM_H
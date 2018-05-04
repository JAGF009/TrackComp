#ifndef __CONFIG_FILE_H__
#define __CONFIG_FILE_H__

#include <string>
#include <map>

// #include "Chameleon.hpp"

class ConfigFile {
  std::map<std::string,std::string> content_;

public:
  ConfigFile(std::string const& configFile);

  std::string const& Value(std::string const& section, std::string const& entry) const;

  std::string const& Value(std::string const& section, std::string const& entry, double value);
  std::string const& Value(std::string const& section, std::string const& entry, std::string const& value);
};

#endif
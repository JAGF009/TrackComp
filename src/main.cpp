#include <iostream>
// #include <sstream>
#include <string>
#include <vector>
#include "../STRUCK/BasicConfig.hpp"


int main(int argc, char** argv)
{
    std::vector<std::string> features {"haar gaussian 0.2", "histogram gaussian 0.1", "haar linear"};
    auto configurationString = buildBasicConf("run/to/the/hills", "baby", features);
    std::string line;
    while (getline(configurationString, line))
    {
        std::cout << line << '\n';
    }
    std::cout << std::endl;
    return 0;
}
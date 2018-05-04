#include <iostream>
#include <string>
#include "../STRUCK/BasicConfig.hpp"


int main(int argc, char** argv)
{

    auto a = buildBasicConf("run/to/the/hills", "baby", "", "these are the features I like");
    std::string line;
    while (getline(a, line))
    {
        std::cout << line << '\n';
    }
    std::cout << std::endl;
    return 0;
}
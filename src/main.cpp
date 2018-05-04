#include <iostream>
// #include <sstream>
#include <string>
#include <vector>
#include "../STRUCK/BasicConfig.hpp"
#include "TrackerStruck.hpp"


int main(int argc, char** argv)
{
    auto configurationString = buildBasicConf("run/to/the/hills", "baby", {"haar gaussian 0.2", "histogram gaussian 0.1", "haar linear"});
    TrackerStruck track(configurationString);
    return 0;
}
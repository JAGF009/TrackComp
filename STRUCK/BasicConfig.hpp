#ifndef BASICCONFIG_H_ST
#define BASICCONFIG_H_ST
#include <sstream>

void add(std::ostream& ss, const std::string& key, const std::string& value)
{
    if (!value.empty())
        ss << key << " = " << value << '\n';
}

std::stringstream buildBasicConf(const std::string& sPath, const std::string& sName,
                                 const std::string& rPath, const std::string& features,
                                 const std::string& fWidth = "320", const std::string& fHeight = "240",
                                 const std::string& quietMode = "0", const std::string& debugMode = "1",
                                 const std::string& seed = "0", const std::string& sRadius = "30",
                                 const std::string& svmC = "100.0", const std::string& bSize = "100")

{
    std::stringstream ss;
    add(ss, "quietMode", quietMode);
    add(ss, "debugMode", debugMode);
    add(ss, "sequenceBasePath", sPath);
    add(ss, "resultsPath", rPath);
    add(ss, "sequenceName", sName);
    add(ss, "frameWidth", fWidth);
    add(ss, "frameHeight", fHeight);
    add(ss, "seed", seed);
    add(ss, "searchRadius", sRadius);
    add(ss, "svmC", svmC);
    add(ss, "svmBudgetSize", bSize);
    return ss;    
}


#endif
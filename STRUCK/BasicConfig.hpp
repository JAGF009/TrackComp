#ifndef BASICCONFIG_H_ST
#define BASICCONFIG_H_ST

#include <sstream>
#include <vector>

void _addConf(std::ostream& ss, const std::string& key, const std::string& value)
{
    if (!value.empty())
        ss << key << " = " << value << '\n';
}

/*
image features to use.
format is: feature kernel [kernel-params]
where:
  feature = haar/raw/histogram
  kernel = gaussian/linear/intersection/chi2
  for kernel=gaussian, kernel-params is sigma
multiple features can be specified and will be combined
feature = haar gaussian 0.2
#feature = raw gaussian 0.1
#feature = histogram intersection
*/

std::stringstream buildBasicConf(const std::string& sPath, const std::string& sName,
                                 const std::vector<std::string>& features, const std::string& rPath = "",
                                 const std::string& fWidth = "320", const std::string& fHeight = "240",
                                 const std::string& quietMode = "0", const std::string& debugMode = "0",
                                 const std::string& seed = "0", const std::string& sRadius = "30",
                                 const std::string& svmC = "100.0", const std::string& bSize = "100")

{
    std::stringstream ss;
    _addConf(ss, "quietMode", quietMode);
    _addConf(ss, "debugMode", debugMode);
    _addConf(ss, "sequenceBasePath", sPath);
    _addConf(ss, "resultsPath", rPath);
    _addConf(ss, "sequenceName", sName);
    _addConf(ss, "frameWidth", fWidth);
    _addConf(ss, "frameHeight", fHeight);
    _addConf(ss, "seed", seed);
    _addConf(ss, "searchRadius", sRadius);
    _addConf(ss, "svmC", svmC);
    _addConf(ss, "svmBudgetSize", bSize);
    for (auto feat: features) _addConf(ss, "feature", feat);
    return ss;    
}


#endif
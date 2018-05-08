#ifndef BASICCONFIG_H_ST
#define BASICCONFIG_H_ST

#include <sstream>
#include <vector>

void add(std::ostream& ss, const std::string& key, const std::string& value)
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
    for (auto feat: features) add(ss, "feature", feat);
    return ss;    
}


#endif
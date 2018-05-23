#ifndef ENUM_CONST_HPP__
#define ENUM_CONST_HPP__

#include <string>

namespace pix
{
enum class DBType
{
    VOC,
    MOT17,
    VOT17
};
enum class TrackerType
{
    STRUCK,
    Re3,
    OpenCV_TLD,
    OpenCV_KCF,
    OpenCV_MF,
    OpenCV_BOOSTING,
    OpenCV_MIL
};

struct TermStyle
{
    std::string swarning(const std::string& m) { return this->FAIL + m + this->ENDC; }
    std::string sfatal(const std::string& m) { return this->FAIL + this->BOLD + m + this->ENDC;}
    private:
        const std::string ENDL{"\n"};
        const std::string TAB{"\t"};
        const std::string HEADER{"\033[95m"};
        const std::string OKBLUE{"\033[94m"};
        const std::string OKGREEN{"\033[92m"};
        const std::string WARNING{"\033[93m"};
        const std::string FAIL{"\033[91m"};
        const std::string ENDC{"\033[0m"};
        const std::string BOLD{"\033[1m"};
        const std::string UNDERLINE{"\033[4m"};
        
};
        
} // namespace pix

#endif // ENUM_CONST_HPP__
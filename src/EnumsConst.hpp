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
        
} // namespace pix

#endif
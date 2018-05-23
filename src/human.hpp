#ifndef HUMAN_PIX_HPP
#define HUMAN_PIX_HPP

#include <string>
#include "EnumsConst.hpp"

bool iequals(const std::string& a, const std::string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}


std::string show_user(pix::TrackerType tt)
{
    ::std::string s{""};
    switch (tt){
        case pix::TrackerType::STRUCK: 
            s = "STRUCK";
            break;
        case pix::TrackerType::Re3:
            s = "Re3";
            break;
        case pix::TrackerType::OpenCV_TLD:
            s = "TLD";
            break;
        case pix::TrackerType::OpenCV_KCF:
            s = "KCF";
            break;
        case pix::TrackerType::OpenCV_MF:
            s = "MedianFlow";
            break;
        case pix::TrackerType::OpenCV_BOOSTING:
            s = "Boosting";
            break;
        case pix::TrackerType::OpenCV_MIL:
            s = "MIL";
            break;
        }
    return s;
}

std::string show_user(pix::DBType dbt)
{
    ::std::string s{""};
    switch(dbt)
    {
        case pix::DBType::VOC: 
            s = "VOC";
            break;
        case pix::DBType::MOT17: 
            s = "MOT";
            break;
        case pix::DBType::VOT17:
            s = "VOT";
            break;
        default: 
            s = "VOC";
    }
    return s;
}

pix::TrackerType from_user_t(const std::string& s)
{
    pix::TrackerType tt;
    if (iequals(s, "STRUCK"))
        tt = pix::TrackerType::STRUCK;
    else if (iequals(s, "Re3"))
        tt = pix::TrackerType::Re3;
    else if (iequals(s, "KCF"))
        tt = pix::TrackerType::OpenCV_KCF;
    else if (iequals(s, "MIL"))
        tt = pix::TrackerType::OpenCV_MIL;
    else if (iequals(s, "MedianFlow") || iequals(s, "MF"))
        tt = pix::TrackerType::OpenCV_MF;
    else if (iequals(s, "TLD"))
        tt = pix::TrackerType::OpenCV_TLD;
    else if (iequals(s, "BOOSTING"))
        tt = pix::TrackerType::OpenCV_BOOSTING;
    else
    {
        std::cout << "TRACKER SPECIFIED NOT KNOWN:" << s << " USING STRUCK." << std::endl;
        tt = pix::TrackerType::STRUCK;
    }
        
    return tt;
}

pix::DBType from_user_db(const std::string& s)
{
    pix::DBType dbt;
    if (iequals(s, "VOC") || iequals(s, "PIX"))
        dbt = pix::DBType::VOC;
    else if (iequals(s, "MOT") || iequals(s, "MOT17"))
        dbt = pix::DBType::MOT17;
    else if (iequals(s, "VOT") || iequals(s, "VOT17"))
        dbt = pix::DBType::VOT17;
    else
    {
        std::cout << "DATA BASE SPECIFIED NOT KNOWN:" << s << " USING VOC/PIX." << std::endl;
        dbt = pix::DBType::VOC;
    }
        
    return dbt;
}

#endif // HUMAN_PIX_HPP
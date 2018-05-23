#include "Factory.hpp"

#include <iostream>

//  TRACKERS
#include "../STRUCK/BasicConfig.hpp"
#include "TrackerStruck.hpp"
#include "TrackerOpenCV.hpp"
#include "TrackerRe3.hpp"

//  DBReader

#include "PIXReader.hpp"
#include "MOTReader.hpp"



std::unique_ptr<pix::TrackerInterface> pix::make_tracker(pix::TrackerType tt)
{
    std::unique_ptr<pix::TrackerInterface> p;
    switch (tt)
    {
    case pix::TrackerType::STRUCK:
    {
        auto iss = buildBasicConf(
            "", "", {"haar gaussian 0.2"});
        p = std::make_unique<TrackerStruck>(iss);
        break;
    }
    case pix::TrackerType::Re3:
        p = std::make_unique<TrackerRe3>();
        break;
    case pix::TrackerType::OpenCV_TLD:
    case pix::TrackerType::OpenCV_KCF:
    case pix::TrackerType::OpenCV_MF:
    case pix::TrackerType::OpenCV_BOOSTING:
    case pix::TrackerType::OpenCV_MIL:
        p = std::make_unique<pix::TrackerOpenCV>(tt);
        break;
    default:
        p = nullptr;
        break;
    }
    return p;
}

std::unique_ptr<DBReader> pix::make_dbreader(pix::DBType dbt, const std::string& path)
{
    std::unique_ptr<DBReader> p;
    switch (dbt)
    {
    case pix::DBType::VOC:
    {
        p = std::make_unique<PixReader>(path);
        break;
    }
    case pix::DBType::MOT17:
        p = std::make_unique<MOTReader>(path);
        break;
    default:
        std::cout << "NOT DEFINED DBREADER FOR THAT" << std::endl;
        p = nullptr;
        break;
    }
    return p;
}


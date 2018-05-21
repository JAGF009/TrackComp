#include "TrackerFactory.hpp"
#include "../STRUCK/BasicConfig.hpp"
#include <iostream>
#include "TrackerStruck.hpp"
#include "TrackerOpenCV.hpp"
#include "TrackerRe3.hpp"

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
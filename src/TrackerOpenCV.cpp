#include "TrackerOpenCV.hpp"

using namespace std;
using namespace cv;
using namespace pix;

TrackerOpenCV::TrackerOpenCV(const pix::TrackerType type)

{
    switch (type)
    {
    case TrackerType::OpenCV_TLD:
        tracker = TrackerTLD::create();
        break;
    case TrackerType::OpenCV_KCF:
        tracker = TrackerKCF::create();
        break;
    case TrackerType::OpenCV_MF:
        tracker = TrackerMedianFlow::create();
        break;
    case TrackerType::OpenCV_BOOSTING:
        tracker = TrackerBoosting::create();
        break;
    case TrackerType::OpenCV_MIL:
        tracker = TrackerMIL::create();
        break;
    default:
        break;
    }
}

void TrackerOpenCV::init_track(const cv::Mat& im, const pix::Rect bb)
{
    tracker->init(im, bb.toOpenCV());
}
void TrackerOpenCV::init_track(const std::string& path, const pix::Rect bb)
{
    cv::Mat im = cv::imread(path, 0);
    init_track(im, bb);
}

pix::Rect TrackerOpenCV::track(const cv::Mat& im)
{
    cv::Rect2d roi;
    tracker->update(im, roi);
    return pix::Rect::fromOpenCV(roi, "no_name");

}

pix::Rect TrackerOpenCV::track(const std::string& path)
{
    cv::Mat im = cv::imread(path, 0);
    return track(im);
}


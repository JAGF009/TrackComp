#include "TrackerOpenCV.hpp"

using namespace std;
using namespace cv;
using namespace pix;

TrackerOpenCV::TrackerOpenCV(const pix::TrackerType type) : m_type(type)

{
    switch (m_type)
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

cv::Scalar TrackerOpenCV::color() 
{
    switch (m_type)
    {
    case TrackerType::OpenCV_TLD:

        return cv::Scalar(216, 237, 26);

    case TrackerType::OpenCV_KCF:

        return cv::Scalar(9, 189, 239);

    case TrackerType::OpenCV_MF:

        return cv::Scalar(252, 240, 7);

    case TrackerType::OpenCV_BOOSTING:

        return cv::Scalar(33, 8, 76);

    case TrackerType::OpenCV_MIL:

        return cv::Scalar(19, 239, 213);

    default:
        return cv::Scalar(0, 0, 0);
    }
}


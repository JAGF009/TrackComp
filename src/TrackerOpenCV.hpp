#ifndef TRACKER_OPEN_CV_PIX__
#define TRACKER_OPEN_CV_PIX__

#include "TrackerBasic.hpp"
#include "EnumsConst.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

namespace pix
{


class TrackerOpenCV : public pix::TrackerInterface
{
    public: 
        TrackerOpenCV(const pix::TrackerType);
        void init_track(const cv::Mat&, const pix::Rect) override;
        void init_track(const std::string&, const pix::Rect) override;
        pix::Rect track(const cv::Mat&) override;
        pix::Rect track(const std::string&) override;
        cv::Scalar color() override;

    private: 
        cv::Ptr<cv::Tracker> tracker;
        pix::TrackerType m_type;
};
}


#endif
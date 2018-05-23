#ifndef TRACKER_STRUCK__
#define TRACKER_STRUCK__

#include "TrackerBasic.hpp"
#include <memory>
#include <opencv2/opencv.hpp>

#include "../STRUCK/Tracker.h"

class TrackerStruck: public pix::TrackerInterface
{
    public: 
        TrackerStruck(std::istream& in);
        void init_track(const cv::Mat&, const pix::Rect) override;
        void init_track(const std::string&, const pix::Rect) override;
        pix::Rect track(const cv::Mat&) override;
        pix::Rect track(const std::string&) override;
        cv::Scalar color() override { return cv::Scalar(57, 237, 26); }
        

    private: 
        int32_t m_imW{0};
        int32_t m_imH{0};
        std::string m_name;
        float m_scaleW{1.0};
        float m_scaleH{1.0};
        std::unique_ptr<Tracker> m_p_tracker; // Dont like to work with pointers.
        cv::Mat m_resized_im;

};


#endif
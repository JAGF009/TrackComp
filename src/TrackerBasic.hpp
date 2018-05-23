#ifndef TRACKER_BASIC_H_
#define TRACKER_BASIC_H_

#include <string>

#include <opencv2/opencv.hpp>
#include "Rect.hpp"

namespace pix
{
    class TrackerInterface
    {

        public:
            enum class Mode {Path, Image};
            virtual pix::Rect track(const cv::Mat&) = 0;
            virtual pix::Rect track(const std::string&) = 0;
            virtual void init_track(const cv::Mat&, const pix::Rect) = 0;
            virtual void init_track(const std::string&, const pix::Rect) = 0;
            virtual ~TrackerInterface() = default;
            virtual cv::Scalar color() = 0;
            void setMode(Mode m)          { mode = m;    }
            Mode getMode() const noexcept { return mode; }
        private: 
            Mode mode {Mode::Image};
    };
}

#endif // TRACKER_BASIC_H_
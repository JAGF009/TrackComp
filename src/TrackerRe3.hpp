#include "TrackerBasic.hpp"
#include <zmq.hpp>

namespace pix
{
    class TrackerRe3 : public pix::TrackerInterface
    {
        public:
            TrackerRe3();
            pix::Rect track(const cv::Mat&) override;
            pix::Rect track(const std::string&) override;
            void init_track(const cv::Mat&, const pix::Rect) override;
            void init_track(const std::string&, const pix::Rect) override;
    };
}
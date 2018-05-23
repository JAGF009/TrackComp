#include "TrackerBasic.hpp"
#include <zmq.hpp>
#include "../3rd_party/subprocess.hpp"

namespace pix
{
    class TrackerRe3 : public pix::TrackerInterface
    {
        private: 
            subprocess::Popen proc;
        public:
            TrackerRe3();
            ~TrackerRe3();
            pix::Rect track(const cv::Mat&) override;
            pix::Rect track(const std::string&) override;
            void init_track(const cv::Mat&, const pix::Rect) override;
            void init_track(const std::string&, const pix::Rect) override;
            cv::Scalar color() override { return cv::Scalar(241, 56, 255); }
    };
}
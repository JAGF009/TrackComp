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
            virtual pix::Rect track(const std::string&) = 0;
            virtual void init_track(const std::string&, const pix::Rect) = 0;
            virtual ~TrackerInterface() = default;
    };
}

#endif // TRACKER_BASIC_H_
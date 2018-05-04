#ifndef TRACKER_BASIC_H_
#define TRACKER_BASIC_H_

#include <string>
#include "Rect.hpp"
#include <gsl/pointers>

namespace pix
{
    class Tracker
    {
        public:
            virtual pix::Rect track(const std::string&) = 0;
            virtual void initialize(const pix::Rect) = 0;
            virtual ~Tracker() = default;
    };
}

#endif // TRACKER_BASIC_H_
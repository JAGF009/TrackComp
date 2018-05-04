#ifndef TRACKER_STRUCK__
#define TRACKER_STRUCK__

#include "TrackerBasic.hpp"

class TrackerStruck: public pix::Tracker
{
    public: 
        void initialize(const pix::Rect) override;
        pix::Rect track(const std::string&) override;
};


#endif
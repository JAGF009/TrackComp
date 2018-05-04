#ifndef TRACKER_STRUCK__
#define TRACKER_STRUCK__

#include "TrackerBasic.hpp"
#include <gsl/gsl>
#include <memory>

#include "../STRUCK/Tracker.h"

class TrackerStruck: public pix::TrackerInterface
{
    public: 
        TrackerStruck(std::istream& in);
        ~TrackerStruck();
        void initialize(const std::string&, const pix::Rect) override;
        pix::Rect track(const std::string&) override;
        

    private: 
        int32_t m_imW{0};
        int32_t m_imH{0};
        std::string m_name;
        bool m_needResize{false};
        float m_scaleW{1.0};
        float m_scaleH{1.0};
        std::unique_ptr<Tracker> m_p_tracker; // Dont like to work with pointers.

};


#endif
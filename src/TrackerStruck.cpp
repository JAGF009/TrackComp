#include "TrackerStruck.hpp"
#include <iostream>

#include "../STRUCK/Config.h"

TrackerStruck::TrackerStruck(std::istream& in)
{
    Config cf(in);
    m_p_tracker = std::make_unique<Tracker>(cf);
    m_imW = cf.frameWidth;
    m_scaleW = (float) m_imW;
    m_imH = cf.frameHeight;
    m_scaleH = (float) m_imH;
    m_name = "undefined";
}

void TrackerStruck::init_track(const cv::Mat& im, const pix::Rect r)
{
    m_scaleW /= im.cols;
    m_scaleH /= im.rows;

    cv::resize(im, m_resized_im, cv::Size(m_imW, m_imH));

    FloatRect fr(r.X() * m_scaleW, r.Y() * m_scaleH, r.W() * m_scaleW, r.H() * m_scaleH);
    m_p_tracker->Initialise(m_resized_im, fr);
}

pix::Rect TrackerStruck::track(const cv::Mat& im)
{
    cv::resize(im, m_resized_im, cv::Size(m_imW, m_imH));

    m_p_tracker->Track(m_resized_im);

    auto fr = m_p_tracker->GetBB();
    return pix::Rect(fr.XMin() / m_scaleW, fr.YMin() / m_scaleH, fr.Width() / m_scaleW, fr.Height() / m_scaleH, m_name);
}

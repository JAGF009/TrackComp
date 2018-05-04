#include "TrackerStruck.hpp"

#include "../STRUCK/Config.h"

TrackerStruck::TrackerStruck(std::istream& in)
{
    Config cf(in);
    m_p_tracker = std::make_unique<Tracker>(cf);
    m_imW = cf.frameWidth;
    m_imH = cf.frameHeight;
    m_name = "undefined";
}

TrackerStruck::~TrackerStruck()
{
    m_p_tracker.release();
}

void TrackerStruck::initialize(const std::string& imPath, const pix::Rect r)
{
    cv::Mat im = cv::imread(imPath, 0);
    m_scaleW /= im.cols;
    m_scaleH /= im.rows;
    cv::resize(im, im, cv::Size(m_imW, m_imH));
    FloatRect fr(r.X() * m_scaleW, r.Y() * m_scaleH, r.W() * m_scaleW, r.H() * m_scaleH);
    m_p_tracker->Initialise(im, fr);
    return;
}

pix::Rect TrackerStruck::track(const std::string& imPath)
{
    cv::Mat im = cv::imread(imPath, 0);
    cv::resize(im, im, cv::Size(m_imW, m_imH));
    m_p_tracker->Track(im);
    auto fr = m_p_tracker->GetBB();
    return pix::Rect(fr.XMin() / m_scaleW, fr.YMin() / m_scaleH, fr.Width() / m_scaleW, fr.Height() / m_scaleH, m_name);
}

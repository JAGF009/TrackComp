#define SHOW___

#include "TrackMeas.hpp"
#include "PIXReader.hpp"


#include <algorithm>
#include <cmath>

using namespace pix;
using namespace std;


std::string mul_string(const std::string& s, int n)
{
    std::string newstring{""};
    if (n <= 0) return newstring;
    newstring += s;
    while(--n)
        newstring += s;  
    return newstring;
}


void drawRect(cv::Mat& im, pix::Rect r, cv::Scalar color = cv::Scalar(0, 0, 0), int thickness = 1)
{
        cv::rectangle(im, r.toOpenCV(), color, thickness);
}


TrackMeas::TrackMeas(const std::string& path, pix::DBType dt_type, pix::TrackerType track)
{

    tracker = pix::make_tracker(track);
    db = std::make_unique<PixReader>(path);
}

TrackMeas::~TrackMeas()
{
    cv::destroyAllWindows();
}

void TrackMeas::go()
{
    const int db_size = db->nFrames();
    int frame_number = 0;
    std::string name {db->imageName(frame_number)};
    image = cv::imread(name);
    pix::Rect initBB = db->getBBFrameID(frame_number++, "Jose");
    tracker->init_track(image, initBB);
    while (1)
    {
        int n = 100 * frame_number / db_size;
        std::cout << "\r[" << mul_string("#", n) << mul_string(" ", 100-n) << "]" << " " << n << "%";
        std::cout.flush();
        name = db->imageName(frame_number); 
        if (name.empty()) break;
        image = cv::imread(name);
        auto realBB = db->getBBFrameID(frame_number++, "Jose");
        
        pix::Rect bbt = tracker->track(image);
        newFrame(realBB, bbt);
#ifdef SHOW___
        auto key = show(realBB, bbt);
        if (key == 27) break;
#endif
        frame_number += 10;
    }
    std::cout << endl;
}

int TrackMeas::show(const Rect& gt, const Rect& tr)
{
    cv::rectangle(image, gt.toOpenCV(), cv::Scalar(255, 0, 0), 3);
    cv::rectangle(image, tr.toOpenCV(), cv::Scalar(0, 0, 255), 3);
    cv::imshow("m_name", image);
    return cv::waitKey(1);
}

void TrackMeas::newFrame(const Rect& gt, const Rect& track)
{
    if (!gt.valid() && !track.valid()) return;
    n_frames ++;
    if (!gt.valid())
    {
        n_false_positives++;
        return;
    }
    if (!track.valid())
    {
        n_gts++;
        n_false_negatives++;
        return;
    }
    n_gts++;
    m_fScore.push_back(gt.IoU(track));
    m_f1Score.push_back(gt.F1Intermediate(track));
}


double TrackMeas::fScore(double threshold) const noexcept
{
    long int tp = std::count_if(m_fScore.begin(), m_fScore.end(), Comp(threshold));
    m_int local_false_positives = n_false_positives + m_fScore.size() - tp;
    if (tp == 0 && n_false_negatives == 0 && local_false_positives == 0) return 0.0;
    // std::cout << "tp: " << tp << " n_false_negatives: " << n_false_negatives << " n_false_positives: " << n_false_positives << std::endl;
    double precision = ((double) tp) / (tp + local_false_positives);
    double recall = ((double) tp) / (tp + n_false_negatives);
    return 2 * precision * recall / (precision + recall);
}

double TrackMeas::f1Score() const noexcept
{
    return 0;
}

double TrackMeas::OTP(double threshold) const noexcept
{
    auto ms = std::count_if(m_fScore.begin(), m_fScore.end(), Comp(threshold));
    auto n = std::accumulate(m_fScore.begin(), m_fScore.end(), (double) 0, [&](double& s, const double& d) -> double {if (d >= threshold) return s + d; return s;});
    if (ms <= 0) return 0;
    return ((double)n) / ms;
}

double TrackMeas::ATA() const noexcept
{
    if (n_frames == 0) return 0;
    return std::accumulate(m_fScore.begin(), m_fScore.end(), (double) 0) / n_frames;
}
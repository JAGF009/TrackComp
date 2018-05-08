#define SHOW___

#include "TrackMeas.hpp"
#include "Rect.hpp"

#include "TrackerStruck.hpp"
#include "../STRUCK/BasicConfig.hpp"
#include "PIXReader.hpp"

#include <algorithm>
#include <cmath>

using namespace pix;
using namespace std;


TrackMeas::TrackMeas(const std::string& path, DBType dt_type, TrackerType track)
{
    auto iss = buildBasicConf(
        "", "", {"haar gaussian 0.2"}
    ); 
    tracker = std::make_unique<TrackerStruck>(iss);
    db = std::make_unique<PixReader>(path);
}

TrackMeas::~TrackMeas()
{
    cv::destroyAllWindows();
}

void TrackMeas::go()
{
    
    int frame_number = 0;
    std::string name {db->imageName(frame_number)};
    image = cv::imread(name);
    pix::Rect initBB = db->getBBFrameID(frame_number++, "Jose");
    tracker->init_track(image, initBB);
    while (1)
    {
        std::cout << "Frame number: " << name << endl;
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
        
    }
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
    }
    if (!track.valid())
    {
        n_false_negatives++;
    }
    m_fScore.push_back(gt.IoU(track));
    m_f1Score.push_back(gt.F1Intermediate(track));
}


double TrackMeas::fScore(double threshold)
{
    long int tp = std::count_if(m_fScore.begin(), m_fScore.end(), [&](float n){return n >= threshold;});
    m_int local_false_positives = n_false_positives + m_fScore.size() - tp;
    if (tp == 0 && n_false_negatives == 0 && local_false_positives == 0) return 0.0;
    // std::cout << "tp: " << tp << " n_false_negatives: " << n_false_negatives << " n_false_positives: " << n_false_positives << std::endl;
    double precision = ((double) tp) / (tp + local_false_positives);
    double recall = ((double) tp) / (tp + n_false_negatives);
    return 2 * precision * recall / (precision + recall);
}

double TrackMeas::f1Score()
{
    return 0;
}
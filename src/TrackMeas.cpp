#include "TrackMeas.hpp"
#include "Rect.hpp"

#include <algorithm>
#include <cmath>

using namespace pix;

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
    long int tp = std::count_if(m_fScore.begin(), m_fScore.end(), Comp(threshold));
    m_int local_false_positives = n_false_positives + m_fScore.size() - tp;
    if (tp == 0 && n_false_negatives == 0 && local_false_positives == 0) return 0.0;
    // std::cout << "tp: " << tp << " n_false_negatives: " << n_false_negatives << " n_false_positives: " << n_false_positives << std::endl;
    double precision = ((double) tp) / (tp + local_false_positives);
    double recall = ((double) tp) / (tp + n_false_negatives);
    // std::cout << "precision: " << precision << " recall: " << recall;
    return 2 * precision * recall / (precision + recall);
}

double TrackMeas::f1Score()
{
    return 0;
}
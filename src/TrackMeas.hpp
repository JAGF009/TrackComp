#ifndef TRACKMEAS_H
#define TRACKMEAS_H
#include <vector>
#include "Rect.hpp"

struct Comp
{
    Comp(double athres): thresh(athres) {}

    bool operator()(const double& lhs) { return lhs >= thresh;} 

    double thresh;
};

class TrackMeas
{
    public:
        TrackMeas() {}

        void newFrame(const pix::Rect& = pix::Rect(), const pix::Rect& = pix::Rect());
        double fScore(double);
        double f1Score();

    private:
        std::vector<double> m_fScore {};
        std::vector<double> m_f1Score {};
        m_int n_frames {0};
        m_int n_track {0};
        m_int n_gts {0};
        m_int n_false_positives {0};
        m_int n_false_negatives {0};
};

#endif // TRACKMEAS_H
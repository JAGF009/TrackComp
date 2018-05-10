#ifndef TRACKMEAS_H
#define TRACKMEAS_H
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

#include "Rect.hpp"
#include "TrackerFactory.hpp"
#include "DBReader.hpp"

namespace pix{


struct Comp
{
    Comp(double athres): thresh(athres) {}

    bool operator()(const double& lhs) { return lhs >= thresh;} 

    double thresh;
};

class TrackMeas
{
    private:
        m_int n_frames {0};
        m_int n_track {0};
        m_int n_gts {0};
        m_int n_false_positives {0};
        m_int n_false_negatives {0};
        m_int m_frameSkip{0};
        bool m_stop{false};
        std::unique_ptr<DBReader> db;
        std::unique_ptr<pix::TrackerInterface> tracker;
        cv::Mat image;
        std::vector<double> m_fScore {};
        std::vector<double> m_f1Score {};

    public:
        TrackMeas() = default;
        TrackMeas(const std::string& path, pix::DBType dt_type, pix::TrackerType track_type);
        ~TrackMeas();

        m_int frameSkip() const noexcept;
        void setFrameSkip(m_int fs) noexcept { m_frameSkip = fs;}
        void stop() noexcept { m_stop = true; }
        bool stopped() const noexcept { return m_stop; }

        void init_track(const cv::Mat&, const pix::Rect&);
        void go();
        double fScore(double) const noexcept;
        double f1Score() const noexcept;
        double OTP(double) const noexcept;
        double ATA() const noexcept;


    private:

        void show(const pix::Rect&, const pix::Rect&);
        void newFrame(const pix::Rect& = pix::Rect(), const pix::Rect& = pix::Rect());
};

}
#endif // TRACKMEAS_H
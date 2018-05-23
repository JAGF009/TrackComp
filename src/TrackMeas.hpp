#ifndef TRACKMEAS_H
#define TRACKMEAS_H
#include <vector>
#include <memory>
#include <unordered_set>
#include <opencv2/opencv.hpp>

#include "Rect.hpp"
#include "Factory.hpp"
#include "Trajectory.hpp"

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
        m_int m_width{0};
        m_int m_height{0};
        bool m_stop{false};
        std::string m_id;
        std::unique_ptr<DBReader> db;
        std::unique_ptr<pix::TrackerInterface> tracker;
        cv::Mat image;
        std::vector<double> m_fScore {};
        std::vector<double> m_f1Score {};
        std::vector<double> m_distances {};
        pix::Trajectory real_traj;
        pix::Trajectory detectec_traj;

    public:
        TrackMeas() = default;
        TrackMeas(const std::string& path, const std::string& id, pix::DBType dt_type, pix::TrackerType track_type);
        ~TrackMeas();

        m_int frameSkip() const noexcept { return m_frameSkip; } 
        void setFrameSkip(m_int fs) noexcept { m_frameSkip = fs; }
        void stop() noexcept { m_stop = true; }
        bool stopped() const noexcept { return m_stop; }

        bool idInFrame(m_int, const std::string&, std::unordered_set<std::string>&) const;

        void init_track(const cv::Mat&, const pix::Rect&);
        void go();
        double fScore(double) const noexcept;
        double f1Score() const noexcept;
        double OTA(double) const noexcept;
        double OTP(double) const noexcept;
        double ATA() const noexcept;
        double Deviation() const noexcept;


    private:

        void show(const pix::Rect&, const pix::Rect&, int time = 1);
        void newFrame(const pix::Rect& = pix::Rect(), const pix::Rect& = pix::Rect());
};

}
#endif // TRACKMEAS_H
#include "Rect.hpp"
#include <deque>

namespace pix
{

class Trajectory
{
    private: 
        std::deque<pix::Point> m_points;
        m_int m_max_size;
    
    public:
        Trajectory(m_int max_size = 50): m_max_size(max_size) {}
        void push(const pix::Point& p) {m_points.emplace_back(p); if (m_points.size() > m_max_size) m_points.pop_front();}
        void push(const cv::Point& p)
        {
            pix::Point p_p(p.x, p.y);
            push(p_p);
        }
        void push(const pix::Rect& r)
        {
            pix::Point p_p((r.left() + r.right()) / 2, r.bottom());
            push(p_p);
        }
        void draw(cv::Mat&, const cv::Scalar&);
};
}
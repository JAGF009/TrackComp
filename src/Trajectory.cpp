#include "Trajectory.hpp"

using namespace pix;

void Trajectory::draw(cv::Mat& im, const cv::Scalar& color)
{
    /*
    for (auto p: m_points)
        cv::circle(im, p.toOpenCV(), 1, color, 3);
    */
   for (int i=1; i!=m_points.size(); i++)
   {
       cv::line(im, m_points[i-1].toOpenCV(), m_points[i].toOpenCV(), color, 3);
   }
}
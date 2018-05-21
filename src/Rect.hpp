#ifndef RECT_H
#define RECT_H

#include <cstdint>
#include <iostream>


#include <opencv2/opencv.hpp>

using m_int = int32_t;

namespace pix
{

struct Point
{
    Point(m_int ax, m_int ay): x(ax), y(ay) {}
    Point(): x(0), y(0) {}

    cv::Point2i toOpenCV() {return cv::Point2i(x, y);}

    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    float x;
    float y;
};

class Rect{
    public:
        explicit Rect();
        Rect(m_int x, m_int y, m_int w, m_int h, const std::string& id);
        Rect(Point aupperLeft, Point abottomRight, const std::string& id);

        friend std::ostream& operator<<(std::ostream& os, const Rect& r);

        m_int left()  const {return upperLeft().x; }
        m_int top()   const {return upperLeft().y; }
        m_int right()  const {return bottomRight().x; }
        m_int bottom() const {return bottomRight().y; }

        Point center() const;

        cv::Rect toOpenCV() const;
        static Rect fromOpenCV(const cv::Rect& from, const std::string& name);

        const std::string& id() const {return m_id;}


        m_int X() const {return m_x;}
        void setX(m_int x) {m_x=x; _check_valid();}

        m_int Y() const {return m_y;}
        void setY(m_int y) {m_y=y;  _check_valid();}

        m_int W() const {return m_w;}
        void setW(m_int w) {m_w=w; _check_valid();}

        m_int H() const {return m_h;}
        void setH(m_int h) {m_h=h; _check_valid();}

        bool valid() const {return !m_invalid;}

        Point upperLeft() const {return m_upperLeft;}
        Point bottomRight() const {return m_bottomRight;}

        m_int area() const {return m_w * m_h;}

        double IoU(const Rect& lhs) const;

        double F1Intermediate(const Rect& lhs) const;

        double distance(const Rect& lhs) const;

        // Calculates the intersection of two rectangles;
        Rect operator&(const Rect& lhs) const;
        // Calculates the union of two rectangles;
        Rect operator|(const Rect& lhs) const;

        Point movement(const Rect& lhs) const;


    private:

        void _update_corners();
        void _check_valid();


        Point m_upperLeft;
        Point m_bottomRight;
        std::string m_id;
        std::string m_real_id;
        m_int m_x;
        m_int m_y;
        m_int m_w;
        m_int m_h;
        bool m_invalid{false}; // Unused for now.


};

}
#endif // RECT_H
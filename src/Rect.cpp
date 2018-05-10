#include "Rect.hpp"
#include <algorithm>


using namespace pix;

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "Point: (" << p.x << "," << p.y << ")";
    return os;
}

Rect::Rect()
{
    m_x = 0;
    m_y = 0;
    m_w = 0;
    m_h = 0;
    m_id = "no-id";
    _update_corners();
}

Rect::Rect(int32_t x, int32_t y, int32_t w, int32_t h, const std::string& id):
        m_x(x), m_y(y), m_w(w), m_h(h), m_id(id) {
            _update_corners();
        }
Rect::Rect(Point aupperLeft, Point abottomRight, const std::string& id)
{
    Rect(aupperLeft.x, aupperLeft.y, abottomRight.x - aupperLeft.x, abottomRight.y - aupperLeft.y, id);
}

std::ostream& operator<<(std::ostream& os, const pix::Rect& r)
{
    os << "Rect: " << r.id() <<  ", x: " << r.X() << ", y: " << r.Y() << ", w: " << r.W() << ", h: " << r.H();
    return os;
}

Point Rect::center() const 
{
    return Point(W() - X(), H() - Y());
}

cv::Rect Rect::toOpenCV() const
{
    return cv::Rect(m_x, m_y, m_w, m_h);
}

Rect Rect::fromOpenCV(const cv::Rect& from, const std::string& name)
{
    return Rect(from.x, from.y, from.width, from.height, name);
}

double Rect::IoU(const Rect& lhs) const
{
    m_int uni {(*this & lhs).area()};
    return ((double) uni)/(area()+lhs.area() - uni);
}

double Rect::F1Intermediate(const Rect& lhs) const
// In F1Intermediate method.
{
    Rect uni = (*this & lhs);
    if (uni.area() == 0) return 0;
    m_int gt_a = area();
    m_int tr_a = lhs.area();
    double p = ((double) uni.area()) / tr_a;
    double r = ((double) uni.area()) / gt_a;
    return p * r / (p + r);
}

Rect Rect::operator&(const Rect& lhs) const
{
    /*
    std::cout << "Rect 1: " << *this << "\nRect 2: " << lhs << std::endl;
    std::cout << "Rect 1 upperLeft:" << upperLeft();
    std::cout << "\nRect 1 bottomRight:" << bottomRight();
    std::cout << "\nRect 2 upperLeft:" << lhs.upperLeft();
    std::cout << "\nRect 2 bottomRight:" << lhs.bottomRight() << std::endl;
    */
    m_int x_ul {std::max(upperLeft().x, lhs.upperLeft().x)};
    m_int y_ul {std::max(upperLeft().y, lhs.upperLeft().y)};
    m_int x_br {std::min(bottomRight().x, lhs.bottomRight().x)};
    m_int y_br {std::min(bottomRight().y, lhs.bottomRight().y)};
    m_int w {x_br - x_ul};
    m_int h {y_br - y_ul};
    /*
    std::cout << "x: " << x_ul <<" y: " <<  y_ul << " x_br: " << x_br << " y_br: " << y_br << std::endl;
    std::cout << "w: " << w << " h: " << h << std::endl;
    */
    return Rect(x_ul, y_ul, w, h, m_id + "int" + lhs.id());
}

Rect Rect::operator|(const Rect& lhs) const
// This union does not work as you might expect, it is the enclosing rectangle.
{
    m_int x_ul {std::min(upperLeft().x, lhs.upperLeft().x)};
    m_int y_ul {std::min(upperLeft().y, lhs.upperLeft().y)};
    m_int x_br {std::max(bottomRight().x, lhs.bottomRight().x)};
    m_int y_br {std::max(bottomRight().y, lhs.bottomRight().y)};
    return Rect(x_ul, y_ul, x_br - x_ul, y_br - y_ul, m_id + "un" + lhs.id());

}

Point Rect::movement(const Rect& old) const
{
    return Point(
        ((float) ((old.center().x - center().x) + (old.upperLeft().x - upperLeft().x) + (old.bottomRight().x - bottomRight().x))) / 3,
        ((float) ((old.center().y - center().y) + (old.upperLeft().y - upperLeft().y) + (old.bottomRight().y - bottomRight().y))) / 3
    );
}


void Rect::_update_corners()
{
    if (m_w <=0 || m_h <= 0)
    {
        m_x = 0;
        m_y = 0;
        m_w = 0;
        m_h = 0;
        m_upperLeft = Point(0, 0);
        m_bottomRight = Point(0, 0);
        m_invalid = true;
        m_id = "invalid";
        return;
    }
    m_upperLeft = Point(m_x, m_y);
    m_bottomRight = Point(m_x + m_w, m_y + m_h);
}
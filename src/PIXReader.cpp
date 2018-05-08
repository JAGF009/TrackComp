#include "PIXReader.hpp"
#include <stdexcept>
#include "../3rd_party/filesystem.hpp"

using namespace std;
using namespace pix;

PixReader::PixReader(const string &path)
{
    if (path.back() != '/')
        throw std::runtime_error("IN 'PixReader(const string& path)' path has to be a directory");
    if (exists(path + "xmls/"))
        xmls.load(path + "xmls/");

    m_int frame_number{0};

    string name{xmls.imageFullName(frame_number)};
    while (exists(name))
    {
        std::cout << name << std::endl;
        vector<Rect> v;
        BoxesMap rs = xmls.read(frame_number);
        for (auto it = rs.cbegin(); it != rs.cend(); it++)
        {
            for (auto r : it->second)
                v.push_back(r);
        }
        m_db.emplace_back(name, v);
        name = xmls.imageFullName(++frame_number);
    }

}

string PixReader::imageName(m_int number) const
{
    try
    {
        return m_db.at(number).name;
    } catch(...)
    {
        return "";
    }
}

vector<Rect> PixReader::getBBFrame(m_int frame) const
{
/*     vector<Rect> v;
    BoxesMap rs = xmls.read(frame);
    for (auto it = rs.cbegin(); it != rs.cend(); it++)
    {
        for (auto r : it->second)
            v.push_back(r);
    }
    return v; */
    return m_db.at(frame).boxes;
}

Rect PixReader::getBBFrameID(m_int frame, const string &id) const
{
    auto rects = getBBFrame(frame);
    for (auto r: rects)
        if (r.id() == id) return r;
    return Rect(0, 0, 0, 0, "inv");

    /* vector<Rect> rects = xmls.read(frame)[id];
    if (rects.empty())
        
    return rects[0]; // In this case it will only be 1; */
}

ostream &operator<<(ostream &os, const PixReader &p)
{
    os << "PixReader for: ";
    os << p.imageName(0);
    return os;
}
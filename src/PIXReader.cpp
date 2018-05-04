#include "PIXReader.hpp"
#include <stdexcept>
#include "../3rd_party/filesystem.hpp"


using namespace std;
using namespace pix;

PixReader::PixReader(const string& path)
{
    if (path.back() != '/') throw std::runtime_error("IN 'PixReader(const string& path)' path has to be a directory");
    if (exists(path + "xmls/")) xmls.load(path + "xmls/");

}

string PixReader::imageName(m_int number) const
{
    string name = xmls.imageFullName(number);
    if (!exists(name))
        return "";
    return name;
}

vector<Rect> PixReader::getBBFrame(m_int frame) const
{
    vector<Rect> v;
    BoxesMap rs = xmls.read(frame);
    for (auto it = rs.cbegin(); it != rs.cend(); it++)
    {
        for (auto r: it->second) v.push_back(r);
    }
    return v;
}

Rect PixReader::getBBFrameID(m_int frame,const string& id) const
{
    vector<Rect> rects = xmls.read(frame)[id];
    if (rects.empty())
        return Rect(0,0,0,0,"inv");
    return rects[0]; // In this case it will only be 1;
}

ostream& operator<<(ostream& os, const PixReader& p)
{
    os << "PixReader for: ";
    os << p.imageName(0);
    return os;
}
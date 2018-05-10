#ifndef DB_READER_H
#define DB_READER_H

#include <string>
#include <vector>
#include "Rect.hpp"

class DBReader
{
    public:

        virtual std::string imageName(m_int number) const = 0;
        virtual std::vector<pix::Rect> getBBFrame(m_int frame) const = 0;
        virtual pix::Rect getBBFrameID(m_int frame, const std::string& id) const = 0;
        virtual m_int nFrames() const = 0;
        virtual ~DBReader() = default;

};










#endif // DB_READER_H
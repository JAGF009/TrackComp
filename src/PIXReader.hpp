#ifndef PIX_READER_H
#define PIX_READER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "DBReader.hpp"
#include "xmlhandler.hpp"
#include "Rect.hpp"

class PixReader: public DBReader 
{
    public: 
        PixReader(const std::string& path);
        std::string imageName(m_int number) const override;
        std::vector<pix::Rect> getBBFrame(m_int frame) const override;
        pix::Rect getBBFrameID(m_int frame, const std::string& id) const override;
        m_int nFrames() const override { return m_db.size(); }

    friend std::ostream& operator<<(std::ostream&, const PixReader&);

    private:

        struct RegisterDB
        {
            using Boxes = std::vector<pix::Rect>;
            std::string name;
            Boxes boxes;
            RegisterDB(const std::string& nname, const Boxes& bboxes): name(nname), boxes(bboxes) {}
        };
        std::vector<RegisterDB> m_db;
        XMLHandler xmls;
};

#endif // PIX_READER_H
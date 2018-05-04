#ifndef MOTREADER_H
#define MOTREADER_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

#include "Rect.hpp"
#include "DBReader.hpp"

using namespace pix;


class MOTReader: public DBReader
{
    public:
        MOTReader(const std::string& path);
        ~MOTReader() override = default;

        std::string seqName() const { return m_seqName; }
        std::string imDir() const { return m_imDir; }
        std::string imPath() const { return m_imPath; }
        m_int frameRate() const { return m_frameRate; }
        m_int seqLength() const { return m_seqLength; }
        m_int imWidth() const { return m_imWidth; }
        m_int imHeigth() const { return m_imHeigth; }
        std::string imExt() const { return m_imExt; }

        std::string imageName(m_int number) const override;

        std::vector<pix::Rect> getBBFrame(m_int frame) const override;
        pix::Rect getBBFrameID(m_int frame, const std::string& id) const override;
        

    friend std::ostream& operator<<(std::ostream& os, const MOTReader&);

    private:
        void _readGroundTruth(const std::string& path);

        const std::string imageFormat{"%06d"};
        //vector<pix::Rect> groundtruth;
        //unordered_map<int, vector<pix::Rect>> groundtruth;
        std::unordered_map<m_int, std::unique_ptr<std::vector<pix::Rect>>> groundtruth; // Faster this way? Should seek it;
        std::string m_seqName;
        std::string m_imDir;
        std::string m_imPath;
        m_int m_frameRate;
        m_int m_seqLength;
        m_int m_imWidth;
        m_int m_imHeigth;
        std::string m_imExt;

};


#endif
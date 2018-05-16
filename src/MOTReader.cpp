#include "MOTReader.hpp"
#include <fstream>
#include "../3rd_party/ConfigFile.hpp"
#include "../3rd_party/formated_string.hpp"

using namespace std;
using namespace pix;

MOTReader::MOTReader(const string& path)
{

    ConfigFile cf(path + "seqinfo.ini");

    m_seqName = cf.Value("Sequence", "name");
    m_imDir = cf.Value("Sequence", "imDir");
    m_frameRate = std::stoi(cf.Value("Sequence", "frameRate"));
    m_seqLength = std::stoi(cf.Value("Sequence", "seqLength"));
    m_imWidth = std::stoi(cf.Value("Sequence", "imWidth"));
    m_imHeigth = std::stoi(cf.Value("Sequence", "imHeight"));
    m_imExt = cf.Value("Sequence", "imExt", "");

    m_imPath = path + m_imDir + "/" + imageFormat + m_imExt;

    _readGroundTruth(path + "gt/gt.txt");

}

string MOTReader::imageName(m_int number) const
{
    string s{""};
    if (0 <= number && number <= m_seqLength)
        s=string_format(m_imPath, number);
    return s;
}

vector<Rect> MOTReader::getBBFrame(m_int frame) const
{
    
    auto it = groundtruth.find(frame);
    if (it != groundtruth.end())
        return *((*it).second);
    return vector<Rect>{};
}

Rect MOTReader::getBBFrameID(m_int frame, const string& id) const
{
    
    vector<Rect> v{};
    auto it = groundtruth.find(frame);
    if (it != groundtruth.end())
        v = *((*it).second);
    for (auto r:v) 
        if (r.id() == id)
            return r;
            
    return Rect();
}

ostream& operator<<(ostream& os, const MOTReader& m)
{
    os << "Sequence Name: " << m.seqName() << '\n';
    os << "Image Dir: " << m.imDir() << '\n';
    os << "Image Path: " << m.imPath() << '\n';
    os << "Frame rate: " << m.frameRate() << '\n';
    os << "Sequence Length: " << m.seqLength() << '\n';
    os << "Image Width: " << m.imWidth() << '\n';  
    os << "Image Height: " << m.imHeigth() << '\n';
    os << "Image Extension: " << m.imExt(); 
    return os;

}

void MOTReader::_readGroundTruth(const string& path)
{
    int c{0};
    ifstream gt;
    string line;
    gt.open(path);
    if (gt.is_open())
    {
        while (getline(gt, line))
        {
            vector<string> v = explode(line, ',');
            if (v[6]=="1")
            {
                c++;
                unique_ptr<vector<Rect>> &entry = groundtruth[stoi(v[0])];
                if (!entry)
                    entry = make_unique<vector<Rect>>();
                entry->emplace_back(
                    Rect(
                            stoi(v[2]),
                            stoi(v[3]),
                            stoi(v[4]),
                            stoi(v[5]),
                            v[1]
                        )
                );
            }

            
        }
        gt.close();
        std::cout << "Total number of boxes: " << c <<std::endl;
    }
    else{
        std::cout << "Unable to open file" << std::endl;
    }
}
#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "Rect.hpp"
#include "pugixml.hpp"

#define XML 1
#define JPG 2




using Boxes = std::vector<pix::Rect>;
using BoxesMap = std::unordered_map<std::string, Boxes>;


size_t bs(std::vector<int>&, const int);
void insort(std::vector<int>&, const int);

std::string splitbase(const std::string& filename, const std::string& word = "_frame");
std::string filename2number(const std::string &filename, const std::string& word = "_frame");

/*
std::vector<std::string> filesInDir(const std::string& folder, bool absolute=false);
std::vector<std::string> filesInDirFilter(const std::string& folder, const std::string& filter);

std::string dirname_st(const std::string& path);
std::string basename_st(const std::string& path);

inline bool exists(const std::std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0);
}
*/


class XMLHandler
{
public:
    XMLHandler() = default;
    XMLHandler(std::string filepath);
    bool load(std::string filepath);
    BoxesMap read(int frame, std::string classFilter = "any") const;
    bool write(BoxesMap& boxes, int frame);

    std::string imageName(int frame) const;
    std::string imageFullName(int frame) const;

    int min() const;
    int max() const;

    int jump_from(int from, int steps);

private:
    std::string dirname_xmls;
    std::string basename_xmls;
    std::string dirname_images;
    std::string basename_images;
    std::vector<int> frames;

    const std::unordered_map<std::string, int> _s_map{
        {".xml", XML}, {".jpg", JPG}
    };

    void makeHeader(pugi::xml_node& mainNode, int frame);
    bool includeBoxes(pugi::xml_node& boxNode, BoxesMap& allBoxes);
    std::string fullName(int frame, const std::string& extension=".xml") const;
};

#endif // XMLHANDLER_H

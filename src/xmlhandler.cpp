#include "xmlhandler.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>

/*
#include <dirent.h>
#include <cstddef> // size_t
#include <cstring> //strcpy
#include <libgen.h> // basename dirname
*/

#include "../3rd_party/filesystem.hpp"

// namespace fs = std::experimental::filesystem;

using namespace pix;

XMLHandler::XMLHandler(string filepath)
{
    load(filepath);
}

bool XMLHandler::load(string filepath)
{
    vector<string> xmls = filesInDirFilter(filepath, "xml");
    // name = filesDir.absoluteFilePath(xmls[0].section("", 0, xmls[0].lastIndexOf("_frame") + 6));
    if (xmls.empty()) return false;
    dirname_xmls = dirname_st(xmls[0]);
    dirname_images = dirname_st(dirname_xmls) + "/images";
    vector<string> images = filesInDirFilter(dirname_images + "/", "jpg");
    basename_images = splitbase(basename_st(images[0]));
    basename_xmls = splitbase(basename_st(xmls[0]));
    /*
    std::cout << dirname_xmls << std::endl;
    std::cout << dirname_images << std::endl;
    std::cout << basename_images << std::endl;
    std::cout << basename_xmls << std::endl;
    */
    
    for (auto s: xmls)
        frames.push_back(std::stoi(filename2number(s)));
    sort(frames.begin(), frames.end());
    if (!frames.empty())
    {
        // qDebug() << frames;
        return true;  // If there are some xmls return true!
    }
    return false;
}

BoxesMap XMLHandler::read(int frame, string classFilter) const
{
    if (find(frames.begin(), frames.end(), frame) != frames.end())
    {
        pugi::xml_document doc;
        if (doc.load_file(fullName(frame).c_str()))
        {
            BoxesMap allBoxes{};
            for (pugi::xml_node object: doc.first_child().children("object"))
            {
                string className {object.child("name").text().as_string()};
                Boxes boxes{};
                for (pugi::xml_node box: object.children("bndbox"))
                {
                    // qDebug() << object.child_value("name");
                    float xmin {box.child("xmin").text().as_float()};
                    float ymin {box.child("ymin").text().as_float()};
                    float xmax {box.child("xmax").text().as_float()};
                    float ymax {box.child("ymax").text().as_float()};
                    // qDebug() << xmin << ymin << xmax << ymax;
                    boxes.push_back(Rect(xmin, ymin, xmax-xmin, ymax-ymin, className));
                }
                if (!boxes.empty()) 
                    allBoxes[className] = boxes; // Maybe there is the object tag but no bndbox in it
                                                 // if that happens just dont include an empty vector in the map.
            }
            return allBoxes;
        }
    }
    return BoxesMap{};
}

bool XMLHandler::write(BoxesMap& allBoxes, int frame)
{
    std::cout << "XMLHandler::write" << '\n';
    std::cout << "\tis not available in this implementation. This is only mean to read and not modify the files" << std::endl;
    return false;
    
    /*
    string newFileName = fullName(frame);
    pugi::xml_document doc;
    pugi::xml_node main_node = doc.append_child("WRCProject");

    
    //qDebug() << allBoxes;
    
    

    makeHeader(main_node, frame);
    if(includeBoxes(main_node, allBoxes))
    {
        if (!filesDir.exists(newFileName))
        {
            insort(frames, frame);
        }
        //doc.save(std::cout);
        //doc.save_file(newFileName.toStdString().c_str());
        return true;
    }
    else {
        //qDebug() << "************XMLHandler::write" << newFileName << filesDir.exists(newFileName);
        if (filesDir.exists(newFileName))
        {
            filesDir.remove(newFileName);
            int i = frames.indexOf(frame);
            frames.removeAt(i);
        }
    }
    return false;
    */

}

string XMLHandler::imageName(int frame) const
{
    string s = basename_st(fullName(frame, ".jpg"));
    if (s==".") s = "";
    return s;
}

string XMLHandler::imageFullName(int frame) const
{
    string s = fullName(frame, ".jpg");
    if (s==".") s = "";
    return s;
}

int XMLHandler::min() const
{
    return frames.front();
}

int XMLHandler::max() const
{
    return frames.back();
}

int XMLHandler::jump_from(int from, int steps)
{

    int found = bs(frames, from);
    found += steps;
    if (found >= 0 && found < frames.size())
    {
        return frames.at(found);
    }

    return from;

}
void XMLHandler::makeHeader(pugi::xml_node& mainNode, int frame)
{
    
    mainNode.append_child("folder").append_child(pugi::node_pcdata).set_value("WRC");
    mainNode.append_child("filename").append_child(pugi::node_pcdata).set_value(imageName(frame).c_str());

    // <source>
    pugi::xml_node source = mainNode.append_child("source");
    source.append_child("database").append_child(pugi::node_pcdata).set_value("Pixelabs Database");
    source.append_child("annotation").append_child(pugi::node_pcdata).set_value("WRC");
    source.append_child("image").append_child(pugi::node_pcdata).set_value("WRC");

    // <owner>
    pugi::xml_node owner = mainNode.append_child("owner");
    owner.append_child("flickrid").append_child(pugi::node_pcdata).set_value("Pixelabs");
    owner.append_child("name").append_child(pugi::node_pcdata).set_value("Pixelabs");

    // <size>
    pugi::xml_node size = mainNode.append_child("size");
    size.append_child("width").append_child(pugi::node_pcdata).set_value("1920");
    size.append_child("height").append_child(pugi::node_pcdata).set_value("1080");
    size.append_child("depth").append_child(pugi::node_pcdata).set_value("3");

    // <segmented>
    mainNode.append_child("segmented").append_child(pugi::node_pcdata).set_value("0");
    
}

bool XMLHandler::includeBoxes(pugi::xml_node &boxNode, BoxesMap& allBoxes)
{
    
    bool empty {true};
    for (auto it = allBoxes.cbegin(); it!=allBoxes.cend(); it++)  // conts begin() to conts end()
    {
        pugi::xml_node objectNode = boxNode.append_child("object");
        objectNode.append_child("name").append_child(pugi::node_pcdata).set_value(it->first.c_str());
        objectNode.append_child("pose");
        objectNode.append_child("truncated").append_child(pugi::node_pcdata).set_value("0");
        objectNode.append_child("difficult").append_child(pugi::node_pcdata).set_value("1");
        for (Rect box: it->second)
        {
            auto bndbox = objectNode.append_child("bndbox");
            bndbox.append_child("xmin").text().set(static_cast<float>(box.left()));
            bndbox.append_child("xmax").text().set(static_cast<float>(box.right()));
            bndbox.append_child("ymin").text().set(static_cast<float>(box.top()));
            bndbox.append_child("ymax").text().set(static_cast<float>(box.bottom()));
            empty = false;
        }
    }
    return !empty;
}
string XMLHandler::fullName(int frame, const string& extension) const
{
    string result{};
    try
    {
        switch (_s_map.at(extension))
        {
            case XML:
                if (dirname_xmls.empty() || basename_xmls.empty())
                    break;
                result = dirname_xmls + "/" + basename_xmls + to_string(frame) + extension;
                break;
            case JPG:
                if (dirname_xmls.empty() || basename_xmls.empty())
                    break;
                result = dirname_images + "/" + basename_images + to_string(frame) + extension;
                break;
            default:
                break;
        }
    }
    catch (std::out_of_range)
    {}
    //std::cout << "fullName: "<< result << std::endl;
    return result;
        
}

string splitbase(const string& basename, const string& word)
{
    size_t found = basename.rfind(word);
    if (found == std::string::npos)
        return "";
    found += word.length();
    return basename.substr(0, found);
}

string filename2number(const string& filename,const string& word)
{
    //std::cout << "filename2number" << std::endl;
    size_t found = filename.rfind(word);
    //std::cout << found << std::endl;
    if (found == std::string::npos)
        return "";
    size_t dot = filename.rfind(".");
    //std::cout << found << " " << dot << std::endl;
    found += word.length();
    return filename.substr(found, dot - found);
    // return filename.section("_frame", 1, -1).section(".", 0, 0);
}

size_t bs(vector<int> &v, const int x)
{
    size_t lo {0};
    size_t hi {v.size()};
    int mid {-1};
    while (lo < hi)
    {
        mid = (hi+lo)/2;
        if (x <= v[mid])
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

void insort(vector<int> &v, const int x)
{
    vector<int>::iterator it = v.begin();
    int i = bs(v, x);
    it += i;
    v.insert(it, x);
}

/*
vector<string> filesInDir(const string& folder, bool absolute)
{
    vector<string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (folder.c_str())) != NULL) 
    {
        while ((ent = readdir (dir)) != NULL) 
        {
            if (ent->d_type == 0x08)
            {
                string s = string(ent->d_name);
                if (absolute) s = folder+s;
                files.push_back(s);
            }
        }
        closedir (dir);
    } else 
    {
        perror ("");
        return files;
    }
    return files;
}

vector<string> filesInDirFilter(const string& folder, const string& filter)
{
    vector<string> files = filesInDir(folder, true);
    for (auto i = files.size() - 1; i!=-1; i--)
    {
        size_t found_it = files[i].rfind(filter);
        auto it = files.begin() + i;
        if (found_it == std::string::npos)
            files.erase(it);
        else 
            if (found_it + filter.length() != files[i].length())
               files.erase(it); 
    }
    return files;
}


string dirname_st(const string& path)
{
    char buff[path.length()+1];
    strcpy(buff, path.c_str());
    return string(dirname(buff));
}

string basename_st(const string& path)
{
    char buff[path.length()+1];
    strcpy(buff, path.c_str());
    return string(basename(buff));
}
*/
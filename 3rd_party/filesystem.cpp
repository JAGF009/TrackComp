#include <dirent.h>
#include <cstddef> // size_t
#include <cstring> //strcpy
#include <libgen.h> // basename dirname
#include <errno.h> 

#include "filesystem.hpp"

#include <string>
#include <vector>
#include <iostream>
#include "formated_string.hpp"


using namespace std;

std::vector<std::string> filesInDir(const std::string& folder, bool absolute)
{
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (folder.c_str())) != NULL) 
    {
        while ((ent = readdir (dir)) != NULL) 
        {
            if (ent->d_type == 0x08)
            {
                std::string s = std::string(ent->d_name);
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

std::vector<std::string> filesInDirFilter(const std::string& folder, const std::string& filter)
{
    std::vector<std::string> files = filesInDir(folder, true);
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

bool ensureDir(const std::string& path)
{
    std::vector<std::string> splitted = explode(path, '/');
    std::string p = "";
    for (int i = 0; i!=splitted.size() -1; i++)  // splitted.size() -1 avoid file
    {
        p += splitted[i] + "/";
        // std::cout << "Checking for dir: " << p << std::endl;
        if (!isDir(p))
        {
            // std::cout << "Making dir: " << p << std::endl;
            mkdir(p.c_str(), 0777);
        }   
    }
    // std::cout << "ensureDir" << std::endl;
}


std::string dirname_st(const std::string& path)
{
    char buff[path.length()+1];
    strcpy(buff, path.c_str());
    return std::string(dirname(buff));
}

std::string basename_st(const std::string& path)
{
    char buff[path.length()+1];
    strcpy(buff, path.c_str());
    return std::string(basename(buff));
}
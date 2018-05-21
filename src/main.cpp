#include "TrackMeas.hpp"
#include <iostream>
#include "TrackerRe3.hpp"

#include <zmq.hpp>

#include <tclap/CmdLine.h>

bool iequals(const std::string& a, const std::string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}


std::string show_user(pix::TrackerType tt)
{
    ::std::string s{""};
    switch (tt){
        case pix::TrackerType::STRUCK: 
            s = "STRUCK";
            break;
        case pix::TrackerType::Re3:
            s = "Re3";
            break;
        case pix::TrackerType::OpenCV_TLD:
            s = "TLD";
            break;
        case pix::TrackerType::OpenCV_KCF:
            s = "KCF";
            break;
        case pix::TrackerType::OpenCV_MF:
            s = "MedianFlow";
            break;
        case pix::TrackerType::OpenCV_BOOSTING:
            s = "Boosting";
            break;
        case pix::TrackerType::OpenCV_MIL:
            s = "MIL";
            break;
        }
    return s;
}

pix::TrackerType from_user(const std::string& s)
{
    pix::TrackerType tt;
    if (iequals(s, "STRUCK"))
        tt = pix::TrackerType::STRUCK;
    else if (iequals(s, "Re3"))
        tt = pix::TrackerType::Re3;
    else if (iequals(s, "KCF"))
        tt = pix::TrackerType::OpenCV_KCF;
    else if (iequals(s, "MIL"))
        tt = pix::TrackerType::OpenCV_MIL;
    else if (iequals(s, "MedianFlow") || iequals(s, "MF"))
        tt = pix::TrackerType::OpenCV_MF;
    else if (iequals(s, "TLD"))
        tt = pix::TrackerType::OpenCV_TLD;
    else if (iequals(s, "BOOSTING"))
        tt = pix::TrackerType::OpenCV_BOOSTING;
    else
    {
        std::cout << "TRACKER SPECIFIED NOT KNOWN:" << s << " USING STRUCK." << std::endl;
        tt = pix::TrackerType::STRUCK;
    }
        
    return tt;
}

int main(int argc, char** argv)
{
    
    TCLAP::CmdLine cmd("Tracking comparator", ' ', "1.0");

    TCLAP::ValueArg<std::string> trackerType("t", "tracker", "Tracker to use:\n      One of:\n\tSTRUCK\n\tRe3\n\tMIL\n\tMF\n\tKCF\n\tTLD\n\tBOOSTING", false, "STRUCK", "string");
    TCLAP::ValueArg<int> frameSkip("f", "frameskip", "Number of frames to skip", false, 0, "int");
    TCLAP::ValueArg<std::string> numDB("n", "numberDB", "Number of the clip to use", true, "5", "string");
    
    cmd.add(numDB);
    cmd.add(trackerType);
    cmd.add(frameSkip);

    cmd.parse(argc, argv);

    std::string t = trackerType.getValue();
    
    pix::TrackMeas a("/home/dino/TrackingResearch/DB/final/ceil-"+numDB.getValue()+"/", pix::DBType::VOC, from_user(trackerType.getValue()));

    std::cout << "Tracker is: " << show_user(from_user(trackerType.getValue())) << std::endl;
    std::cout << "Skiping: " << frameSkip.getValue() << " frames." << std::endl;
    
    a.setFrameSkip(frameSkip.getValue());
    a.go();
    std::cout << "METRIC FScore    -> " << a.fScore(0.5) << std::endl;
    std::cout << "METRIC OTP       -> " << a.OTP(0.5) << std::endl;
    std::cout << "METRIC ATA       -> " << a.ATA() << std::endl;
    std::cout << "METRIC DEVIATION -> " << a.Deviation() << std::endl;
    return 0;
}
#include "TrackMeas.hpp"
#include <iostream>


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


int main(int argc, char** argv)
{
    std::string n{argv[1]};
    pix::TrackerType tt = pix::TrackerType::STRUCK;
    pix::TrackMeas a("/home/dino/TrackingResearch/DB/final/ceil-"+n+"/", pix::DBType::VOC, tt);
    std::cout << "Tracker is: " << show_user(tt) << std::endl;
    a.go();
    std::cout << "I AM WORKING ON NEW METRICS :'( FScore -> "<< a.fScore(0.5) << std::endl;
    std::cout << "NEW METRIC :) OTP -> " << a.OTP(0.5) << std::endl;
    std::cout << "NEW METRIC :) ATA -> " << a.ATA() << std::endl;
    return 0;
}
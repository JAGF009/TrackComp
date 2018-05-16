#include "TrackMeas.hpp"
#include <iostream>
#include "TrackerRe3.hpp"

#include <zmq.hpp>


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
    /*
    std::string n{argv[1]};
    pix::TrackerType tt = pix::TrackerType::STRUCK;
    pix::TrackMeas a("/home/dino/TrackingResearch/DB/final/ceil-"+n+"/", pix::DBType::VOC, tt);
    std::cout << "Tracker is: " << show_user(tt) << std::endl;
    a.go();
    std::cout << "I AM WORKING ON NEW METRICS :'( FScore -> "<< a.fScore(0.5) << std::endl;
    std::cout << "NEW METRIC :) OTP -> " << a.OTP(0.5) << std::endl;
    std::cout << "NEW METRIC :) ATA -> " << a.ATA() << std::endl;
    */
    pix::TrackerRe3 a;
    std::cout << "WHAT?" << std::endl;
    a.init_track("/home/dino/TrackingResearch/DB/final/ceil-5/images/im_frame0.jpg", pix::Rect(15,26,100,200,"Hola"));
    a.track("/home/dino/TrackingResearch/DB/final/ceil-5/images/im_frame1.jpg");
    return 0;
}
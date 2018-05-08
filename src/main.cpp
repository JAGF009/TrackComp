#include "TrackMeas.hpp"
#include <iostream>


int main(int argc, char** argv)
{
    std::string n{argv[1]};
    pix::TrackMeas a("/home/dino/TrackingResearch/DB/final/ceil-"+n+"/", pix::DBType::VOC, pix::TrackerType::STRUCK);
    //pix::TrackMeas a("/home/dino/PycharmProjects/BGSub/ceil2/", pix::DBType::VOC, pix::TrackerType::STRUCK);
    a.go();
    std::cout << a.fScore(0.5);
    return 0;
}
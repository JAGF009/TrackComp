#include "TrackMeas.hpp"


int main(int argc, char** argv)
{
    // pix::TrackMeas a("/home/dino/TrackingResearch/DB/final/ceil-9/", pix::DBType::VOC, pix::TrackerType::STRUCK);
    pix::TrackMeas a("/home/dino/PycharmProjects/BGSub/ceil2/", pix::DBType::VOC, pix::TrackerType::STRUCK);
    a.go();
    return 0;
}
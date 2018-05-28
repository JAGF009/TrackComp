#include "TrackMeas.hpp"
#include <iostream>
#include "TrackerRe3.hpp"

#include <zmq.hpp>
#include "human.hpp" // To convert from user string to enumeration and viceversa.
#include <tclap/CmdLine.h>

#include "../3rd_party/formated_string.hpp"


int main(int argc, char** argv)
{
    
    TCLAP::CmdLine cmd("Tracking comparator", ' ', "1.0");

    TCLAP::UnlabeledValueArg<std::string> pathFilesArg("path", "Path of the data base to be used", true, "", "path");

    TCLAP::ValueArg<std::string> idArg("", "id", "Identificator of the track", true, "0", "string");

    std::vector<std::string> trackers{"STRUCK", "Re3", "MIL", "KCF", "TLD", "BOOSTING"};
    TCLAP::ValuesConstraint<std::string> allowedTrackers(trackers);
    TCLAP::ValueArg<std::string> trackerTypeArg("t", "", "Tracker to use", true, "STRUCK", &allowedTrackers);

    TCLAP::SwitchArg allTrackers("a", "all", "Set this if you want to run the secuence in all the trackers", false);

    std::vector<std::string> dbs{"VOC", "MOT", "VOT"};
    TCLAP::ValuesConstraint<std::string> allowedDBs(dbs);
    TCLAP::ValueArg<std::string> DBArg("d", "DB", "Data base to use", false, "VOC", &allowedDBs);

    TCLAP::ValueArg<int> frameSkipArg("f", "frameskip", "Number of frames to skip", false, 0, "int");
    
    
    cmd.add(frameSkipArg);
    cmd.add(idArg);
    cmd.add(DBArg);
    cmd.xorAdd(trackerTypeArg, allTrackers);
    cmd.add(pathFilesArg);
    

    cmd.parse(argc, argv);

    if (!allTrackers.getValue())
    {
        std::cout << "PATH TO FILE     -> " << pathFilesArg.getValue() << std::endl;
        std::cout << "ID to track      -> " << idArg.getValue() << std::endl;
        std::cout << "Tracker          -> " << show_user(from_user_t(trackerTypeArg.getValue())) << std::endl;
        std::cout << "Data base type   -> " << show_user(from_user_db(DBArg.getValue())) << std::endl;
        std::cout << "Frames to skip   -> " << frameSkipArg.getValue() << std::endl;
        
        pix::TrackMeas a(pathFilesArg.getValue(), idArg.getValue(), from_user_db(DBArg.getValue()), from_user_t(trackerTypeArg.getValue()));
        
        a.setFrameSkip(frameSkipArg.getValue());
        a.go();

        std::cout << "FScore    -> " << a.fScore(0.5) << std::endl;
        std::cout << "OTA       -> " << a.OTA(0.5) << std::endl;
        std::cout << "OTP       -> " << a.OTP(0.5) << std::endl;
        std::cout << "ATA       -> " << a.ATA() << std::endl;
        std::cout << "DEVIATION -> " << a.Deviation() << std::endl;
    }
    else 
    {
        // std::cout << "RUNNING SEQUENCE IN ALL TRACKERS" << std::endl;
        std::vector<std::string> separated = explode(pathFilesArg.getValue(), '/');
        auto sep_size = separated.size();

        // std::cout << "RESULTS WILL BE SAVED ON: " << "results/"+join({separated[sep_size - 2], separated[sep_size - 1]}, '-') + "-" + idArg.getValue() + "-" + "tracker" +".csv" << std::endl;
        std::string path_base = "results/"+join({separated[sep_size - 2], separated[sep_size - 1]}, '-') + "-" + idArg.getValue() + "/";
        
        std::vector<pix::TrackerType> trackers{
            pix::TrackerType::STRUCK, 
            pix::TrackerType::Re3, 
            pix::TrackerType::OpenCV_KCF,
            pix::TrackerType::OpenCV_TLD, 
            pix::TrackerType::OpenCV_MF,
            pix::TrackerType::OpenCV_BOOSTING, 
            pix::TrackerType::OpenCV_MIL
        };
        
        for (auto tracker: trackers)
        {
            pix::TrackMeas a(pathFilesArg.getValue(), idArg.getValue(), from_user_db(DBArg.getValue()), tracker);
        
            a.setFrameSkip(frameSkipArg.getValue());
            // std::cout << path_base + show_user(tracker) + ".csv" << std::endl;
            a.goStoreResults(path_base + show_user(tracker) + ".csv");
        }
        
        
    }
    return 0;
}
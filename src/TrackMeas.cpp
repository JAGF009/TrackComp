#include "TrackMeas.hpp"



#ifndef SHOW___
#include <thread>


// FOR TERMINAL
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

class BufferToggle
{
    private:
        struct termios oldAttr, newAttr;
        int oldFlags, newFlags;
        int fd = fileno(stdin);

        /*
         * Disables buffered input
         */

        void off(void)
        {
            // std::cout << "OFF BUFFERED error=";

            int err = tcgetattr(fd, &oldAttr); //get the current terminal I/O structure
            newAttr = oldAttr;
            // std::cout << err << std::endl;

            newAttr.c_iflag = 0; /* input mode */
            newAttr.c_oflag = 0; /* output mode */
            newAttr.c_lflag &= ~ICANON; /* line settings */
            newAttr.c_cc[VMIN] = 1; /* minimum chars to wait for */
            newAttr.c_cc[VTIME] = 1; /* minimum wait time */
            oldFlags = fcntl(fd, F_GETFL, O_NONBLOCK);
            tcsetattr(fd, 0, &newAttr); //Apply the new settings
        }


        /*
         * Enables buffered input
         */

        void on(void)
        {
            // std::cout << "ON BUFFERED: error=";
            int err = tcsetattr(fd, TCSANOW, &oldAttr);
            // std::cout << err << std::endl;
            fcntl(fd, F_SETFL, oldFlags);
        }

    public:
        BufferToggle(){off();}
        ~BufferToggle(){on();}

        int getKey()
        {
            // std::cout << "GETTING KEY" << std::endl;
            char ch;
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 10000; // small 0.01 msec delay
            // std::cout << "LOOK" << std::endl;
            int looked = select(1, NULL, NULL, NULL, &tv);
            // std::cout << "LOOKED: " << looked << std::endl;


            int error = (read(fd, &ch, 1) != 1);
            // std::cout << "ERROR: " << error << std::endl;
            return (error ? -1 : (int) ch);
        }
};

void stop_in_thread(pix::TrackMeas* tm)
{
    BufferToggle bf;
    while (!tm->stopped())
    {
        int erino = bf.getKey();
        if (erino == 27) tm->stop();
    }
}

#endif


#include "PIXReader.hpp"

#include <cstdio>

#include "../3rd_party/filesystem.hpp"

#include <algorithm>
#include <cmath>


using namespace pix;
using namespace std;

std::string mul_string(const std::string& s, int n)
{
    std::string newstring{""};
    if (n <= 0) return newstring;
    newstring += s;
    while(--n)
        newstring += s;  
    return newstring;
}


void drawRect(cv::Mat& im, pix::Rect r, cv::Scalar color = cv::Scalar(0, 0, 0), int thickness = 1)
{
        cv::rectangle(im, r.toOpenCV(), color, thickness);
}


TrackMeas::TrackMeas(const std::string& path, const std::string& id, pix::DBType db_type, pix::TrackerType track) : m_id(id)
{

    tracker = pix::make_tracker(track);
    db = pix::make_dbreader(db_type, path);
}

TrackMeas::~TrackMeas()
{
    cv::destroyAllWindows();
}
bool TrackMeas::idInFrame(m_int frame, const std::string& id, std::unordered_set<std::string>& ids) const
{
    if (frame > db->nFrames()) throw std::runtime_error("Frame too big");
    auto boxes = db->getBBFrame(frame);
    for (auto box : boxes)
    {
        ids.insert(box.id());
        if (box.id() == id)
            return true;
    }

    return false;
}
void TrackMeas::go()
{
#ifndef SHOW___
    std::thread thread1 (stop_in_thread, this);
    thread1.detach(); // I dont like to do this, but anyhow...
#endif
    std::cout << "\rPRESS ESC TO STOP AT ANY TIME." << "\n\r";
    std::cout.flush();
    const int db_size = db->nFrames();
    frame_number = -1;
    std::unordered_set<std::string> ids{};
    try
    {
        while (!idInFrame(++frame_number, m_id, ids)) {}
    } catch (std::runtime_error)
    {
        TermStyle ts;
        std::cout << ts.sfatal(std::string ("ID '" + m_id + "' does not exist in the data base!")) << std::endl;
        std::cout << "Posible id values are:" << std::endl;
        for (auto s : ids) std::cout << "\t" << s << std::endl;
        std::cout << std::endl;
        return;
    }
    
    std::string name = db->imageName(frame_number);

    pix::Rect oldBB;
    oldBB = db->getBBFrameID(frame_number++, m_id);
    image = cv::imread(name);
    m_width = image.cols;
    m_height = image.rows;

    switch(tracker->getMode())
    {
        case pix::TrackerInterface::Mode::Image:
        {
            init_track(image, oldBB);
            break;
        }  
        case pix::TrackerInterface::Mode::Path:
            tracker->init_track(name, oldBB);
            break;
        default: 
            std::cout << "Unkwonw mode!" << std::endl;
    }
    
    while (1)
    {
        int n = 100 * frame_number / db_size;
        std::cout << "\r ("<< frame_number << "/" << db_size << ") [" << mul_string("#", n) << mul_string(" ", 100-n) << "]" << " " << n << "%";
        std::cout.flush();
        name = db->imageName(frame_number); 
        if (name.empty()) break;
        auto realBB = db->getBBFrameID(frame_number++, m_id);
        pix::Rect newBB;
        image = cv::imread(name);
        switch(tracker->getMode())
        {
            case pix::TrackerInterface::Mode::Image:
            {
                newBB = tracker->track(image);
                break;
            }  
            case pix::TrackerInterface::Mode::Path:
                newBB = tracker->track(name);
                break;
        }
        pix::Point m = newBB.movement(oldBB); // Unused.
        newFrame(realBB, newBB); // To calculate the metrics

#ifdef SHOW___
        show(realBB, newBB); // Allow escape key to stop the process cleanly       
#endif
        frame_number += m_frameSkip;
        oldBB = newBB;
        if (m_stop) break;
    }
    std::cout << "\n\r";
    std::cout.flush();
    stop();
}

void TrackMeas::goStoreResults(const std::string& path)
{
    ensureDir(path);
    store = true;
    storage.open(path, ios::out | ios::trunc);
    storage << "FRAME_N,GT_X,GT_Y,GT_W,GT_H,TRACK_X,TRACK_Y,TRACK_W,TRACK_H\n";
    go();
    storage << "METRIC,VALUE\n";
    storage << "FSCORE," << fScore(0.5) << '\n'; 
    storage << "ATA," << ATA() << '\n'; 
    storage << "OTA," << OTA(0.5) << '\n'; 
    storage << "OTP," << OTP(0.5) << '\n'; 
    storage << "DEVIATION," << Deviation() << '\n'; 
    store = false;
    storage.close();
}

void TrackMeas::init_track(const cv::Mat& im, const pix::Rect& r)

{
    tracker->init_track(im, r);
}

void TrackMeas::show(const Rect& gt, const Rect& tr, int time)
{
    cv::rectangle(image, gt.toOpenCV(), cv::Scalar(255, 255, 255), 3);
    cv::rectangle(image, tr.toOpenCV(), tracker->color(), 3);
    real_traj.draw(image, cv::Scalar(255, 255, 255));
    detectec_traj.draw(image, tracker->color());
    cv::imshow("m_name", image);
    if(cv::waitKey(time) == 27) stop();
}

void TrackMeas::newFrame(const Rect& gt, const Rect& track)
{
    if (!gt.valid() && !track.valid()) return;
    
    n_frames++;
    std::stringstream ss;
    ss << frame_number;

    if (!gt.valid())
    {
        n_false_positives++;
        detectec_traj.push(track);
        ss << ",0,0,0,0," << track.X() << "," << track.Y() << "," << track.W() << "," << track.H() << '\n';
        if (store) storage << ss.str(); // storage.write(ss.str().c_str());
        return;
    }

    if (!track.valid())
    {
        n_gts++;
        n_false_negatives++;
        real_traj.push(gt);
        ss << "," << gt.X() << "," << gt.Y() << "," << gt.W() << "," << gt.H() << ",0,0,0,0" << '\n';
        if (store) storage << ss.str(); // storage.write(ss.str().c_str());
        return;
    }
    ss << "," << gt.X() << "," << gt.Y() << "," << gt.W() << "," << gt.H() << "," << track.X() << "," << track.Y() << "," << track.W() << "," << track.H() << '\n';
    if (store) storage << ss.str(); // storage.write(ss.str().c_str());
    n_gts++;
    m_fScore.emplace_back(gt.IoU(track));
    m_f1Score.emplace_back(gt.F1Intermediate(track));
    real_traj.push(gt);
    detectec_traj.push(track);
    m_distances.emplace_back(gt.distance(track));
}


double TrackMeas::fScore(double threshold) const noexcept
{
    long int tp = std::count_if(m_fScore.begin(), m_fScore.end(), Comp(threshold));
    m_int local_false_positives = n_false_positives + m_fScore.size() - tp;
    if (tp == 0 && n_false_negatives == 0 && local_false_positives == 0) return 0.0;
    // std::cout << "tp: " << tp << " n_false_negatives: " << n_false_negatives << " n_false_positives: " << n_false_positives << std::endl;
    double precision = ((double) tp) / (tp + local_false_positives);
    double recall = ((double) tp) / (tp + n_false_negatives);
    return 2 * precision * recall / (precision + recall);
}

double TrackMeas::f1Score() const noexcept
{
    return 0;
}
double TrackMeas::OTA(double threshold) const noexcept
{
    if (n_gts == 0) return 0;
    long int tp = std::count_if(m_fScore.begin(), m_fScore.end(), Comp(threshold));
    m_int local_false_positives = n_false_positives + m_fScore.size() - tp;
    return 1 - (((double) n_false_negatives + (double) local_false_positives) / (double) n_gts);
}
double TrackMeas::OTP(double threshold) const noexcept
{
    auto ms = std::count_if(m_fScore.begin(), m_fScore.end(), Comp(threshold));
    auto n = std::accumulate(m_fScore.begin(), m_fScore.end(), (double) 0, [&](double& s, const double& d) -> double {if (d >= threshold) return s + d; return s;});
    if (ms <= 0) return 0;
    return ((double)n) / ms;
}

double TrackMeas::ATA() const noexcept
{
    if (n_frames == 0) return 0;
    return std::accumulate(m_fScore.begin(), m_fScore.end(), (double) 0) / n_frames;
}

double TrackMeas::Deviation() const noexcept
{
    if (n_frames == 0) return 0;
    double norm {sqrt(pow(m_width, 2)+ pow(m_height, 2))};
    return (1 -(std::accumulate(m_distances.begin(), m_distances.end(), (double) 0) / norm) / n_frames);
}
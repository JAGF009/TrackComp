#define SHOW___

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


TrackMeas::TrackMeas(const std::string& path, pix::DBType dt_type, pix::TrackerType track)
{

    tracker = pix::make_tracker(track);
    db = std::make_unique<PixReader>(path);
}

TrackMeas::~TrackMeas()
{
    cv::destroyAllWindows();
}

void TrackMeas::go()
{
#ifndef SHOW___
    std::thread thread1 (stop_in_thread, this);
    thread1.detach(); // I dont like to do this, but anyhow...
#endif
    std::cout << "PRESS ESC TO STOP AT ANY TIME." << std::endl;
    pix::Rect oldBB, newBB;
    const int db_size = db->nFrames();
    int frame_number = 0;
    std::string name {db->imageName(frame_number)};
    
    oldBB = db->getBBFrameID(frame_number++, "Jose");
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
    }
    
    while (1)
    {
        int n = 100 * frame_number / db_size;
        // std::cout << "\r ("<< frame_number << "/" << db_size << ") [" << mul_string("#", n) << mul_string(" ", 100-n) << "]" << " " << n << "%";
        // std::cout.flush();
        name = db->imageName(frame_number); 
        if (name.empty()) break;
        auto realBB = db->getBBFrameID(frame_number++, "Jose");
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
        pix::Point m = newBB.movement(oldBB);
        // std::cout << "Movement x: " << m.x << " y:" << m.y << std::endl;
        newFrame(realBB, newBB); // To calculate the metrics

#ifdef SHOW___
        show(realBB, newBB); // Allow escape key to stop the process cleanly       
#endif
        frame_number += m_frameSkip;
        oldBB = newBB;
        if (m_stop) break;
    }
    std::cout << endl;
    stop();
}

void TrackMeas::init_track(const cv::Mat& im, const pix::Rect& r)

{
    tracker->init_track(im, r);
}

void TrackMeas::show(const Rect& gt, const Rect& tr)
{
    cv::rectangle(image, gt.toOpenCV(), cv::Scalar(255, 0, 0), 3);
    cv::rectangle(image, tr.toOpenCV(), cv::Scalar(0, 0, 255), 3);
    real_traj.draw(image, cv::Scalar(255, 0, 0));
    detectec_traj.draw(image, cv::Scalar(0, 0, 255));
    cv::imshow("m_name", image);
    if(cv::waitKey(1) == 27) stop();
}

void TrackMeas::newFrame(const Rect& gt, const Rect& track)
{
    if (!gt.valid() && !track.valid()) return;
    
    n_frames ++;
    if (!gt.valid())
    {
        n_false_positives++;
        return;
    }
    if (!track.valid())
    {
        n_gts++;
        n_false_negatives++;
        return;
    }
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
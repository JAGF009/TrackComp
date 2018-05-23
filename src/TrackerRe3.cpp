#include "TrackerRe3.hpp"
#include <iostream>
#include <sstream>
#include <utility>

#include "../3rd_party/formated_string.hpp"



using namespace pix;

class ZMQEasyClient 
{
    const std::string dir;

    public:
        static zmq::context_t context;
        static zmq::socket_t socket;

        static const std::string END;
        static const std::string OK;
        static const std::string INIT;
        static const std::string KEEP;
    


        ZMQEasyClient(const std::string& ddir) : dir(ddir) {}
        std::string send(const std::string& s) const 
        {
            //zmq::context_t context (1);
            //zmq::socket_t socket(context, ZMQ_REQ);
            socket.connect(dir.c_str());
            zmq::message_t msg(s.size());
            memcpy(msg.data(), s.c_str(), s.size());
            socket.send(msg);
            zmq::message_t reply;
            socket.recv(&reply);
            char buf[reply.size() + 1];
            memcpy(buf, reply.data(), reply.size());
            buf[reply.size()] = '\0';
            return std::move(std::string(buf));
        }
    };
zmq::context_t ZMQEasyClient::context (1);
zmq::socket_t ZMQEasyClient::socket (context, ZMQ_REQ);

const std::string ZMQEasyClient::END = "END";
const std::string ZMQEasyClient::OK = "OK";
const std::string ZMQEasyClient::INIT = "INIT";
const std::string ZMQEasyClient::KEEP = "KEEP";

TrackerRe3::TrackerRe3() : proc({"python", "/home/dino/TrackingResearch/re3-tensorflow/demo/demo_zmq.py"}, subprocess::output{subprocess::PIPE}, subprocess::error{subprocess::PIPE})
{
    setMode(TrackerInterface::Mode::Path);
    std::cout << "Process opened" << std::endl;
}

TrackerRe3::~TrackerRe3()
{
    ZMQEasyClient client("ipc:///tmp/qwiduhausyhd:5555");
    auto z = client.send(ZMQEasyClient::END); // This could block eternally, I dont know if it is ok to assume that the process is alive.
    proc.kill(); // In case process did not end, we sent sig 9 to kill it, wont do anything if already killed.
}

void TrackerRe3::init_track(const cv::Mat& im, const pix::Rect r)
{
        std::cout << "TrackerRe3::init_track(const cv::Mat& im, const pix::Rect r)" << std::endl;
}

void TrackerRe3::init_track(const std::string& path, const pix::Rect r)
{
    ZMQEasyClient client("ipc:///tmp/qwiduhausyhd:5555");
    std::string s = join(
        {client.INIT, 
        path,
        r.id(), 
        std::to_string(r.left()),
        std::to_string(r.top()),
        std::to_string(r.right()),
        std::to_string(r.bottom())}, 
        ',');
    std::string z = client.send(s);
    // std::cout << "INIT RESPONSE: " << z << std::endl;
}

pix::Rect TrackerRe3::track(const std::string& path)
{
    ZMQEasyClient client("ipc:///tmp/qwiduhausyhd:5555");
    std::string s = join(
        {client.KEEP, 
        path},
        ',');
    std::string z = client.send(s);
    auto v = explode(z, ',');
    pix::Rect rect;
    if (v[0]==client.OK)
    {
        // std::cout << v[0] << " " << v[1] << " " << v[2]<< " " << v[3]<< " " << v[4] << std::endl;
        rect.setX(std::stoi(v[1]));
        rect.setY(std::stoi(v[2]));
        rect.setW(std::stoi(v[3]));
        rect.setH(std::stoi(v[4]));

        // std::cout << "RECT: " << rect.X() << " " << rect.Y() << " " << rect.W() << " " << rect.H() << std::endl;
    }
    // std::cout << z << std::endl;

    return rect;
}  
pix::Rect TrackerRe3::track(const cv::Mat&)
{
    return pix::Rect(0,0,0,0,"no");
}    
#include "TrackerRe3.hpp"
#include <iostream>
#include <sstream>
#include <utility>

#include "../3rd_party/formated_string.hpp"


using namespace pix;

std::string join(const std::vector<std::string>& v, char c)
{
    std::stringstream ss;
    for (int i = 0; i!=v.size() -1; i++)
    {
        ss << v[i] << c;
    }
    ss << v.back();
    return ss.str();
}

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

TrackerRe3::TrackerRe3()
{
    setMode(TrackerInterface::Mode::Path);
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
        std::to_string(r.bottom()),
        std::to_string(r.right())}, 
        ',');
    std::string z = client.send(s);
    std::cout << "RESPONSE: " << z << std::endl;
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
    if (v[0]==client.OK)
    {
        std::cout << v[0] << " " << v[1] << " " << v[2]<< " " << v[3]<< " " << v[4] << std::endl;
        z = client.send(ZMQEasyClient::END);
        std::cout << z << std::endl;
    } else {
        std::cout << z << std::endl;
    }
        
    return pix::Rect(0,0,0,0,"no");
}  
pix::Rect TrackerRe3::track(const cv::Mat&)
{
    return pix::Rect(0,0,0,0,"no");
}    
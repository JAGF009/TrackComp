#ifndef TRACKER_FACTORY_H_PIX__
#define TRACKER_FACTORY_H_PIX__

#include "TrackerBasic.hpp"
#include "EnumsConst.hpp"
#include <memory>

namespace pix {
    std::unique_ptr<pix::TrackerInterface> make_tracker(pix::TrackerType tt);
}

#endif
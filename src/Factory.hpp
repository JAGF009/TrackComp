#ifndef TRACKER_FACTORY_H_PIX__
#define TRACKER_FACTORY_H_PIX__

#include "TrackerBasic.hpp"
#include "DBReader.hpp"
#include "EnumsConst.hpp"
#include <memory>

namespace pix {
    std::unique_ptr<pix::TrackerInterface> make_tracker(pix::TrackerType tt);
    std::unique_ptr<DBReader> make_dbreader(pix::DBType dbt, const std::string& path);
}

#endif
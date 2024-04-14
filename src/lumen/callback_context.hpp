#pragma once

#include "lumen/activity/context.hpp"
#include "lumen/net/wifi.hpp"

namespace lumen {
namespace net {

class WiFi;

}

struct CallbackContext {
    activity::Context* activity_context;
    net::WiFi* wifi;
};

} // namespace lumen

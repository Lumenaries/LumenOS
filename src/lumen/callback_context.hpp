#pragma once

#include "lumen/activity/context.hpp"
#include "lumen/net/wifi.hpp"

namespace lumen {

struct CallbackContext {
    CallbackContext(activity::Context* a, net::WiFi* w) {
        activity_context = a;
        wifi = w;
        test = nullptr;
    }

    activity::Context* activity_context;
    net::WiFi* wifi;
    void* test;
};

} // namespace lumen

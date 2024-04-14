#pragma once

#include "lumen/activity/context.hpp"
#include "lumen/callback_context.hpp"

#include "esp_wifi.h"

#include <string>

namespace lumen {

struct CallbackContext;

namespace net {

class WiFi {
public:
    WiFi();

    [[nodiscard]] static std::string get_password();

    void register_callback(CallbackContext& callback_context);

    void reset();

private:
    void randomize_password();
    void log_credentials();
};

} // namespace net

} // namespace lumen

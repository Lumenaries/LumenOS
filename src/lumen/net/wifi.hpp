#pragma once

#include "lumen/activity/context.hpp"

#include "esp_wifi.h"

#include <stdint.h>
#include <string>

namespace lumen::net {

class WiFi {
public:
    WiFi(activity::Context& context);

    [[nodiscard]] static std::string get_password();

    void restart();
    void randomize_password();

private:
    void log_credentials();
};

} // namespace lumen::net

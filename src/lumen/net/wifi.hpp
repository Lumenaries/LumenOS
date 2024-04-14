#pragma once

#include "lumen/activity/context.hpp"

#include <string>

namespace lumen::net {

void init_wifi();
void register_wifi_callback(activity::Context* activity_context);
[[nodiscard]] std::string get_wifi_password();
void reset_wifi();

} // namespace lumen

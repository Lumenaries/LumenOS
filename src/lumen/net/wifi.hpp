#pragma once

#include "lumen/activity/context.hpp"

#include <string>

namespace lumen::net {

void init_wifi(activity::Context& activity_context);
[[nodiscard]] std::string get_wifi_password();
void disconnect_user();

} // namespace lumen

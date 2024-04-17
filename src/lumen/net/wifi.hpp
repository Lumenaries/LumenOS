#pragma once

#include "lumen/activity/context.hpp"

#include <string>

namespace lumen::net {

/** Initialize the Wi-Fi as a soft access point.
 *
 * \param activity_context The activity context.
 */
void init_wifi(activity::Context& activity_context);

[[nodiscard]] std::string get_wifi_password();

// Disconnect the user from the softAP and randomize the password.
void disconnect_user();

} // namespace lumen::net

#pragma once

#include "lumen/activity/context.hpp"

#include "esp_http_server.h"

namespace lumen::web {

/// Handles the creation and destruction of HTTP web servers.
struct Server {
    httpd_handle_t server = nullptr;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    explicit Server(activity::Context& context);
    ~Server();
};

} // namespace lumen::web

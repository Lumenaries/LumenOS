#pragma once

#include "lumen/activity/context.hpp"

#include "esp_http_server.h"
#include "nlohmann/json.hpp"

#include <list>

namespace lumen::web {

/// Handles the creation and destruction of HTTP web servers.
struct Server {
    httpd_handle_t server = nullptr;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /** Server constructor.
     *
     * \param context A reference to a context object.
     */
    explicit Server(activity::Context& context);
    ~Server();

    activity::Context* get_activity_context();

private:
    activity::Context* activity_context_;

    std::list<int> session_sockets_;
};

} // namespace lumen::web

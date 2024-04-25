#pragma once

#include "lumen/activity/context.hpp"

#include "esp_http_server.h"
#include "nlohmann/json.hpp"

#include <list>

namespace lumen::web {

/// Handles the creation and destruction of HTTP web servers.
class Server {
public:
    /** Server constructor.
     *
     * \param context A reference to a context object.
     */
    explicit Server(activity::Context& activity_context);
    ~Server();

    [[nodiscard]] activity::Context* get_activity_context() const;

private:
    httpd_handle_t handle_ = nullptr;
    httpd_config_t config_ = HTTPD_DEFAULT_CONFIG();

    activity::Context* activity_context_;

    std::list<int> session_sockets_;
};

} // namespace lumen::web

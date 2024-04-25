#pragma once

#include "lumen/activity/context.hpp"
#include "lumen/web/event/stream.hpp"

#include "esp_http_server.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nlohmann/json.hpp"

#include <memory>

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

    esp_err_t set_event_stream(httpd_req_t* request);

    void send_event_message(EventMessage const& message);

    void set_event_stream_socket(int socket_fd);

    [[nodiscard]] int get_event_stream_socket() const;

private:
    httpd_handle_t handle_ = nullptr;
    httpd_config_t config_ = HTTPD_DEFAULT_CONFIG();

    activity::Context* activity_context_;

    int event_socket_fd_{};

    std::unique_ptr<event::Stream> event_stream_{};
};

} // namespace lumen::web

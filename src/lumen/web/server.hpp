#pragma once

#include "lumen/activity/context.hpp"

#include "esp_http_server.h"

namespace lumen::web {

esp_err_t dispatch_event_handler(httpd_req_t* request);

struct EventMessage {
    enum class Type {
        none,
        event_stream_closed,
        event_stream_started,
        event_occurred,
    };

    Type type{};
    httpd_req_t* new_request{};

    explicit EventMessage(Type type = Type::none) : type{type} {}

    EventMessage(Type type, httpd_req_t* new_request)
        : type{type}, new_request{new_request}
    {
    }
};

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

    void send_event_message(EventMessage const& message);

    void set_event_stream_socket(int socket_fd);

    [[nodiscard]] int get_event_stream_socket() const;

private:
    httpd_handle_t handle_ = nullptr;
    httpd_config_t config_ = HTTPD_DEFAULT_CONFIG();

    activity::Context* activity_context_;

    int event_socket_fd_{};
};

} // namespace lumen::web

#pragma once

#include "lumen/activity/context.hpp"

#include "esp_http_server.h"

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

    int event_socket_fd_{};
};

/// Struct that represents a message to the event stream handler task.
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

/** Attempt to pass a request to the event stream handler task.
 *
 * \param request Event-stream request that needs to be handled asynchronously.
 *
 * \returns `ESP_FAIL` if the request was unable to be handled.
 *
 * \returns `ESP_OK` if the request was successfully passed off to the event
 * stream handler task.
 */
esp_err_t dispatch_event_handler(httpd_req_t* request);

/** Send a message to the event stream handler task.
 *
 * \param message The message to be passed on to the event handler task.
 */
void send_event_message(EventMessage const& message);

} // namespace lumen::web

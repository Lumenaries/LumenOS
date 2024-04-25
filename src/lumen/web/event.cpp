#include "lumen/web/event.hpp"

#include "lumen/web/server.hpp"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

namespace lumen::web {
namespace {

constexpr auto tag = "web/event";

SemaphoreHandle_t event_stream_semaphore{};
QueueHandle_t event_stream_queue{};

} // namespace

EventMessage::EventMessage(Type type /* = Type::none */) : type{type} {}

EventMessage::EventMessage(Type type, httpd_req_t* new_request)
    : type{type}, new_request{new_request}
{
}

esp_err_t dispatch_event_handler(httpd_req_t* request)
{
    httpd_req_t* copy = nullptr;

    auto error = httpd_req_async_handler_begin(request, &copy);

    if (error != ESP_OK) {
        return error;
    }

    auto handler_message =
        EventMessage{EventMessage::Type::event_stream_started, copy};

    if (xSemaphoreTake(event_stream_semaphore, 0) == pdFALSE) {
        ESP_LOGE(tag, "No workers are available");
        httpd_req_async_handler_complete(copy); // cleanup
        return ESP_FAIL;
    }

    if (xQueueSend(event_stream_queue, &handler_message, 0) == pdFALSE) {
        ESP_LOGE(tag, "worker queue is full");
        httpd_req_async_handler_complete(copy); // cleanup
        return ESP_FAIL;
    }

    auto* server =
        static_cast<Server*>(httpd_get_global_user_ctx(request->handle));

    server->set_event_stream_socket(httpd_req_to_sockfd(copy));

    return ESP_OK;
}

} // namespace lumen::web

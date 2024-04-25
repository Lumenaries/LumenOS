#include "lumen/web/event/stream.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

namespace lumen::web::event {
namespace {

constexpr auto tag = "web/event/stream";

QueueHandle_t event_stream_queue = xQueueCreate(1, sizeof(EventMessage));

} // namespace

Stream::Stream(httpd_req_t* request) {}

} // namespace lumen::web::event

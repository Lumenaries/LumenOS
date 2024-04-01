#include "lumen/app_task.hpp"

#include "lumen/web/server.hpp"

#include "freertos/task.h"

namespace lumen {
namespace {

constexpr auto tag = "app_task";

} // namespace

void app_task(void* /* parameters */)
{
    auto web_server = web::Server{};

    while (true) {
        vTaskDelay(100);
    }
}

} // namespace lumen

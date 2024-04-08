#include "lumen/app_task.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/web/server.hpp"

#include "freertos/task.h"

namespace lumen {
namespace {

constexpr auto tag = "app_task";

} // namespace

void app_task(void* /* parameters */)
{
    auto activity_context = activity::Context{activity::Type::football};

    auto web_server = web::Server{activity_context};

    while (true) {
        vTaskDelay(100);
    }
}

} // namespace lumen

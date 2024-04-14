#include "lumen/button_callback.hpp"

#include "esp_log.h"

namespace lumen {
namespace {

constexpr auto tag = "button_callback";

} // namespace

void power_button_long_press(void* /* button_handle */, void* callback_context)
{
    // TODO: Check the state of the system.
    // If we are in low power mode, we should flash the battery status.
    // If we are not in low power mode, we should restart the Wi-Fi.
    ESP_LOGI(tag, "Registered a long click from the power button");

    auto* context = static_cast<CallbackContext*>(callback_context);

    context->wifi->reset();
    context->activity_context->set_activity(activity::Type::connect);
}

} // namespace lumen

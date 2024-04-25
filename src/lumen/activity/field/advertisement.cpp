#include "lumen/activity/field/advertisement.hpp"

#include "esp_log.h"

namespace lumen::activity::field {
namespace {

constexpr auto tag = "activity/field/advertisement";

}

Advertisement::Advertisement(std::string const& ad) : Field{ad}
{
    // Load in all of the advertisements from "/data/advertisements.txt"
}

void Advertisement::set_value(std::string const& value) {}

std::string Advertisement::to_string() const
{
    return {};
}

void Advertisement::display(hardware::Display* display)
{
    auto display_width = 96;

    static auto current_x = display_width - 1;

    auto const* value = get_value().c_str();

    int16_t throwaway{};

    uint16_t string_width{};
    uint16_t string_height{};

    display->getTextBounds(
        value, 0, 0, &throwaway, &throwaway, &string_width, &string_height
    );

    ESP_LOGI(
        tag, "string_width: %d, string_height: %d", string_width, string_height
    );

    display->setTextWrap(false);
    display->setTextSize(2);

    display->drawFastHLine(
        0, 37, display_width, hardware::Display::color565(128, 128, 128)
    );

    display->setCursor(current_x, 39);
    display->print(value);

    current_x--;

    if (current_x < -string_width) {
        current_x = display_width - 1;
        is_displaying_ = false;
    } else {
        is_displaying_ = true;
    }
}

bool Advertisement::is_displaying() const
{
    return is_displaying_;
}

bool Advertisement::should_display(uint64_t time) const
{
    if (time % display_interval_ == 0 || is_displaying_) {
        return true;
    }

    return false;
}

} // namespace lumen::activity::field

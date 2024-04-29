#include "lumen/activity/field/advertisement.hpp"

#include "lumen/activity/activity.hpp"

#include "esp_log.h"

namespace lumen::activity::field {
namespace {

constexpr auto tag = "activity/field/advertisement";

bool timer_alarm_callback(
    gptimer_handle_t timer,
    gptimer_alarm_event_data_t const* timer_data,
    void* context
);

} // namespace

Advertisement::Advertisement(
    uint64_t display_interval,
    std::map<int, std::string> const& advertisements
)
    : Field{}, display_interval_{display_interval},
      advertisements_{&advertisements},
      // We should never have a key that is negative
      current_ad_key_{
          advertisements_->size() ? advertisements_->begin()->first : -1
      },
      timer_{50'000, timer_alarm_callback, this}
{
    // Load in the first advertisement in the map if it is nonempty
    if (current_ad_key_ >= 0) {
        auto second = advertisements_->find(current_ad_key_)->second;
        set_value_only(second);
    }
}

std::string Advertisement::to_string() const
{
    return {};
}

void Advertisement::display(hardware::Display* display)
{
    if (current_ad_key_ < 0 && advertisements_->size() > 0) {
        auto const& first_el = advertisements_->begin();
        current_ad_key_ = first_el->first;

        set_value_only(first_el->second);
    }

    auto display_width = 96;

    static auto current_x = display_width - 1;

    auto const* value = get_value().c_str();

    int16_t throwaway{};

    uint16_t string_width{};
    uint16_t string_height{};

    display->getTextBounds(
        get_value().c_str(),
        0,
        0,
        &throwaway,
        &throwaway,
        &string_width,
        &string_height
    );

    display->setTextWrap(false);
    display->setTextSize(2);

    display->setCursor(current_x, 50);
    display->setTextColor(g_primary_color);
    display->print(get_value().c_str());
    display->fillRect(0, 50, 23, 16, 0);
    display->drawFastVLine(24, 50, 16, 0);

    current_x -= 1;

    if (current_x < -string_width + 23) {
        current_x = display_width - 1;
        is_displaying_ = false;

        auto ad = advertisements_->find(current_ad_key_);

        if (ad == advertisements_->end() ||
            std::next(ad) == advertisements_->end()) {
            // The element we were pointing at was deleted or it was the last
            // ad. Reset back to first
            ESP_LOGI(
                tag,
                "The element we were pointing at was deleted or it was the "
                "last ad. Reset back to first"
            );

            auto const& first_ad = advertisements_->begin();

            if (first_ad != advertisements_->end()) {
                ESP_LOGI(tag, "Setting to first ad...");

                current_ad_key_ = first_ad->first;
                set_value_only(first_ad->second);
            } else {
                ESP_LOGI(tag, "Map is empty 2");

                current_ad_key_ = -1;
                set_value_only({});
            }
        } else {
            ESP_LOGI(tag, "Setting to next element...");

            // Set to next element
            current_ad_key_ = ad->first;
            set_value_only(ad->second);
        }

    } else {
        is_displaying_ = true;
    }
}

bool Advertisement::is_displaying() const
{
    return is_displaying_;
}

bool Advertisement::should_display(uint64_t time)
{
    if ((time % display_interval_ == 0 || is_displaying_) &&
        advertisements_->size() > 0) {
        timer_.start();
        return true;
    }

    timer_.stop();
    return false;
}

namespace {

bool timer_alarm_callback(
    gptimer_handle_t timer,
    gptimer_alarm_event_data_t const* timer_data,
    void* context
)
{
    auto* field = static_cast<Advertisement*>(context);

    return field->signal_update_from_isr(g_update_display_signal);
}

} // namespace

} // namespace lumen::activity::field

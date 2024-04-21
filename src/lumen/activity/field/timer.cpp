#include "lumen/activity/field/timer.hpp"

#include "esp_log.h"

namespace lumen::activity::field {
namespace {

constexpr auto tag = "activity/field/timer";

/// Update the value of the timer field and signal an update
bool timer_alarm_callback(
    gptimer_handle_t timer,
    gptimer_alarm_event_data_t const* timer_data,
    void* context
);

gptimer_event_callbacks_t const callbacks = {.on_alarm = timer_alarm_callback};

gptimer_alarm_config_t const alarm_config = {
    .alarm_count = 1'000'000, // period = 1s
    .reload_count = 0,
    .flags = {.auto_reload_on_alarm = 1}
};

} // namespace

Timer::Timer(uint64_t start_time, bool count_up /* = false */)
    : Field{start_time}, start_time_{start_time}, is_count_up_{count_up}
{
    auto err = gptimer_new_timer(&config_, &timer_);

    if (err != ESP_OK) {
        ESP_LOGE(tag, "Unable to initialize new timer");
    }

    gptimer_register_event_callbacks(timer_, &callbacks, this);

    gptimer_set_alarm_action(timer_, &alarm_config);

    gptimer_enable(timer_);
}

Timer::~Timer()
{
    stop();
    gptimer_disable(timer_);
    gptimer_del_timer(timer_);
}

uint64_t Timer::get_start_time() const
{
    return start_time_;
}

bool Timer::is_running() const
{
    return is_running_;
}

bool Timer::is_count_up() const
{
    return is_count_up_;
}

std::string Timer::to_string() const
{
    auto time = get_value();

    auto minutes = time / 60;
    auto seconds = std::to_string(time - minutes * 60);

    // Display single digit numbers with a leading 0
    if (seconds.size() == 1) {
        seconds = "0" + seconds;
    }

    return {std::to_string(minutes) + ":" + seconds};
}

void Timer::start()
{
    // If this is a count down timer, don't start it if the value is already 0
    if (!is_count_up_ && get_value() == 0) {
        return;
    }

    if (!is_running_) {
        gptimer_start(timer_);
        is_running_ = true;
    }
}

void Timer::stop()
{
    if (is_running_) {
        gptimer_stop(timer_);
        is_running_ = false;
    }
}

void Timer::toggle()
{
    if (is_running_) {
        stop();
    } else {
        start();
    }
}

void Timer::reset()
{
    stop();
    set_value(start_time_);
}

void Timer::set_value(uint64_t const& time)
{
    if (time == 0) {
        stop();
    }

    Field::set_value(time);
}

bool Timer::set_value_from_isr(uint64_t const& time)
{
    if (time == 0) {
        stop();
    }

    return Field::set_value_from_isr(time);
}

namespace {

bool timer_alarm_callback(
    gptimer_handle_t /* timer */,
    gptimer_alarm_event_data_t const* /* timer_data */,
    void* context
)
{
    auto* timer_field = static_cast<Timer*>(context);

    auto value = timer_field->get_value();

    if (timer_field->is_count_up()) {
        value++;
    } else {
        if (value > 0) {
            value--;
        }
    }

    return timer_field->set_value_from_isr(value);
}

} // namespace

} // namespace lumen::activity::field

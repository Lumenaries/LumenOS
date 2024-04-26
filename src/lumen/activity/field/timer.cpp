#include "lumen/activity/field/timer.hpp"

#include "esp_log.h"

namespace lumen::activity::field {
namespace {

constexpr auto tag = "activity/field/timer";

/** Update the value of the timer field and signal an update.
 *
 * \param timer The handle to the timer object that caused the alarm.
 *
 * \param timer_data The data associated with the alarm event.
 *
 * \param context Context passed in by the user at registration-time.
 */
bool timer_alarm_callback(
    gptimer_handle_t timer,
    gptimer_alarm_event_data_t const* timer_data,
    void* context
);

} // namespace

Timer::Timer(uint64_t start_time, bool count_up /* = false */)
    : Field{start_time}, start_time_{start_time}, is_count_up_{count_up},
      hardware_timer_{1'000'000, timer_alarm_callback, this}
{
}

uint64_t Timer::get_start_time() const
{
    return start_time_;
}

bool Timer::is_running() const
{
    return hardware_timer_.is_running();
}

bool Timer::is_count_up() const
{
    return is_count_up_;
}

void Timer::set_value(uint64_t const& time)
{
    if (time == 0) {
        hardware_timer_.stop();
    }

    Field::set_value(time);
}

bool Timer::set_value_from_isr(uint64_t const& time)
{
    if (time == 0) {
        hardware_timer_.stop();
    }

    return Field::set_value_from_isr(time);
}

void Timer::set_start_time(uint64_t start_time)
{
    start_time_ = start_time;
}

void Timer::set_count_up(bool is_count_up)
{
    is_count_up_ = is_count_up;
}

std::string Timer::to_string() const
{
    auto time = get_value();

    auto minutes = std::to_string(time / 60);
    auto seconds = std::to_string(time % 60);

    // Display single digit numbers with a leading 0
    if (seconds.size() == 1) {
        seconds = "0" + seconds;
    }

    if (minutes.size() == 1) {
        minutes = "0" + minutes;
    }

    return minutes + ":" + seconds;
}

void Timer::start()
{
    // If this is a count down timer, don't start it if the value is already 0
    if (!is_count_up_ && get_value() == 0) {
        return;
    }

    hardware_timer_.start();
}

void Timer::stop()
{
    hardware_timer_.stop();

    // Let the website know that the timer has paused
    signal_update(g_update_event_stream);
}

void Timer::toggle()
{
    hardware_timer_.toggle();
}

void Timer::reset()
{
    hardware_timer_.stop();
    set_value(start_time_);
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

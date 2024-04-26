#include "lumen/hardware/timer.hpp"

namespace lumen::hardware {

Timer::Timer(
    uint64_t alarm_frequency,
    gptimer_alarm_cb_t callback,
    void* callback_context
)
    : alarm_config_{.alarm_count = alarm_frequency, .reload_count = 0, .flags = {.auto_reload_on_alarm = 1}},
      callbacks_{.on_alarm = callback}
{
    gptimer_new_timer(&config_, &timer_);

    gptimer_register_event_callbacks(timer_, &callbacks_, callback_context);

    gptimer_set_alarm_action(timer_, &alarm_config_);

    gptimer_enable(timer_);
}

Timer::~Timer()
{
    stop();
    gptimer_disable(timer_);
    gptimer_del_timer(timer_);
}

void Timer::start()
{
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

bool Timer::is_running() const
{
    return is_running_;
}

} // namespace lumen::hardware

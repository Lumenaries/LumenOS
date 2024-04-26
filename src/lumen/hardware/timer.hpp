#pragma once

#include "driver/gptimer.h"

namespace lumen::hardware {

class Timer {
public:
    /** Create an instance of a hardware timer.
     *
     * \param alarm_frequency How often the alarm should fire in HZ. e.g.
     * 1'000'000 = 1 second
     *
     * \param callback Callback that should run for each alarm.
     *
     * \param callback_context Context to be passed into the callback.
     */
    Timer(
        uint64_t alarm_frequency,
        gptimer_alarm_cb_t callback,
        void* callback_context
    );

    ~Timer();

    [[nodiscard]] bool is_running() const;

    void start();
    void stop();
    void toggle();

private:
    gptimer_handle_t timer_{};
    gptimer_config_t config_ = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1'000'000 // 1 tick = 1us
    };

    gptimer_alarm_config_t alarm_config_{};
    gptimer_event_callbacks_t callbacks_{};

    bool is_running_{};
};

} // namespace lumen::hardware

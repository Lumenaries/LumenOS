#pragma once

#include "lumen/activity/field/field.hpp"

#include "driver/gptimer.h"

#include <string>

namespace lumen::activity::field {

/** A field which represents a timer.
 *
 * A timer can either be count up or count down, which can be configured at
 * construction. Count down timers will not start if their current value is set
 * to 0 seconds.
 *
 * The value of the timer represents the number of seconds that have elapsed in
 * the case of a count up timer, or the number of seconds left until 0 in the
 * case of a count down timer.
 *
 * \note Timer fields will update the display once every second while they're
 * running.
 */
class Timer : public Field<uint64_t> {
public:
    /** Timer constructor.
     *
     * \param start_time The number of seconds from which the timer should begin
     * counting.
     *
     * \param count_up Whether or not the timer will count up or count down.
     */
    explicit Timer(uint64_t start_time, bool count_up = false);
    ~Timer() override;

    [[nodiscard]] uint64_t get_start_time() const;
    [[nodiscard]] bool is_running() const;
    [[nodiscard]] bool is_count_up() const;

    /** Set the number of seconds in the timer.
     *
     * Set the number of seconds that have elapsed since starting in the case of
     * a count up timer, or the number of seconds left until 0 in the case of a
     * count down timer. Will also trigger a display update.
     *
     * \param time The new value of the timer. If `time` is 0, then the timer
     * will be stopped automatically.
     */
    void set_value(uint64_t const& time) override;

    /** Set the number of seconds in the timer.
     *
     * Set the number of seconds that have elapsed since starting in the case of
     * a count up timer, or the number of seconds left until 0 in the case of a
     * count down timer. Will also trigger a display update.
     *
     * \note This function is only meant to be used inside of an ISR.
     *
     * \param time The new value of the timer. If `time` is 0, then the timer
     * will be stopped automatically.
     *
     * \return Whether or not a higher priority task was awakened as a result of
     * setting the valule.
     */
    bool set_value_from_isr(uint64_t const& time) override;

    /** Set the start time of the timer.
     *
     * \param start_time The number of seconds from which the timer should begin
     * counting.
     */
    void set_start_time(uint64_t start_time);

    /** Set whether the timer is count up or count down.
     *
     * \param count_up Whether or not the timer will count up or count down.
     */
    void set_count_up(bool is_count_up);

    /// Convert the contents of the timer to a string.
    [[nodiscard]] std::string to_string() const override;

    /// Start the timer if it is not running already.
    void start();

    /// Stop the timer if it is running.
    void stop();

    /// Either start or stop the timer depending on the current state.
    void toggle();

    /// Stop the timer and reset its value to `start_time` given in constructor.
    void reset();

private:
    gptimer_handle_t timer_{};
    gptimer_config_t config_ = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1'000'000 // 1 tick = 1us
    };

    uint64_t start_time_{};
    bool is_running_{};
    bool is_count_up_{};
};

} // namespace lumen::activity::field

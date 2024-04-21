#pragma once

#include "lumen/app_task.hpp"

#include <string>

namespace lumen::activity::field {

/// Base class from which displayable types derive.
template <typename T>
class Field {
public:
    /** Field constructor.
     *
     * \param value Initial value of the field.
     */
    explicit Field(T const& value = T{}) : value_{value} {}
    virtual ~Field() = default;

    [[nodiscard]] T get_value() const
    {
        return value_;
    }

    /** Set the value of the field and trigger a display update.
     *
     * \param value New value of the field.
     */
    virtual void set_value(T const& value)
    {
        if (value_ != value) {
            value_ = value;
            signal_update();
        }
    }

    /** Set the value of the field and trigger a display update.
     *
     * \note This function is only meant to be used inside of an ISR.
     *
     * \param value New value of the field.
     */
    virtual bool set_value_from_isr(T const& value)
    {
        if (value_ != value) {
            value_ = value;
            return signal_update_from_isr();
        }

        return false;
    }

    /// Convert the contents of the field to a string.
    [[nodiscard]] virtual std::string to_string() const = 0;

    /// Signal the App Task to refresh the display.
    void signal_update()
    {
        xTaskNotify(get_app_task_handle(), g_update_display_signal, eSetBits);
    }

    /// Signal the App Task to refresh the display.
    bool signal_update_from_isr()
    {
        auto higher_priority_task_awoken = pdFALSE;

        xTaskNotifyFromISR(
            get_app_task_handle(),
            g_update_display_signal,
            eSetBits,
            &higher_priority_task_awoken
        );

        return higher_priority_task_awoken == pdTRUE;
    }

private:
    T value_{};
};

} // namespace lumen::activity::field

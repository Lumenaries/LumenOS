#pragma once

#include "lumen/activity/field/field.hpp"

#include <string>

namespace lumen::activity::field {

/// A field which represents a string type.
class Text : public Field<std::string> {
public:
    /** Text constructor.
     *
     * \param parent Pointer to the activity object that should be updated when
     * a state change occurs.
     *
     * \param value Initial value that the field should hold.
     */
    explicit Text(std::string const& value);

    /// Returns whether this field will scroll across the screen when displayed.
    [[nodiscard]] bool is_scrollable() const;

    /** Set whether is displayed as scrollable text.
     *
     * \param scrollable `true` if the text should scroll, `false` otherwise.
     */
    void set_scrollable(bool scrollable);

    /// Convert the contents of the field to a string.
    [[nodiscard]] std::string to_string() const override;

private:
    bool scrollable_{};
};

} // namespace lumen::activity::field

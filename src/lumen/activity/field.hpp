#pragma once

#include "lumen/activity/activity.hpp"

#include <string>

namespace lumen::activity {

class Activity;

template <typename T>
class Field {
public:
    // Field() = default;
    //  explicit Field(T value) : value_{value} {}
    Field(Activity* parent, T value) : parent_{parent}, value_{value} {}
    virtual ~Field() = default;

    // T get_value()
    [[nodiscard]] T get_value() const
    {
        return value_;
    }

    // void set_value(T value)
    void set_value(T value)
    {
        value_ = value;
        signal_update();
    }

    virtual std::string to_string() = 0;

protected:
    void signal_update();

private:
    Activity* parent_;
    // T value_;
    T value_;
};

class NumberField : public Field<uint> {
public:
    NumberField(Activity* parent, uint increment = 1);

    NumberField& increase();

    NumberField& decrease();

    std::string to_string() override;

private:
    uint increment_{};
};

class TextField : public Field<std::string> {
public:
    TextField(Activity* parent, std::string const& value);

    bool is_scrollable();
    void set_scrollable(bool scrollable);

    std::string to_string() override;

private:
    bool scrollable_{};
};

} // namespace lumen::activity

#include "lumen/app_task.hpp"

#include "lumen/activity/display.hpp"
#include "lumen/activity/snapshot.hpp"
#include "lumen/web/server.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "led_strip.h"

#include <memory>
#include <optional>

namespace lumen {
namespace {

QueueHandle_t message_queue = nullptr;

constexpr auto r1_pin = 32;
constexpr auto g1_pin = 14;
constexpr auto b1_pin = 15;
constexpr auto r2_pin = 27;
constexpr auto g2_pin = 33;
constexpr auto b2_pin = 12;
constexpr auto a_pin = 21;
constexpr auto b_pin = 19;
constexpr auto c_pin = 5;
constexpr auto lat_pin = 7;
constexpr auto oe_pin = 8;
constexpr auto clk_pin = 13;
constexpr auto d_pin = 4;
constexpr auto e_pin = -1;

constexpr auto panel_res_x = 32;
constexpr auto panel_res_y = 16;

constexpr auto num_rows = 4;
constexpr auto num_cols = 3;

constexpr auto led_pin = 48;

led_strip_handle_t configure_led();
void blink_led(led_strip_handle_t led, std::optional<bool> on = {});

} // namespace

void app_task(void* /* parameters */)
{
    message_queue = xQueueCreate(5, sizeof(activity::Message));

    auto message_buffer = activity::Message{};

    HUB75_I2S_CFG::i2s_pins pins = {
        r1_pin,
        g1_pin,
        b1_pin,
        r2_pin,
        g2_pin,
        b2_pin,
        a_pin,
        b_pin,
        c_pin,
        d_pin,
        e_pin,
        lat_pin,
        oe_pin,
        clk_pin
    };

    // auto display = std::make_unique<activity::Display>(
    //     num_rows, num_cols, panel_res_x, panel_res_y, pins
    //);

    // display->begin();
    // display->setBrightness(20);
    // display->clearScreen();

    auto web_server = web::Server{};
    auto led = configure_led();

    // auto activity = activity::Snapshot(display.get());

    while (true) {
        xQueueReceive(message_queue, &message_buffer, portMAX_DELAY);

        switch (message_buffer.command) {
        case activity::MessageCommand::increase_score:
            // activity.increase_score(message_buffer.team);
            blink_led(led);
            break;
        case activity::MessageCommand::decrease_score:
            // activity.decrease_score(message_buffer.team);
            blink_led(led, false);
            break;
        case activity::MessageCommand::reset:
            // activity.reset();
            blink_led(led, false);
            break;
        }
    }
}

void send_message_to_app(activity::Message const& message)
{
    // We don't want to lose messages, so wait for as long as necessary
    xQueueSendToBack(message_queue, &message, portMAX_DELAY);
}

namespace {

led_strip_handle_t configure_led()
{
    led_strip_handle_t led = nullptr;

    led_strip_config_t strip_config = {
        .strip_gpio_num = led_pin, .max_leds = 1
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags = {.with_dma = false}
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led));

    led_strip_clear(led);
    return led;
}

void blink_led(led_strip_handle_t led, std::optional<bool> on /* = {} */)
{
    static bool s_on = false;

    if (on) {
        s_on = on.value();
    }

    if (s_on) {
        led_strip_set_pixel(led, 0, 16, 16, 16);
        led_strip_refresh(led);
    } else {
        led_strip_clear(led);
    }

    s_on = !s_on;
}

} // namespace

} // namespace lumen

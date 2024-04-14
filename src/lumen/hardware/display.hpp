#pragma once

#include "Adafruit_GFX.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include <memory>

namespace lumen::hardware {

class Display : public Adafruit_GFX {
public:
    Display();

    MatrixPanel_I2S_DMA* getDisplay();

    /** Set the brightness of the display.
     *
     * \param brightness The brightness value out of. A value of 0 = 0%, and
     * 255 = 100%.
     */
    void setBrightness(uint8_t brightness);

    /** Draw a pixel to a given coordinate.
     *
     * \param x X-coordinate of pixel to light.
     * \param y Y-coordinate of pixel to light.
     * \param color "Packed" color value of pixel. Use color565() to convert
     * typical RGB values into 5:6:5 "packed" format.
     */
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;

    /** Draw a pixel to a given coordinate.
     *
     * \param x X-coordinate of pixel to light.
     * \param y Y-coordinate of pixel to light.
     * \param r Red color value of LED.
     * \param g Green color value of LED.
     * \param b Blue color value of LED.
     */
    void drawPixelRGB888(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b);

    /** Color every pixel the same color.
     *
     * \param color Color value of the screen. Use color444(), color565(), or
     *              color333() to convert a typical RGB value.
     */
    void fillScreen(uint16_t color) override;

    /// Turn off every pixel.
    void clearScreen();

    /** Convert RGB values into 5:6:5 "packed" 16 bit color format.
     *
     * \param red Red color value of LED.
     * \param green Green color value of LED.
     * \param blue Blue color value of LED.
     */
    static constexpr uint16_t color565(uint8_t red, uint8_t green, uint8_t blue)
    {
        return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
    }

    /// Swap the display buffer when double buffering is enabled.
    void flipDMABuffer();

private:
    struct Coordinate {
        int16_t x;
        int16_t y;
    };

    std::unique_ptr<MatrixPanel_I2S_DMA> display_{};

    // Number of rows in the chain.
    int numRows_{CONFIG_HARDWARE_DISPLAY_PANEL_ROWS};

    // Number of columns in the chain.
    int numCols_{CONFIG_HARDWARE_DISPLAY_PANEL_COLUMNS};

    // Number of pixels in the X direction of each panel.
    int panelResX_{CONFIG_HARDWARE_DISPLAY_PANEL_RES_X};

    // Number of pixels in the Y direction of each panel.
    int panelResY_{CONFIG_HARDWARE_DISPLAY_PANEL_RES_Y};

    // The number pixels on the X axis in the entire display.
    int displayResX_{
        CONFIG_HARDWARE_DISPLAY_PANEL_RES_X *
        CONFIG_HARDWARE_DISPLAY_PANEL_COLUMNS
    };

    // The number pixels on the Y axis in the entire display.
    int displayResY_{
        CONFIG_HARDWARE_DISPLAY_PANEL_RES_X *
        CONFIG_HARDWARE_DISPLAY_PANEL_COLUMNS
    };

    // The width of the chain in pixels (as the DMA engine sees it).
    int dmaResX_{
        CONFIG_HARDWARE_DISPLAY_PANEL_RES_X *
        CONFIG_HARDWARE_DISPLAY_PANEL_COLUMNS *
        CONFIG_HARDWARE_DISPLAY_PANEL_ROWS
    };

    /** Remap the desired coordinates so they display correctly.
     *
     * \param x Virtual X-coordinate in the range [0, displayResX_].
     * \param x Virtual Y-coordinate in the range [0, displayResY_].
     */
    Coordinate mapCoord(int16_t x, int16_t y);
};

} // namespace lumen::hardware

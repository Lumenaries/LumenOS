#pragma once

#include "Adafruit_GFX.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include <memory>

namespace lumen::hardware {

class Display : public Adafruit_GFX {
public:
    Display(
        int numRows,
        int numCols,
        int panelResX,
        int panelResY,
        HUB75_I2S_CFG::i2s_pins& pins
    );

    bool begin();

    // 0 - 0%, 255 - 100%
    void setBrightness(uint8_t brightness);

    void drawPixel(int16_t x, int16_t y, uint16_t color) override;

    void drawPixelRGB888(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b);

    void fillScreen(uint16_t color) override;

    void clearScreen();

    uint16_t color444(uint8_t r, uint8_t g, uint8_t b);

    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

    uint16_t color333(uint8_t r, uint8_t g, uint8_t b);

    void flipDMABuffer();

    MatrixPanel_I2S_DMA* dmaDisplay()
    {
        return dmaDisplay_.get();
    }

private:
    struct Coordinate {
        int16_t x;
        int16_t y;
    };

    // Number of rows in the chain
    int numRows_;

    // Number of columns in the chain
    int numCols_;

    // Number of pixels in the X direction of each panel
    int panelResX_;

    // Number of pixels in the Y direction of each panel
    int panelResY_;

    // The number pixels on the X axis in the entire display
    int displayResX_;

    // The number pixels on the Y axis in the entire display
    int displayResY_;

    // The width of the chain in pixels (as the DMA engine sees it)
    int dmaResX_;

    std::unique_ptr<MatrixPanel_I2S_DMA> dmaDisplay_;

    Coordinate mapCoord(int16_t x, int16_t y);
};

} // namespace lumen::hardware

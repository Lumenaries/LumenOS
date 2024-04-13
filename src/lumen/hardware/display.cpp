#include "lumen/hardware/display.hpp"

namespace lumen::hardware {
namespace {

constexpr int yRemap[] = {0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 4, 5, 6, 7};

} // namespace

Display::Display()
    : Adafruit_GFX(
          CONFIG_HARDWARE_DISPLAY_PANEL_RES_X *
              CONFIG_HARDWARE_DISPLAY_PANEL_COLUMNS,
          CONFIG_HARDWARE_DISPLAY_PANEL_RES_Y *
              CONFIG_HARDWARE_DISPLAY_PANEL_ROWS
      )
{
    auto config = HUB75_I2S_CFG(
        panelResX_ * 2,
        panelResY_ / 2,
        numRows_ * numCols_,
        HUB75_I2S_CFG::i2s_pins{
            CONFIG_HARDWARE_DISPLAY_R1_PIN,
            CONFIG_HARDWARE_DISPLAY_G1_PIN,
            CONFIG_HARDWARE_DISPLAY_B1_PIN,
            CONFIG_HARDWARE_DISPLAY_R2_PIN,
            CONFIG_HARDWARE_DISPLAY_G2_PIN,
            CONFIG_HARDWARE_DISPLAY_B2_PIN,
            CONFIG_HARDWARE_DISPLAY_A_PIN,
            CONFIG_HARDWARE_DISPLAY_B_PIN,
            CONFIG_HARDWARE_DISPLAY_C_PIN,
            CONFIG_HARDWARE_DISPLAY_D_PIN,
            CONFIG_HARDWARE_DISPLAY_E_PIN,
            CONFIG_HARDWARE_DISPLAY_LAT_PIN,
            CONFIG_HARDWARE_DISPLAY_OE_PIN,
            CONFIG_HARDWARE_DISPLAY_CLK_PIN,
        }
    );

    display_ = std::make_unique<MatrixPanel_I2S_DMA>(config);

    begin();
    clearScreen();
    // TODO: We may need to adjust the default brightness at some point
    setBrightness(20);
}

void Display::setBrightness(uint8_t brightness)
{
    display_->setBrightness(brightness);
}

void Display::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    auto mapped = mapCoord(x, y);
    display_->drawPixel(mapped.x, mapped.y, color);
}

void Display::drawPixelRGB888(
    int16_t x,
    int16_t y,
    uint8_t r,
    uint8_t g,
    uint8_t b
)
{
    auto mapped = mapCoord(x, y);
    display_->drawPixelRGB888(mapped.x, mapped.y, r, g, b);
}

void Display::fillScreen(uint16_t color)
{
    display_->fillScreen(color);
}

void Display::clearScreen()
{
    fillScreen(0);
}

void Display::flipDMABuffer()
{
    display_->flipDMABuffer();
}

MatrixPanel_I2S_DMA* Display::getDisplay()
{
    return display_.get();
}

Display::Coordinate Display::mapCoord(int16_t x, int16_t y)
{
    // Check if requested coordinate is outside the display bounds
    if (x < 0 || x >= displayResX_ || y < 0 || y == displayResY_) {
        return {-1, -1};
    }

    Coordinate coord{x, y};

    // First, remap the requested grid coordinate to a chain coordinate

    // Current row indexed at 0
    int row = (coord.y / panelResY_);

    if ((row % 2) == 0) {
        coord.x = ((numRows_ - (row + 1)) * displayResX_) + coord.x;
        coord.y = (coord.y % panelResY_);
    } else {
        // Odd row, panel is upside down.

        // X coordinate is reversed for this row
        coord.x = dmaResX_ - coord.x - (row * displayResX_) - 1;

        // Y coordinate is inverted for this row
        coord.y = panelResY_ - 1 - (coord.y % panelResY_);
    }

    // Next, remap the chain coordinate to a panel-specific coordinate

    if ((coord.y & 4) != 0) {
        // even row
        coord.x = (coord.x % 8) | (8 + ((coord.x >> 3) << 4));
    } else {
        // odd row
        coord.x = (coord.x ^ 7) + 8 * (coord.x >> 3);
    }

    coord.y = yRemap[coord.y];

    return coord;
}

bool Display::begin()
{
    return display_->begin();
}


} // namespace lumen::hardware

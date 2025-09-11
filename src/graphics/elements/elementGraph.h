#pragma once
#include "../pageElement.h"

namespace graphics
{
    class elementGraph : public pageElement
    {

    public:
        uint16_t axesColor;
        uint8_t axesWidth = 3;

        uint16_t graphLineColor;
        uint8_t graphLineWidth = 5;

        uint16_t graphFillColor;
        bool graphFill = false;

        uint16_t graphBackgroundColor = 0x0000;

        uint8_t *data = NULL;
        uint8_t pointCount = 0;

        elementGraph(uint16_t p_pos_x_px, uint16_t p_pos_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px, uint16_t p_color)
            : pageElement(p_pos_x_px, p_pos_y_px, p_size_x_px, p_size_y_px), axesColor(p_color), graphLineColor(p_color), graphFillColor(p_color) {};
        bool draw(Adafruit_SPITFT *screen) override;

    private:
        uint16_t data_pos_x;
        uint16_t data_pos_y;
        uint16_t data_size_x;
        uint16_t data_size_y;

        bool graphWriteFrame(Adafruit_SPITFT *screen);
        bool graphWriteData(Adafruit_SPITFT *screen);
        bool graphWriteDataSectionCollumn(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                          Adafruit_SPITFT *screen);
    };
}

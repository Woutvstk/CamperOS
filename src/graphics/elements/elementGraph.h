#pragma once
#include "../pageElement.h"

namespace graphics
{
    class elementGraph : public pageElement
    {

    public:
        uint16_t axesColor;
        uint8_t axesWidth = 3;
        bool frameAllSides = false;

        int16_t axesLabelMaxX = 0;
        int16_t axesLabelMinX = 0;
        int16_t axesLabelMaxY = 0;
        int16_t axesLabelMinY = 0;
        uint16_t axesLabelColor;
        uint8_t axesLabelSize = 1;

        uint16_t graphLineColor;
        uint8_t graphLineWidth = 5;

        uint16_t graphFillColor;
        bool graphFill = false;

        uint16_t graphBackgroundColor = 0x0000;

        uint8_t *data = NULL;
        uint8_t pointCount = 0;

        elementGraph(uint16_t p_pos_x_px, uint16_t p_pos_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px, uint16_t p_color)
            : pageElement(p_pos_x_px, p_pos_y_px, p_size_x_px, p_size_y_px), axesColor(p_color), graphLineColor(p_color), graphFillColor(p_color), axesLabelColor(p_color) {};
        bool draw(GFXcanvas16 *screen) override;
        touchInputEvent getTouchInputEvent(uint16_t touchPos_x, uint16_t touchPos_y, uint8_t touch_z);

    private:
        // internal drawing window
        uint16_t int_pos_x_px;
        uint16_t int_pos_y_px;
        uint16_t int_size_x_px;
        uint16_t int_size_y_px;

        bool graphWriteFrame(GFXcanvas16 *screen);
        bool graphWriteData(GFXcanvas16 *screen);
        bool graphWriteDataSectionCollumn(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                          GFXcanvas16 *screen);
    };
}

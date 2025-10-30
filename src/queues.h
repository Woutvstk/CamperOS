#pragma once
#include "Arduino.h"
#include "globals.h"
#include "graphics/Page.h"

// forward declare hardware::touchScreen to avoid including hardware header here
namespace hardware
{
    class touchScreen;
}

/*
Task handles
*/
extern TaskHandle_t xtaskUiControllerHandle;
extern TaskHandle_t xtaskUiDrawerHandle;

/*
Queue's between tasks
*/

/*
 QrotaryISR2taskUIController
*/
#define QrotaryISR2taskUIControllerLength 8
#define QrotaryISR2taskUIControllerType bool
extern QueueHandle_t QrotaryISR2taskUIController;

/*
QtaskUIController2taskDrawer
*/
struct SdrawerInstruction
{
    graphics::Page *page;
    hardware::touchScreen *touchScreen;

    SdrawerInstruction(graphics::Page *page, hardware::touchScreen *touchScreen)
        : page(page), touchScreen(touchScreen) {}

    SdrawerInstruction() : page(NULL), touchScreen(NULL) {}
};

#define QtaskUIController2taskDrawerLength 1
#define QtaskUIController2taskDrawerType SdrawerInstruction
extern QueueHandle_t QtaskUIController2taskDrawer;

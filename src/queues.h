#pragma once
#include "Arduino.h"
#include "globals.h"
#include "graphics/Page.h"

// Task handles
extern TaskHandle_t xtaskUiControllerHandle;
extern TaskHandle_t xtaskUiDrawerHandle;

// Queue's between tasks

// QrotaryISR2taskUIController
#define QrotaryISR2taskUIControllerLength 8
#define QrotaryISR2taskUIControllerType bool
extern QueueHandle_t QrotaryISR2taskUIController;

// QtaskUIController2taskDrawer
struct SdrawerInstruction
{
    graphics::basePage *page;
    Adafruit_SPITFT *screen;
    uint8_t *dataStart;

    SdrawerInstruction(graphics::basePage *page, Adafruit_SPITFT *screen, uint8_t *dataStart)
        : page(page), screen(screen), dataStart(dataStart) {}

    SdrawerInstruction() : page(NULL), screen(NULL), dataStart(NULL) {}
};

#define QtaskUIController2taskDrawerLength 1
#define QtaskUIController2taskDrawerType SdrawerInstruction
extern QueueHandle_t QtaskUIController2taskDrawer;
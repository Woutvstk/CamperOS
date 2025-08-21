#pragma once
#include "Arduino.h"
// Structs/Queue's between tasks

// QrotaryISR2taskUIController
#define QrotaryISR2taskUIControllerLength 8
#define QrotaryISR2taskUIControllerType bool
extern QueueHandle_t QrotaryISR2taskUIController;

// QtaskUIController2taskDrawer
struct SdrawerInstruction
{
    uint8_t page = 0;
    void *displaydata;
};

#define QtaskUIController2taskDrawerLength 4
#define QtaskUIController2taskDrawerType SdrawerInstruction
extern QueueHandle_t QtaskUIController2taskDrawer;
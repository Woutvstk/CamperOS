#include <stdio.h>
#include <Arduino.h>
#include "globals.h"
#include "queues.h"
#include "config.h"
#include "hardware/touchScreenList.h"
#include "graphics.h" // pages, pageElements, ...

// TaskUiController
// Gathers information and adds it to an array for the taskUiDrawer task
// handles user input (rotary, touchscreen, ...)
void taskUiController(void *parameter);

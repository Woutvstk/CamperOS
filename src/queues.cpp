#include "queues.h"

// QrotaryISR2taskUIController
QueueHandle_t QrotaryISR2taskUIController = xQueueCreate(QrotaryISR2taskUIControllerLength, sizeof(QrotaryISR2taskUIControllerType));

// QtaskUIController2taskDrawer
QueueHandle_t QtaskUIController2taskDrawer = xQueueCreate(QtaskUIController2taskDrawerLength, sizeof(QtaskUIController2taskDrawerType));

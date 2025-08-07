// defines for general use

// diplay 0 settings
#define UiUpdateRate        120 // screen updates per minute
#define display0Rotation    3
#define screen0Type         ILI9341
#define touch0              0

// Structs/Queue's between tasks

// QrotaryISR2taskUIController
#define QrotaryISR2taskUIControllerLength 8
#define QrotaryISR2taskUIControllerType bool
static QueueHandle_t QrotaryISR2taskUIController = xQueueCreate(QrotaryISR2taskUIControllerLength, sizeof(QrotaryISR2taskUIControllerType));

// QtaskUIController2taskDrawer
struct SdrawerInstruction
{
    uint8_t page = 0;
    void *displaydata;
};

#define QtaskUIController2taskDrawerLength 4
#define QtaskUIController2taskDrawerType SdrawerInstruction
static QueueHandle_t QtaskUIController2taskDrawer = xQueueCreate(QtaskUIController2taskDrawerLength, sizeof(QtaskUIController2taskDrawerType));
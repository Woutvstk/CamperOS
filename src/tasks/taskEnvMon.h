#include <Wire.h>
#include "Adafruit_BME680.h"
#include "queues.h"

#define SEALEVELPRESSURE_HPA (1013.25)

struct BME680
{
    float temp;
    uint32_t press;
    float hum;
    uint32_t gas;
    float alt;
};

struct BME680Settings
{
    QueueHandle_t &dataQueue;
    uint32_t sampleInterval;
    uint32_t dataInterval;
};

void taskEnvMon(void *parameter);
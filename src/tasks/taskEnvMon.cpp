#include "taskEnvMon.h"

void taskEnvMon(void *parameter)
{
    Wire.begin();
    Adafruit_BME680 bme(&Wire);
    if (!bme.begin())
    {
        Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    }
    BME680 tmp;

    while (true)
    {
        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));
        unsigned long endTime = bme.beginReading();
        vTaskDelay(endTime - millis());
        bme.endReading();
        tmp.temp = bme.temperature;
        tmp.press = (bme.pressure / 100.0);
        tmp.hum = bme.humidity;
        tmp.gas = (bme.gas_resistance / 1000.0);
        tmp.alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
    }
}
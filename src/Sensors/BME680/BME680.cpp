#include "BME680.h"

BME680::BME680()
{
    this->temperature.name = "Temperature";
    this->temperature.units = "C";
    this->temperature.packet_constant = TEMPERATURE_PACKET_CONSTANT;
    this->species.push_back(&this->temperature);

    this->pressure.name = "Pressure";
    this->pressure.units = "mbar";
    this->pressure.packet_constant = PRESSURE_PACKET_CONSTANT;
    this->species.push_back(&this->pressure);

    this->humidity.name = "Humidity";
    this->humidity.units = "%";
    this->humidity.packet_constant = HUMIDITY_PACKET_CONSTANT;
    this->species.push_back(&this->humidity);

    this->voc.name = "VOC";
    this->voc.units = "";
    this->voc.packet_constant = DONT_ADVERTISE_CONSTANT;
    this->species.push_back(&this->voc);
}

BME680::~BME680() {}

bool BME680::start()
{
    bool adafruit_init_success = false;

    if (!(adafruit_init_success = this->_bme680.begin())) {
        Serial.println("Could not start BME680!");
    } else {
        Serial.println("Initialized BME Sensor!");
    }
    this->_bme680.setTemperatureOversampling(BME680_OS_8X);
    this->_bme680.setHumidityOversampling(BME680_OS_2X);
    this->_bme680.setPressureOversampling(BME680_OS_4X);
    this->_bme680.setIIRFilterSize(BME680_FILTER_SIZE_3);
    this->_bme680.setGasHeater(320, 150); // 320*C for 150 ms

    return adafruit_init_success;
}

bool BME680::measure()
{
    if (!this->_bme680.performReading()) {
        Serial.println("Failed to read BME680");
        return false;
    }

    this->temperature.raw_value = this->_bme680.temperature;
    this->temperature.adj_value = (this->temperature.slope * this->temperature.raw_value) + this->temperature.zero;

    this->pressure.raw_value = this->_bme680.pressure;
    this->pressure.adj_value = (this->pressure.slope * (this->pressure.raw_value / 100)) + this->pressure.zero;

    this->humidity.raw_value = this->_bme680.humidity;
    this->humidity.adj_value = (this->humidity.slope * this->humidity.raw_value) + this->humidity.zero;

    this->voc.raw_value = this->_bme680.gas_resistance;
    this->voc.adj_value = (this->voc.slope * this->voc.raw_value) * this->voc.zero;

    return true;
}
#include "AQSync.h"

AQSync::AQSync(USARTSerial &_serial)
{
    this->name = "AQSync";

    this->serial = &_serial;

    this->serial->begin(9600);
    this->serial->setTimeout(5000);
}

AQSync::~AQSync() {}

bool AQSync::verifyPacket(char *packet)
{
    // size_t receive_sum = 0;

    // for (uint8_t i = 0; i < AQSYNC_SERIAL_PACKET_LENGTH - 2; i++) {
    //     receive_sum += packet[i];
    // }
    // receive_sum += 0x42;

    // uint16_t checksum = (packet[AQSYNC_SERIAL_PACKET_LENGTH-2] << 8) + packet[AQSYNC_SERIAL_PACKET_LENGTH - 1];
    // return receive_sum == checksum;
    String receivedData = packet;

}

void AQSync::loop()
{
    PAMSensor::loop();
    memset(this->buff, 0, AQSYNC_SERIAL_PACKET_LENGTH);

    if (this->serial->available())
    {
        char incomingByte = this->serial->read()
        if (incomingByte == 'm')
        {
            
        }
        else
        {

        }
    }

    if (this->serial->find("B")) {
        this->serial->readBytes(this->buff, AQSYNC_SERIAL_PACKET_LENGTH);
        if(this->buff[0] == 0x4d){
            if(this->verifyPacket(this->buff)){ //All units are ug/m^3
                this->pm1.raw_value = (this->buff[3] << 8) + this->buff[4];
                this->pm1.adj_value = (this->pm1.slope * this->pm1.raw_value) + this->pm1.zero;

                float pm2_5_correction_factor = 1;
                std::vector<PAMSpecie *> *humidity_species = PAMSensorManager::GetInstance()->findSpeciesForName("humidity");
                if (humidity_species->size() >= 1) {
                    float humidity = humidity_species->at(0)->adj_value / 100;
                    pm2_5_correction_factor = PM_25_CONSTANT_A + (PM_25_CONSTANT_B * humidity) / (1 - humidity);
                }
                free(humidity_species);

                this->pm2_5.raw_value = (this->buff[5] << 8) + this->buff[6];
                this->pm2_5.adj_value = (this->pm2_5.slope * (this->pm2_5.raw_value / pm2_5_correction_factor)) + this->pm2_5.zero;

                this->pm10.raw_value = (this->buff[7] << 8) + this->buff[8];
                this->pm10.adj_value = (this->pm10.slope * this->pm10.raw_value) + this->pm10.zero;
            }
        }
    } else {
        while(this->serial->available()) {
            this->serial->read();
        }
    }
}
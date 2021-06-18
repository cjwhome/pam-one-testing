

#ifndef __AQSYNC_H__
#define __AQSYNC_H__

#include "Particle.h"

#include "../../PAMSensorManager/PAMSensorManager.h"
#include "../../PAMSensor/PAMSensor.h"
#include "../../PAMSpecie/PAMSpecie.h"
#include "../../PAMEEPROM/EEPROMAddresses.h"

#define AQSYNC_SERIAL_PACKET_LENGTH (4096)

class AQSync: public PAMSensor {

public:
    AQSync(USARTSerial &serial);
    ~AQSync();

    void loop();

    // PAMSpecie pm1;
    // PAMSpecie pm2_5;
    // PAMSpecie pm10;

private:
    USARTSerial *serial;
    char buff[AQSYNC_SERIAL_PACKET_LENGTH];

    bool verifyPacket(char *packet);
};

#endif
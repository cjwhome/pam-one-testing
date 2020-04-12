#ifndef __PAM_T6713_H__
#define __PAM_T6713_H__

#include "Particle.h"

#include "Telaire_T6713.h"

#include "../../PAMSensor/PAMSensor.h"
#include "../../PAMSpecie/PAMSpecie.h"

class T6713: public PAMSensor {

public:
    T6713();
    ~T6713();

    void start();
    void measure();

    PAMSpecie *CO2 = nullptr;

private:
    Telaire_T6713 t6713;

};

#endif // __PAM_T6713_H__
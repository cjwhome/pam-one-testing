#include "PAMSerial.h"
// THIS IS SO WE GET A LARGER SERIAL BUFFER
#include "SerialBufferRK.h"

PAMSerialManager& __fetch_pam_usb_serial() {
    static setup = false;
    static SerialBuffer<4096> serBuf(Serial4); // This is how we setup getting a bigger buffer for Serial4
    // This gives us a bigger buffer for Serial4 for communication with the Serial4
    if (!setup) {
        serBuf.setup();
        setup = true;
    }
    static PAMSerialManager pam_serial(serBuf);
    return pam_serial;
}
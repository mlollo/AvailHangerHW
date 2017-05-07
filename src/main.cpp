#define I2C_SLAVE_ADDRESS 0x06 // the 7-bit address (remember to change this when adapting this example)
// Get this from https://github.com/rambo/TinyWire
#include "Arduino.h"
#include "TinyWireS.h"


// The default buffer size, Can't recall the scope of defines right now
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif


void setup()
{
	TinyWireS.begin(I2C_SLAVE_ADDRESS);
}

void loop()
{
	setup();
	while (1) {
		if (TinyWireS.available()) {
			TinyWireS.send(0x06);
			//if caca = I2C_SLAVE_ADDRESS ;

		}
	}
	return;
}

#include <Arduino.h>
#include "MoppyInstruments/MoppyInstrument.h"

/**********
 * MoppyInstruments handle the sound-creation logic for your setup.  The
 * instrument class provides a systemMessage handler function and a deviceMessage
 * handler function for handling messages received by the network and a tick
 * function for precise timing events.
 *
 * Uncomment the appropriate include line for your setup, and use that 
 * instrument's constructor
 */

// Floppy drives directly connected to the Arduino's digital pins
#include "MoppyInstruments/FloppyDrives.h"

// L298N stepper motor driver
//#include "src/MoppyInstruments/L298N.h"

// A single device (e.g. xylophone, drums, etc.) connected to shift registers
//#include "src/MoppyInstruments/ShiftRegister.h"

// Decorative LED lights
//#include "MoppyInstruments/DriveLights.h"

// A Compound instrument for pairing two instruments on a single board
//#include "MoppyInstruments/CompoundInstrument.h"

//MoppyInstrument *instrument = new CompoundInstrument(new FloppyDrives(), new DriveLights());
FloppyDrives *instrument = new FloppyDrives();

/**********
 * MoppyNetwork classes receive messages sent by the Controller application,
 * parse them, and use the data to call the appropriate handler as implemented
 * in the instrument class defined above.
 *
 * Uncomment the appropriate networking class for your setup
 */

// Standard Arduino HardwareSerial implementation
#include "MoppyNetworks/MoppySerial.h"
    MoppySerial network = MoppySerial(instrument);

    //// UDP Implementation using some sort of network stack?  (Not implemented yet)
    // #include "src/MoppyNetworks/MoppyUDP.h"
    // MoppyUDP network = MoppyUDP(instrument.systemMessage, instrument.deviceMessage);


//The setup function is called once at startup of the sketch
void setup()
{
    // Call setup() on the instrument to allow to to prepare for action
    instrument->setup();

    // Tell the network to start receiving messages
    network.begin();
}

// The loop function is called in an endless loop
void loop()
{
	// Endlessly read messages on the network.  The network implementation
	// will call the system or device handlers on the intrument whenever a message is received.
    network.readMessages();
}
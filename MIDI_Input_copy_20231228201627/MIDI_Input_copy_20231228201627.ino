#include <MIDI.h>  // Add Midi Library

#define LED 7    // Arduino Board LED is on Pin 13

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();
  bool status = false;


void setup() {
  Serial.begin(750);
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
  MIDI.setHandleControlChange(ControlChange);
  //MIDI.setHandlePitchBend(flicker);
}

void loop() { // Main loop
  // Serial.println("moi kerel");
  // Serial.print("\n");
  // delay(1000);
  if(status == true ) {
    flicker(1);
  }
  MIDI.read(); // Continuously check if Midi data has been received.
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte number, byte pitch, byte velocity) { 
  digitalWrite(LED, true);  
}

void ControlChange(byte channel, byte number, byte pitch, byte velocity)  {

  if(number == 1 && status == false) {
    digitalWrite(LED, true);
    status = true;
  } else {
    digitalWrite(LED, false);
    status = false;
  }
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte note, byte pitch, byte velocity) { 
  digitalWrite(LED,LOW);  //Turn LED off
  
}

void flicker(byte count) {
  for(int i = 0; i < count; i++) {
    digitalWrite(LED,true);
    delay(40);
    digitalWrite(LED,false);
    delay(40);

  }

}

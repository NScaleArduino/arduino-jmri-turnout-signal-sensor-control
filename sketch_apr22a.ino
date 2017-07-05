#include <CMRI.h>
#include <SPI.h>

// References:
// http://thenscaler.com/?page_id=661
// http://thenscaler.com/?page_id=174
// https://github.com/madleech/ArduinoCMRI
// http://jmri.org/community/clinics/NMRA2008/LayoutEditorClinic2008/LayoutEditorClinic.pdf

#include <VarSpeedServo.h>


const int SENSOR_GAP = 99;
const int ANALOG_GAP = 40;

const int ALIGN_MAIN = 80;
const int ALIGN_DIVERGENT = 115;

const int STEP_DELAY = 10;
const int NUM_TURNOUTS = 19;
const int NUM_TOGGLES = 34;
const int NUM_SENSORS = 16;


VarSpeedServo servos[NUM_TURNOUTS];

CMRI cmri0(0); // first SMINI, 24 inputs, 48 outputs
CMRI cmri1(1); // second SMINI, another 24 inputs and another 48 outputs

bool CONNECTED = false;


typedef struct TURNOUT_DEF {
  int pin;
  int pos_main;
  int pos_div;
  int pos_default;
};

typedef struct TURNOUT_DATA {
  TURNOUT_DEF data;
  int alignment;
  int target_pos;
};


typedef struct TOGGLES {
  int pin;
  bool on;
};

typedef struct SENSORS {
  int pin;
};

TOGGLES toggles[NUM_TOGGLES] = {
  {21, LOW},
  {22, LOW},
  {23, LOW},
  {24, LOW},
  {25, LOW},
  {26, LOW},
  {27, LOW},
  {28, LOW},
  {29, LOW},
  {30, LOW},
  {31, LOW},
  {32, LOW},
  {33, LOW},
  {34, LOW},
  {35, LOW},
  {36, LOW},
  {37, LOW},
  {38, LOW},
  {39, LOW},
  {40, LOW},
  {41, LOW},
  {42, LOW},
  {43, LOW},
  {44, LOW},
  {45, LOW},
  {46, LOW},
  {47, LOW},
  {48, LOW},
  {49, HIGH},
  {50, HIGH},
  {51, HIGH},
  {52, HIGH},
  {53, HIGH},
  {54, HIGH},
};


TURNOUT_DATA turnouts[NUM_TURNOUTS] = {
  {{2, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{3, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{4, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{5, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{6, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{7, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{8, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{9, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN}, 
 {{10, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{11, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{12, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{13, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{14, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{15, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{16, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{17, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{18, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{19, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
 {{20, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
};

SENSORS sensors[NUM_SENSORS] = {
  {A0},
  {A1},
  {A2},
  {A3},
  {A4},
  {A5},
  {A6},
  {A7},
  {A8},
  {A9},
  {A10},
  {A11},
  {A12},
  {A13},
  {A14},
  {A15},
};



void setup()
{
  Serial.begin(9600, SERIAL_8N2);
  
  SPI.begin();

  for (int i = 0; i < NUM_TURNOUTS; i++) {
    servos[i].attach(turnouts[i].data.pin);

    setTurnout(i, turnouts[i].data.pos_default, true);
  }

  for (int i = 0; i < NUM_TOGGLES; i++) {
      pinMode(toggles[i].pin, OUTPUT);

      setLed(i, toggles[i].on, true);
  }
  
}

char c;
void loop()
{
    CONNECTED = true;


     while (Serial.available() > 0)
     {
       c = Serial.read();
       cmri0.process_char(c);
       cmri1.process_char(c);
     
        
      for (int i = 0; i < NUM_TURNOUTS; i++) {
        setTurnout(i, getBit(turnouts[i].data.pin), false);
      }
    
      for (int i = 0; i < NUM_TOGGLES; i++) {
        setLed(i, getBit(toggles[i].pin), false);
      }
  
      for (int i = 0; i < NUM_SENSORS; i++) {
        //Serial.println(sensors[i].pin);
        setBit(i, analogRead(sensors[i].pin) < 300 && analogRead(sensors[i].pin) > 15 ? HIGH : LOW);
      }
    }
}

int getBit(int pin) {
  if (pin < 48) {
    return cmri0.get_bit(pin - 2);
  } else {
    return cmri1.get_bit(pin  - 48);
  }
}

void setBit(int pin, int status) {
  cmri0.set_bit(pin, status);
}

void setLed(int id, int status, bool force){

  if (!CONNECTED) {
    status = toggles[id].on;
  }

  if (toggles[id].on == status && force == false) {
    return true;
  }
  
  toggles[id].on =  status;
    
  digitalWrite(toggles[id].pin, status);
}

void setTurnout(int id, byte align, bool force) {
  if (!CONNECTED) {
    align = turnouts[id].data.pos_default;
  }
  
  if (turnouts[id].alignment == align && force == false) {
    return true;
  }
  
  switch (align) {
    case HIGH:
      turnouts[id].target_pos = turnouts[id].data.pos_main;

      break;
    case LOW:
      turnouts[id].target_pos = turnouts[id].data.pos_div;

      break;
  }

  turnouts[id].alignment = align;

  servos[id].write(turnouts[id].target_pos, STEP_DELAY, false);
}

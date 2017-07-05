
#include <SPI.h>


// http://thenscaler.com/?page_id=661
// http://thenscaler.com/?page_id=174
/// https://github.com/madleech/ArduinoCMRI
// http://jmri.org/community/clinics/NMRA2008/LayoutEditorClinic2008/LayoutEditorClinic.pdf

#include <VarSpeedServo.h>

const int ANALOG_GAP = 40;

const int ALIGN_MAIN = 80;
const int ALIGN_DIVERGENT = 115;

const int STEP_DELAY = 10;
const int NUM_TURNOUTS = 16;
const int NUM_TOGGLES = 34;


VarSpeedServo servos[NUM_TURNOUTS];

bool CONNECTED = false;


typedef struct TURNOUT_DEF {
  int pin;
  char io;
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
  char io;
  bool on;
};


TOGGLES toggles[NUM_TOGGLES] = {
  {21, A0, LOW},
  {22, A1, LOW},
  {23, A2, LOW},
  {24, A3, LOW},
  {25, A5, LOW},
  {26, A6, LOW},
  {27, A7, LOW},
  
  {28, A8, LOW},
  {29, A9, LOW},
  {30, A10, LOW},
  {31, A11, LOW},
  {32, A12, LOW},
  {33, A13, LOW},
  {34, A14, LOW},
  {35, A15, LOW},
};



TURNOUT_DATA turnouts[NUM_TURNOUTS] = {
  {{2, A0, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{3, A1, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{4, A2, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{5, A3, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{6, A4, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{7, A5, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{8, A6, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},
  {{9, A7, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN}, 
  {{10, A8, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  {{11, A9, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  {{12, A10, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  {{13, A11, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  {{14, A12, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  {{15, A13, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  {{16, A14, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  {{17, A15, ALIGN_MAIN, ALIGN_DIVERGENT, ALIGN_MAIN}, HIGH, ALIGN_MAIN},  
  };




void setup()
{
  Serial.begin(9600);

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
    
    for (int i = 0; i < NUM_TURNOUTS; i++) {
      setTurnout(i, getBit(turnouts[i].data.io), false);
    }
  
    for (int i = 0; i < NUM_TOGGLES; i++) {
      setLed(i, getBit(toggles[i].io), false);
    }
}

int getBit(char io) {
 // Serial.println(digitalRead(io));
  return analogRead(io) == 0 ? HIGH : LOW;
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
    Serial.println(id); Serial.println(align);
    
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

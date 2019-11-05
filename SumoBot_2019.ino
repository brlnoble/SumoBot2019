//#########################################
//############ Sumobot Code V1 ############
//############   March, 2019   ############
//#########################################


//Front Ping Sensor
#define fPtrig 2 //front ping trigger
#define fPech 3 //front ping echo

//Rear Ping Sensor
#define rPtrig 5 //rear ping trigger
#define rPech 6 //rear ping echo

//Line Sensors
#define fLem A0 //front line emitter at analog 0
#define rLem A1 //rear line emitter at analog 1

//Motors
#define mL1 10 //left motor pin 1
#define mL2 11 //left motor pin 2
#define mR1 12 //right motor pin 1
#define mR2 13 //right motor pin 2



void setup() {
  Serial.begin(9600); //Starts serial with 9600 BAUD
  
  //Assigning input/output pins
  pinMode(fPtrig, OUTPUT);
  pinMode(fPech, INPUT);
  pinMode(rPtrig, OUTPUT);
  pinMode(rPech, INPUT);
  pinMode(fLem, INPUT);
  pinMode(rLem, INPUT);
  pinMode(mL1, OUTPUT);
  pinMode(mL2, OUTPUT);
  pinMode(mR1, OUTPUT);
  pinMode(mR2, OUTPUT);

  //Defaulting motors to off
  digitalWrite(mL1, LOW);
  digitalWrite(mL2, LOW);
  digitalWrite(mR1, LOW);
  digitalWrite(mR2, LOW);

  delay(4000); //NEED DELAY AT START
  forwards();
}

//########################################################
void loop() { //THIS RUNS EVERYTHING
  
  if(frontLine()) {
    //Sensed white line in front
    backwards();
    delay(1000); //moves back for 1 second, change to a proper distance later
  }
  else if(rearLine()) {
    //Sensed white line in back
    forwards();
    delay(1000); //moves forward for 1 second, change to a proper distance later
  }
  
  else if(frontPing() <= 40) {
    forwards(); //something is in front of us
  }
  else if(rearPing() <= 40) {
    backwards(); //something is behind us
  }
  else { //nothing around us
    left();
  }
} //END LOOP
//########################################################


//Additional functions to do various tasks

int frontPing() { //checks distance using front ping sensor
  //sends a pulse out of the trigger
  digitalWrite(fPtrig, LOW);
  delayMicroseconds(2);
  digitalWrite(fPtrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(fPtrig, LOW);

  long dur = pulseIn(fPech, HIGH); //reads a pulse from the echo only if it is HIGH, finding the time it takes to return
  if(dur == 0) {
    return 0;
  }
  else {
    int dist = dur/29/2;
    return dist; //returns distance in cm
  }
}


int rearPing() { //checks distance using rear ping sensor
  //sends a pulse out of the trigger
  digitalWrite(rPtrig, LOW);
  delayMicroseconds(2);
  digitalWrite(rPtrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(rPtrig, LOW);

  long dur = pulseIn(rPech, HIGH); //reads a pulse from the echo only if it is HIGH, finding the time it takes to return
  if(dur == 0) {
    return 0;
  }
  else {
    int dist = dur/29/2;
    return dist; //returns distance in cm
  }
}


bool frontLine() { //checks if there is white below the front sensor
  int check = analogRead(fLem);
  Serial.println(check); //used to check data
  if(check > 600) { // if the voltage is above a certain value, we are on black. 100 was determined experimentally
    return false;
  }
  else {
    return true;
  }
}


bool rearLine() { //checks if there is white below the front sensor
  int check = analogRead(rLem);
  //Serial.println(check); //used to check data
  if(check > 600) { // if the voltage is above a certain value, we are on black. 100 was determined experimentally
    return false;
  }
  else {
    return true;
  }
}


void leftF() { //left motor forwards
  digitalWrite(mL1, HIGH);
  digitalWrite(mL2, LOW);
}

void leftR() { //left motor backwards
  digitalWrite(mL1, LOW);
  digitalWrite(mL2, HIGH);
}

void rightF() { //right motor forwards
  digitalWrite(mR1, HIGH);
  digitalWrite(mR2, LOW);
}

void rightR() { //right motor backwards
  digitalWrite(mR1, LOW);
  digitalWrite(mR2, HIGH);
}


//Functions for motor control

void forwards() {
  leftF();
  rightR();
}

void backwards() {
  leftR();
  rightR();
}

void right() {
  leftF();
  rightR();
}

void left() {
  leftR();
  rightF();
}

void Stop() {
  digitalWrite(mL1, LOW);
  digitalWrite(mL2, LOW);
  digitalWrite(mR1, LOW);
  digitalWrite(mR2, LOW);
}


char* names[] = {"mini Tomato", "blueberry"};
int pins[] = {2, 3};
unsigned long timeOn[] = {2000000, 0}; // time that the pump stays on for each 10000 = 10s pin in order
unsigned long timeOff[] = {3600000, 0}; // time pump stays off -- 3600000 = 1 hr
unsigned long startTime[] = {0, 0}; // time pump was turned on, in ms
bool pumpOn[] = {true, false};
bool disable[] = {false, true};

int pumps = sizeof(pins)/sizeof(int);

void setup() {
  Serial.begin(9600);
  Serial.println(pumps);
  initializePumps();
  //testPumps();
  digitalWrite(pins[0], 1);
  Serial.println("pump on");
  startTime[0] = millis();
  pumpOn[0] = true;
}

void loop() {
  for (int i = 0; i<pumps; i++) {
    if (disable[i]) {continue;};
    if (pumpOn[i])
    {
      if (millis() - startTime[i] > timeOn[i])
      {
        Serial.println("pump off");
        digitalWrite(pins[i], 0);
        startTime[i] = millis();
        pumpOn[i] = false;
      }
    }
    else if (not pumpOn[i])
    {
      if (millis() - startTime[i] > timeOff[i])
      {
        digitalWrite(pins[i], 1);
        Serial.println("pump on");
        startTime[i] = millis();
        pumpOn[i] = true;
      }
    }
  }
}

void testPumps() {
    for (int i = 0; i<pumps; i++) {
    Serial.print("testing: ");
    Serial.println(names[i]);
    digitalWrite(pins[i], 1);
    delay(1000);
    digitalWrite(pins[i], 0);
    delay(1000);
  }
}

void initializePumps() {
  for (int i = 0; i<pumps; i++) {
    pinMode(pins[i], OUTPUT); // make sure out pin is set to 'off'
    //i.e. pulls pin to ground
  }
}


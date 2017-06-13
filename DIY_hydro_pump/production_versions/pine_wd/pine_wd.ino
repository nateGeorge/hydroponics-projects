char* names[] = {"pineapple", "blueberry", "nothing"};
int pins[] = {2, 3, 4};
unsigned long timeOn[] = {30000, 15000, 0}; // time that the pump stays on for each 10000 = 10s
// 420000 = 7 minutes, 240000 = 4 mins
unsigned long timeOff[] = {3570000, 3450000, 3600000}; // time pump stays off -- 3600000 = 1 hr
// 3180000 = 53 minutes, 33600000 = 56 mins
unsigned long startTime[] = {0, 0, 0}; // time pump was turned on, in ms
unsigned long startDelay[] = {0, 35000, 500000}; // delay before starting cycle
unsigned long timeNow; // current time in ms

bool pumpOn[] = {false, false, false};
bool disable[] = {false, false, false};

int pumps = sizeof(pins)/sizeof(int);

void setup() {
  Serial.begin(9600);
  Serial.println(pumps);
  initializePumps();
  //testPumps();
  digitalWrite(pins[0], 1);
  Serial.println("pump 0 on");
  startTime[0] = millis();
  pumpOn[0] = true;
}

void loop() {
  for (int i = 0; i<pumps; i++) {
    timeNow = millis();
    if (disable[i]) {continue;};
    if (pumpOn[i])
    {
      if (timeNow > startTime[i] && timeNow - startTime[i] > timeOn[i])
      {
        Serial.print("pump ");
        Serial.print(i);
        Serial.println(" off");
        digitalWrite(pins[i], 0);
        startTime[i] = millis();
        pumpOn[i] = false;
      }
    }
    else if (not pumpOn[i])
    {
      if (timeNow > startDelay[i])
      {
        if (startDelay[i] > 0 and timeNow > startDelay[i])
        {
          digitalWrite(pins[i], 1);
          Serial.print("pump ");
          Serial.print(i);
          Serial.println(" on");
          startTime[i] = millis();
          pumpOn[i] = true;
          startDelay[i] = 0;
        }
        if (timeNow - startTime[i] > timeOff[i])
        {
          digitalWrite(pins[i], 1);
          Serial.print("pump ");
          Serial.print(i);
          Serial.println(" on");
          startTime[i] = millis();
          pumpOn[i] = true;
          startDelay[i] = 0;
        }
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


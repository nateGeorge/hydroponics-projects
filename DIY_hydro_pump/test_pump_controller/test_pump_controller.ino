int miniTomato = 2; // pin number for the transistor to the tomato waterer
int blueBerry = 3; // pin for transistor to blueberry plant

unsigned long timeOn; // time that the pump stays on
unsigned long timeOff; // time pump stays off

void setup() {
  // put your setup code here, to run once:
  pinMode(miniTomato, OUTPUT); // make sure out pin is set to 'off'
  //i.e. pulls pin to ground
  digitalWrite(miniTomato, 1);
  delay(1000);
  digitalWrite(miniTomato, 0);
  delay(1000);
  digitalWrite(blueBerry, 1);
  delay(1000);
  digitalWrite(blueBerry, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
}

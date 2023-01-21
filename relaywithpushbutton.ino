
const int relay = 13;
const int buttonPin = 9;// the pin our push button is on

void setup() {
  pinMode(relay, OUTPUT); // set relay pin as output
  pinMode(buttonPin,INPUT_PULLUP); // set button as input
}

void loop() {
  int buttonState = digitalRead(buttonPin); // take a reading

  if(buttonState == HIGH)
  {
    digitalWrite(relay,LOW); //turn the relay off
  }
  else
  {
    digitalWrite(relay,HIGH);//turn the relay on
  }
}

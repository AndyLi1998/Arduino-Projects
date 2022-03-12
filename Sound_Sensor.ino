int SoundSensorDI=5;
int LEDPwr=4;

void setup() {
  // put your setup code here, to run once:


  pinMode(SoundSensorDI,INPUT);
  pinMode(LEDPwr,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  if (digitalRead(SoundSensorDI)==HIGH){
    digitalWrite(LEDPwr,HIGH);
  }
  else{
    digitalWrite(LEDPwr,LOW);
  }
}

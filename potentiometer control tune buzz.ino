int buzzPin=2;
int dt1=1;
int dt2=2;
int i;
float potVal;
int potPin=A1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  pinMode(potPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  potVal=analogRead(potPin);
  Serial.println(potVal);

  digitalWrite(buzzPin,HIGH);
  delay(potVal/100);
  digitalWrite(buzzPin,LOW);
  delay(potVal/100);
  
  

}

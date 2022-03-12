int motorIP1=2;
int motorIP2=3;
int speedpin=4;
int mspeed=255;

void setup() {
  // put your setup code here, to run once:
pinMode(motorIP1,OUTPUT);
pinMode(motorIP2,OUTPUT);
pinMode(speedpin,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(motorIP1,HIGH);
digitalWrite(motorIP2,LOW);
analogWrite(speedpin,mspeed);

}

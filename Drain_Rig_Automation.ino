
int ENAIn=2;
int solenoidcontrolIn=3;
int solenoidcontrolOut=9;
int ENAOut=12;
int DIRpin=11;
int PULpin=10;
int counter=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENAIn,INPUT);
  pinMode(solenoidcontrolIn,INPUT);
  pinMode(solenoidcontrolOut,OUTPUT);
  pinMode(ENAOut,OUTPUT);
  pinMode(DIRpin,OUTPUT);
  pinMode(PULpin,OUTPUT);
  Serial.begin(9600);
  digitalWrite(solenoidcontrolOut,LOW);
  digitalWrite(DIRpin,HIGH);
}


void loop() {
  // put your main `code here, to run repeatedly:
  
  while (digitalRead(ENAIn)==HIGH){


      if (digitalRead(solenoidcontrolIn)==HIGH&&digitalRead(solenoidcontrolOut)==HIGH){
        digitalWrite(solenoidcontrolOut,LOW);
        Serial.println(digitalRead(solenoidcontrolOut));
        delay(5000);
        break;
      }
      
      else if(digitalRead(solenoidcontrolIn)==HIGH&&digitalRead(solenoidcontrolOut)==LOW){
        digitalWrite(solenoidcontrolOut,HIGH);
        
        Serial.println(digitalRead(solenoidcontrolOut));
        delay(5000);
        break;
      }

    Serial.println("Im outta if");
 
    digitalWrite(ENAOut,LOW);
    digitalWrite(PULpin,HIGH);
    delayMicroseconds(400);
    digitalWrite(PULpin,LOW);
    delayMicroseconds(400);
    digitalRead(ENAIn);
  }
  Serial.println("Im outta while");
  
}

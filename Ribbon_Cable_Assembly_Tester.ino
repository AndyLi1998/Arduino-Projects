int Sel0=2; 
int Sel1=3;
int Sel2=4;
int Sel3=5;
int FRP=6; //First Row Pass
int SRP=7; //Second Row Pass
int LED_Power=8; //one pin power two LED, default condition FAIL light on
int start_button=9;
int short_check=10;
int counter=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(Sel0,OUTPUT);
  pinMode(Sel1,OUTPUT);
  pinMode(Sel2,OUTPUT);
  pinMode(Sel3,OUTPUT);
  pinMode(FRP,INPUT);
  pinMode(SRP,INPUT);
  pinMode(LED_Power,OUTPUT);
  pinMode(start_button,INPUT);
  pinMode(short_check,INPUT);
  Serial.begin(9600);

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(start_button)==HIGH){
    //set up inital condition: 0000
     digitalWrite(Sel0,LOW);
     digitalWrite(Sel1,LOW);
     digitalWrite(Sel2,LOW);
     digitalWrite(Sel3,LOW);

     //two rows
     for (int i=0;i<2;i++){
      // eight columns
      for (int j=0;j<8;j++){
        
        if (i==0 && digitalRead(FRP)==HIGH && digitalRead(short_check)==HIGH){ //confirming reading at first row, First Row Pass is high, 16 input XOR block output is high (only one pin is high, thus no short)
          counter=counter+1;
          if (j==0){
            // 0001
            digitalWrite(Sel3,HIGH);
          }
          else if (j==1){
            // 0010
            digitalWrite(Sel2,HIGH);
            digitalWrite(Sel3,LOW);
          }
          else if (j==2){
            //0011
            digitalWrite(Sel3,HIGH);
          }
          else if (j==3){
            //0100
            digitalWrite(Sel1,HIGH);
            digitalWrite(Sel2,LOW);
            digitalWrite(Sel3,LOW);
          }
          else if (j==4){
            //0101
            digitalWrite(Sel3,HIGH);
          }
          else if (j==5){
            //0110
            digitalWrite(Sel2,HIGH);
            digitalWrite(Sel3,LOW);
          }
          else if (j==6){
            //0111
            digitalWrite(Sel3,HIGH);
          }
          else if (j==7){
            //1000
            digitalWrite(Sel0,HIGH);
            digitalWrite(Sel1,LOW);
            digitalWrite(Sel2,LOW);
            digitalWrite(Sel3,LOW);
          }
          delay(500);
        }


        
        else if (i==1 && digitalRead(SRP)==HIGH && digitalRead(short_check)==HIGH){ //Second row, same thing
          counter=counter+1;
          if (j==0){
            // 1001
            digitalWrite(Sel3,HIGH);
          }
          else if (j==1){
            // 1010
            digitalWrite(Sel2,HIGH);
            digitalWrite(Sel3,LOW);
          }
          else if (j==2){
            //1011
            digitalWrite(Sel3,HIGH);
          }
          else if (j==3){
            //1100
            digitalWrite(Sel1,HIGH);
            digitalWrite(Sel2,LOW);
            digitalWrite(Sel3,LOW);
          }
          else if (j==4){
            //1101
            digitalWrite(Sel3,HIGH);
          }
          else if (j==5){
            //1110
            digitalWrite(Sel2,HIGH);
            digitalWrite(Sel3,LOW);
          }
          else if (j==6){
            //1111
            digitalWrite(Sel3,HIGH);
          }
          else if (j==7){
            break;
          }
          delay(500);
        }
        
      }
     }

// if all pins are continuous and no short exists, Pass light will turn on.
     if (counter==16) {
      digitalWrite(LED_Power, HIGH);
      delay(3000);
      break;
     }
     else {
      digitalWrite(LED_Power, LOW);
      delay(3000);
      break;
     }

    
  }
}

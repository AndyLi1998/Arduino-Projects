// define pin numbers
const int stepX = 2;
const int dirX  = 5;
const int stepY = 3;
const int dirY  = 6;
const int stepZ = 4;
const int dirZ  = 7;
const int enPin = 8;

//motor status
const byte numMotors = 3;
byte motorStatus[numMotors] = {0, 0, 0};

//buffer
const byte buffSize = 40;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;

char messageFromPC[buffSize] = {0};

//time
unsigned long curMillis;
unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;

void setup() {
  Serial.begin(9600);
  
  // Sets the two pins as Outputs
  pinMode(stepX,OUTPUT);
  pinMode(dirX,OUTPUT);

  pinMode(stepY,OUTPUT);
  pinMode(dirY,OUTPUT);

  pinMode(stepZ,OUTPUT);
  pinMode(dirZ,OUTPUT);

  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  Serial.println("<Arduino is ready>");
}

void loop() {
  // put your main code here, to run repeatedly:
  curMillis = millis();
  getDataFromPC();
  moveMotors();
}

void getDataFromPC() {

    // receive data from PC and save it into inputBuffer
    
  if(Serial.available() > 0) {

    char x = Serial.read();

      // the order of these IF clauses is significant
      
    if (x == endMarker) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }
    
    if(readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }

    if (x == startMarker) { 
      bytesRecvd = 0; 
      readInProgress = true;
    }
  }
}

void parseData() {

    // split the data into its parts
    // assumes the data will be received as (eg) 0,1,35
    
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(inputBuffer,","); // get the first part
  motorStatus[0] = atoi(strtokIndx); //  convert to an integer
  
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  motorStatus[1] = atoi(strtokIndx);
  
  strtokIndx = strtok(NULL, ","); 
  motorStatus[2] = atoi(strtokIndx); 
}

void moveMotors() {
    for(int x = 0; x < 100; x++) {
        if (motorStatus[0] == 1) {
          digitalWrite(stepX,HIGH);

          delayMicroseconds(1000);

          digitalWrite(stepX,LOW);

          delayMicroseconds(1000);
        }

    //delayMicroseconds(1000);
    
        if (motorStatus[1] == 1) {
          digitalWrite(stepY,HIGH);

          delayMicroseconds(1000);

          digitalWrite(stepY,LOW);

          delayMicroseconds(1000);
        }

    //delayMicroseconds(1000);
    
        if (motorStatus[2] == 1) {

          digitalWrite(stepZ,HIGH);

          delayMicroseconds(1000);

          digitalWrite(stepZ,LOW);

          delayMicroseconds(1000);

        }
    }

    //delayMicroseconds(1000);
}

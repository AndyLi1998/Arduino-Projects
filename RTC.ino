#include <dht.h>
#define outPin 8
#define pushButton 7
dht DHT;
#include <Wire.h>
#include <LiquidCrystal.h>
#include <RTClib.h>

DateTime now;
char daysOfTheWeek[7][12]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

RTC_DS3231 rtc;//if mega:21(SCL);20(SDA)    if Uno:A5(SCL);A4(SDA)

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pushButtonState=0;
int lastpushButtonState=0;
int pushcounter=0;
int lastpushcounter=0;

void showDate(void);
void showTime(void);
void showDay(void);


void setup() {
  // put your setup code here, to run once:
  pinMode(pushButton,INPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Clears the LCD screen
  lcd.clear();

  if(!rtc.begin()){
    Serial.println("Couldn't find RTC module");
    while(1);
  }

  if (rtc.lostPower()){
    Serial.println("RTC lost power");
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  }
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(pushcounter);
  while (pushcounter==lastpushcounter){
    pushButtonState=digitalRead(pushButton);
    if (pushButtonState!=lastpushButtonState){
      if(pushButtonState==HIGH){
        pushcounter++;
      }
      delay(500);
      break;
    }
    int readData = DHT.read11(outPin);
    float t = DHT.temperature;  // Read temperature
    float h = DHT.humidity;   // Read humidity
    lcd.setCursor(0,0);
    lcd.print("Temp.: ");
    lcd.print(t);
    lcd.print((char)223);//shows degrees character
    lcd.print("C");
    
    lcd.setCursor(0,1);
    lcd.print("Humi.: ");
    lcd.print(h);
    lcd.print("%");  
  }
  lcd.clear();
  lastpushcounter=pushcounter;
  Serial.println(pushcounter);
  
  while (pushcounter==lastpushcounter){
    pushButtonState=digitalRead(pushButton);
    if (pushButtonState!=lastpushButtonState){
      if(pushButtonState==HIGH){
        pushcounter++;
      }
      delay(500);
      break;
    }
    now=rtc.now();
    showDate();
    showDay();
    showTime();
  }
  lcd.clear();
  lastpushcounter=pushcounter;
  
}

void showDate(){
  lcd.setCursor(0,0);
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());
}

void showDay()
 {
  lcd.setCursor(11,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
 }
 void showTime()
 {
  lcd.setCursor(0,1);
  lcd.print("Time:");
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second());
  lcd.print("    ");
 } 

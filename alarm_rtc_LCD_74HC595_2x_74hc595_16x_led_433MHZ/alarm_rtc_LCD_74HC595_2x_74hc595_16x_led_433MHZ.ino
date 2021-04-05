/*

  ---Shift Register 74HC595-LCD1602--
  SR SER - Pin 14 to Arduino pin PD2
  SR RCK - Pin 12 to Arduino pin PD3 and (LCD E 1602 Pin 6)
  SR SCK - Pin 11 to Arduino pin PD4
  SR GND - Pin  8 to Ground
  SR VCC - Pin 16 to +5v
  SR OE - Pin 13 to Ground
  SR SCLR - Pin 10 to +5v
  
  -----Shift Reg to LCD--------
  SR QG - Pin 6 to D7 (LCD 1602 Pin 14)
  SR QF - Pin 5  to D6 (LCD 1602 Pin 13)
  SR QE - Pin 4  to D5 (LCD 1602 Pin 12)
  SR QD - Pin 3  to D4 (LCD 1602 Pin 11)
  SR QC - Pin 2  to LCD RS (LCD 1602 Pin 4)
*/


#include <TimeLib.h>
#include <TimeAlarms.h>
#include <RemoteSwitch.h>
#include <RCSwitch.h>
#define D_aan 1398037
#define D_uit 1398036

RCSwitch mySwitch = RCSwitch();

#include <virtuabotixRTC.h> 
virtuabotixRTC myRTC(8, 9, 10); // RTC PINS CLOCK, DATA, RESET, ARDUINO PINS D8, D9, D10

#include <LiquidCrystal_SR.h>

//SHIFT 2 74HC595 MASTER 16 LED 
#define SHIFT_DATA A1  //SHIFT 2 DATA, ARDUINO ANALOG A1
#define SHIFT_LATCH A2 //SHIFT 2 LATCH, ARDUINO ANALOG A2 
#define SHIFT_CLK A3   //SHIFT 2 CLOCK, ARDUINO ANALOG A3

//SHIFT 1 75HC595 MASTER LCD 1602
#define  DATAPIN  2    //SHIFT 1 DATA, ARDUINO D2
#define  CLOCKPIN 4    //SHIFT 1 CLOCK, ARDUINO D4
#define  STROBEPIN 3   //SHIFT 1 LATCH, ARDUINO D3

LiquidCrystal_SR lcd(DATAPIN, CLOCKPIN, STROBEPIN);

#define STROOM 5 // LED - RELAY STROOM AAN /UIT
#define KOFFIE 6 // LED - RELAY KOFFIE AAN /UIT

int allon  = 0b1111111111111111;  //  1 alles aan
int alloff = 0b0000000000000000;  //  2 alles uit
int LEDA = 0b0101010101010101;    //  3 om en om
int LEDB = 0b1010101010101010;    //  4 om en om

//SHIFT 2 MASTER 
int LEDa1 = 0b0000000100000000;   //  1 led 1 aan
int LEDa2 = 0b0000001000000000;   //  2 led 2 aan
int LEDa3 = 0b0000010000000000;   //  3 led 3 aan
int LEDa4 = 0b0000100000000000;   //  4 led 4 aan
int LEDa5 = 0b0001000000000000;   //  5 led 5 aan
int LEDa6 = 0b0010000000000000;   //  6 led 6 aan
int LEDa7 = 0b0100000000000000;   //  7 led 7 aan
int LEDa8 = 0b1000000000000000;   //  8 led 8 aan

//SHIFT 3 SLAVE
int LEDb1 = 0b0000000000000001;   //  9 led 9 aan
int LEDb2 = 0b0000000000000010;   //  10 led 10 aan
int LEDb3 = 0b0000000000000100;   //  11 led 11 aan
int LEDb4 = 0b0000000000001000;   //  12 led 12 aan
int LEDb5 = 0b0000000000010000;   //  13 led 13 aan
int LEDb6 = 0b0000000000100000;   //  14 led 14 aan
int LEDb7 = 0b0000000001000000;   //  15 led 15 aan
int LEDb8 = 0b0000000010000000;   //  16 led 16 aan



void setup() {

  pinMode(STROOM, OUTPUT);
  pinMode(KOFFIE, OUTPUT);
  pinMode(A1, OUTPUT); // SHIFT 2 DATA, ARDUINO ANALOG A1
  pinMode(A2, OUTPUT); // SHIFT 2 LATCH, ARDUINO ANALOG A2 
  pinMode(A3, OUTPUT); // SHIFT 2 CLOCK, ARDUINO ANALOG A3

  pinMode(11, OUTPUT); // Datapin 433mhz transmit - ARDUINO PIN D11
  mySwitch.enableTransmit(11);

  lcd.begin(16, 2);
  lcd.home ();
  myRTC.setDS1302Time(00, 39, 15, 5, 03, 4, 2021); // INSTELLEN TIJD RTC.  NA 1 KEER UPLOADEN DEZE REGEL MET // NIET MEER LEESBAAR VOOR ARDUINO

  setTime(15, 39, 00, 4, 03, 21); // INSTELLEN ALARM TIJD - GELIJK AAN TIJD VAN RTC

  // creeer alarmen
  Alarm.alarmRepeat(15, 40, 30, POWER);      // TIJDSTIP .... STROOM IS AAN
  Alarm.alarmRepeat(15, 40, 50, COFFEE);     // TIJDSTIP .... KOFFIE LOOPT
  Alarm.alarmRepeat(15, 41, 00, POWEROFF);   // TIJDSTIP .... KOFFIE KLAAR STROOM UIT

  Alarm.alarmRepeat(15, 41, 20, KAMERAAN);   //  STAANDE LAMP AAN
  Alarm.alarmRepeat(15, 41, 30, KAMERUIT);   //  STAANDE LAMP UIT
  Alarm.alarmRepeat(15, 41, 40, KAMERAAN);   //  STAANDE LAMP AAN
  
  Alarm.alarmRepeat(15, 42, 10, LEDOMOM);    //  OM EN OM AAN UIT
  Alarm.alarmRepeat(15, 42, 15, LEDCHASER);  //  CHASER VAN 1 TOT 16
  
  Alarm.alarmRepeat(15, 42, 20, LEDA1);      //  1
  Alarm.alarmRepeat(15, 42, 25, LEDA2);      //  2
  Alarm.alarmRepeat(15, 42, 30, LEDA3);      //  3
  Alarm.alarmRepeat(15, 42, 35, LEDA4);      //  4
  Alarm.alarmRepeat(15, 42, 40, LEDA5);      //  5
  Alarm.alarmRepeat(15, 42, 45, LEDA6);      //  6
  Alarm.alarmRepeat(15, 42, 50, LEDA7);      //  7
  Alarm.alarmRepeat(15, 42, 55, LEDA8);      //  8

  Alarm.alarmRepeat(15, 43, 00, LEDB1);      //  9
  Alarm.alarmRepeat(15, 43, 05, LEDB2);      //  10
  Alarm.alarmRepeat(15, 43, 10, LEDB3);      //  11
  Alarm.alarmRepeat(15, 43, 15, LEDB4);      //  12
  Alarm.alarmRepeat(15, 43, 20, LEDB5);      //  13
  Alarm.alarmRepeat(15, 43, 25, LEDB6);      //  14
  Alarm.alarmRepeat(15, 43, 30, LEDB7);      //  15
  Alarm.alarmRepeat(15, 43, 35, LEDB8);      //  16

  Alarm.alarmRepeat(15, 43, 40, LEDON);      //  ALLES AAN
  Alarm.alarmRepeat(15, 43, 45, LEDOFF);     //  ALLES UIT
}


void loop() {
  digitalClockDisplay();
  Alarm.delay(1000);
  lcd.clear();
}

//functies voor alarmen

void KAMERAAN() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("STAANDE LAMP AAN");
  mySwitch.send(D_aan, 24);
  delay(5000);
}

void KAMERUIT() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("STAANDE LAMP UIT");
  mySwitch.send(D_uit, 24);
  delay(5000);
}

void POWER() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("De stroom = AAN");
  digitalWrite(STROOM, HIGH);
  delay(5000);
}

void COFFEE() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("De koffie loopt");
  digitalWrite(KOFFIE, HIGH);
  delay(5000);
  digitalWrite(KOFFIE, LOW);
}

void POWEROFF() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("De stroom = UIT");
  lcd.setCursor(0, 0);
  lcd.print("koffie is klaar");
  digitalWrite(STROOM, LOW);
  delay(5000);
}

void LEDOMOM() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("OM EN OM");

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDA >> 8));  // VERTUURD DE EERSTE 8 BITS (0-7)
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDA);         // VERSTUURD DE LAATSTE 8 BITS (8-16)
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDB >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDB);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDA >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDA);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDB >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDB);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDA >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDA);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDB >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDB);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDCHASER() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("CHASER");

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa1 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa1);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa2 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa2);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa3 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa3);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa4 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa4);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa5 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa5);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa6 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa6);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa7 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa7);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa8 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa8);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb1 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb1);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb2 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb2);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb3 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb3);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb4 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb4);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb5 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb5);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb6 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb6);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb7 >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb7);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(500);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb8 >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb8);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(100);
}

void LEDA1() {

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-1");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa1 >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa1);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDA2() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-2");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa2 >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa2);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDA3() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-3");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa3 >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa3);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDA4() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-4");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa4 >> 8)); 
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa4);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDA5() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-5");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa5 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa5);        
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDA6() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-6");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa6 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa6);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDA7() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-7");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa7 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa7);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDA8() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-8");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDa8 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDa8);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB1() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-9");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb1 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb1);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB2() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-10");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb2 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb2);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB3() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-11");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb3 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb3);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB4() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-12");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb4 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb4);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB5() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-13");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb5 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb5);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB6() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-14");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb6 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb6);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB7() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-15");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb7 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb7);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDB8() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("LED-16");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (LEDb8 >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, LEDb8);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDON() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("ALLES AAN");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (allon >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, allon);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void LEDOFF() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("ALLES UIT");
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (alloff >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, alloff);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(1000);
}

void digitalClockDisplay() {

  lcd.clear(); 
  myRTC.updateTime();

  lcd.setCursor(0, 0); lcd.print('T');
  lcd.setCursor(1, 0); lcd.print('E');
  lcd.setCursor(2, 0); lcd.print('S');
  lcd.setCursor(3, 0); lcd.print('T');
  lcd.setCursor(4, 0); lcd.print('I');
  lcd.setCursor(5, 0); lcd.print('N');
  lcd.setCursor(6, 0); lcd.print('G');

  lcd.setCursor(8, 0);  if (myRTC.hours < 10) lcd.print('0'); lcd.print(myRTC.hours);
  lcd.setCursor(10, 0); lcd.print(':');
  lcd.setCursor(11, 0); if (myRTC.minutes < 10) lcd.print('0'); lcd.print(myRTC.minutes);
  lcd.setCursor(13, 0); lcd.print(':');
  lcd.setCursor(14, 0); if (myRTC.seconds < 10) lcd.print('0'); lcd.print(myRTC.seconds);

  lcd.setCursor(0, 1); if (myRTC.dayofmonth < 10) lcd.print('0'); lcd.print(myRTC.dayofmonth);
  lcd.setCursor(2, 1); lcd.print('/');
  lcd.setCursor(3, 1); lcd.print(myRTC.month);
  lcd.setCursor(4, 1); lcd.print('/');
  lcd.setCursor(5, 1); lcd.print(myRTC.year);

}

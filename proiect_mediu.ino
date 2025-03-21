#include <Servo.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int timeRemaining = 60;
int stop = 0;
volatile bool updateLCD = false;
// Creăm un obiect Servo
Servo myservo1;

int score = 0;
int lovita1 = 1;

// Variabile globale
String inputString = ""; 
boolean stringComplete = false; 
volatile int start = 0;
int current_time1;
int current_time2;
int reset = 0;

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PORNIT");


  Serial.begin(9600);
  Serial1.begin(9600);
  analogReference(DEFAULT); 
  pinMode(A0, INPUT); // setarea pinului analogic A1 ca si pin de input
  digitalWrite(A0, HIGH);
  // Atașăm servo la pinul 8
  myservo1.attach(8);
  myservo1.write(0); // Setăm servo-ul la poziția inițială (0 grade)
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(TimeTargetOne);

  Timer3.initialize(1000000);          
  Timer3.attachInterrupt(updateCountdown);

  // Rezervăm spațiu pentru sirul de preluare a datelor de intrare
  inputString.reserve(200);
}

void loop() {
  if(reset == 1){
    reset = 0;
    start = 0;
    stop = 0;
    score = 0;
    lovita1 = 0;
    lcd.clear();
  }

  if (start == 0){
    lcd.setCursor(0, 0);
    lcd.print("Select the time: ");
  }
  else
    if(stop == 1){
      lcd.setCursor(0, 0);
      lcd.print("Final score: ");
      lcd.print(score);
      lcd.setCursor(0, 1);
      lcd.print("Press Reset 0");
    }
    else{
      if(start == 1 and stop == 0){
        if (updateLCD) {
          
          updateLCD = false;
          lcd.setCursor(0, 0);
          lcd.print("Time: ");
          lcd.print(timeRemaining);
          lcd.print("   ");

          lcd.setCursor(0, 1);
          lcd.print("Score: ");
          lcd.print(score);
          lcd.print("   ");
        }

        if(lovita1 == 1){
        myservo1.write(150);
        delay(500);
        myservo1.write(0);
        lovita1 = 0;
      }
    }
  }

  if (stringComplete) {

    int time = inputString.toInt();

    if (time >= 0 && time <= 180) {

      Serial.print("Timpul setat la: ");
      Serial.println(time); 
    } else {
      Serial.println("Timpul este invalid! Introdu un numar intre 0 si 180.");
    }
    start = 1;
    if(time == 0){
      reset = 1;
      start = 0;
      time =300;
    }
    timeRemaining = time;
    // Resetăm flagul
    stringComplete = false;
    inputString ="";
    lcd.clear();
  }
}


void serialEvent1() {
  while (Serial1.available()>0) {
    

    char inChar = (char)Serial1.read();
    Serial.println(inChar);

    if (inChar != '\n') {
      inputString += inChar;
    }
    
 
    if (inChar == '\n') {
      stringComplete = true;
      
    }
  }
}


void TimeTargetOne(void)
{
  if (start == 1 and stop != 1){
    lovita1 = 0;
    int tinta1 = analogRead(A0);
    if (tinta1 < 800){
      Serial.println("prima tinta lovita");
      lovita1 = 1;
      score++;
    }
    Serial.println(tinta1);
  }
} 

void updateCountdown() {
  if (timeRemaining > 0 and start == 1) {
    timeRemaining--;
    updateLCD = true;
  }
  if (timeRemaining == 0 and stop != 1){
    stop = 1;
    Serial.println("GATA");
  }
}

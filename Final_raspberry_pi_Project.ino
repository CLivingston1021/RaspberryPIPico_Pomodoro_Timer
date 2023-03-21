//Christopher Livingston
//03/10/23
//sd247 final raspberry pi pico project
//making a pomodoro timer


#include <LiquidCrystal_I2C.h>

#define buttonPin 16
#define buzzerPin 15
const int workTime = 25 * 60; // 25 minutes
const int breakTime = 5 * 60; // 5 minutes

int buttonState = 0;
int prevState = 0;
unsigned long startTime = 0;
bool isBreak = false;
bool isTimerRunning = false;

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

 lcd.init();
  lcd.backlight();
  lcd.print("Press button to");
  lcd.setCursor(0, 1);
  lcd.print("start Pomodoro");
  delay(5000);
  lcd.clear();
  

  startTime = millis();
}
//Reading button input to start and stop timer
void loop() {
  
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && prevState == HIGH) {
    isTimerRunning = !isTimerRunning;
    if (isTimerRunning) {
      startTime = millis();
    }
    while (digitalRead(buttonPin) == LOW) {
      delay(20);
    }
  }
  prevState = buttonState;
  //to make active buzzer go off when remaining time hits 0 
  if (isTimerRunning) {
    int elapsedTime = (millis() - startTime) / 1000;
    int remainingTime = (isBreak ? breakTime : workTime) - elapsedTime;

    if (remainingTime <= 0) {
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      isBreak = !isBreak;
      startTime = millis();
    }
      //correct format for putting time to display onto lcd 
    int remainingMins = remainingTime / 60;
    int remainingSecs = remainingTime % 60;

    lcd.setCursor(0, 0);
    if (isBreak) {
      lcd.print("Break: ");
    } else {
      lcd.print("Work:  ");
    }
    lcd.setCursor(0, 1);
    if (remainingMins < 10) {
      lcd.print("0");
    }
    lcd.print(remainingMins);
    lcd.print(":");
    if (remainingSecs < 10) {
      lcd.print("0");
    }
    lcd.print(remainingSecs);
  }
  delay(200);
}


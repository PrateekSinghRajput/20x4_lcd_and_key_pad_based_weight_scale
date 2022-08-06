#include <HX711_ADC.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C library
HX711_ADC LoadCell(12, 13); // parameters: dt pin, sck pin
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int led = 11;
int taree = 10;
int a = 0;
long b = 0;
int c = 0;
int Num1,Num2,Number;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode (taree, INPUT_PULLUP);
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(1000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(103); // calibration factor for load cell => strongly dependent on your individual setup
  lcd.init(); // begins connection to the LCD module
  lcd.backlight(); // turns on the backlight
}
void loop() {
 char key = keypad.getKey();
  if ((key)&&(c<4))
  { 
 if (key == '1') //If Button 1 is pressed
    { 
    if (Number==0)
        Number=1;
    else
      Number = (Number*10) + 1; //Pressed twice
    }
if (key == '2') //Button 2 is Pressed
    { 
     if (Number==0)
       Number=2;
    else
       Number = (Number*10) + 2; //Pressed twice
    }
 if (key == '3')
    { 
     if (Number==0)
        Number=3;
    else
        Number = (Number*10) + 3; //Pressed twice
    }    
if (key == '4') //If Button 4 is pressed
    { 
    if (Number==0)
        Number=4;
    else
      Number = (Number*10) + 4; //Pressed twice
    }
if (key == '5')
    { 
     if (Number==0)
      Number=5;
    else
      Number = (Number*10) + 5; //Pressed twice
    }
 if (key == '6')
    {
    if (Number==0)
       Number=6;
    else
      Number = (Number*10) + 6; //Pressed twice
    }     
 if (key == '7') //If Button 7 is pressed
    { 
    if (Number==0)
      Number=7;
    else
      Number = (Number*10) + 7; //Pressed twice
    } 
if (key == '8')
    { 
     if (Number==0)
       Number=8;
    else
       Number = (Number*10) + 8; //Pressed twice
    }   
if (key == '9')
    {
    if (Number==0)
      Number=9;
    else
      Number = (Number*10) + 9; //Pressed twice
    }
 if (key == '0')
    {
    if (Number==0)
    {
       Number=0;
       c = c - 1;
    }
    else
       Number = (Number*10) + 0; //Pressed twice
    } 
      c = c + 1;
}
    if (key=='*') //If cancel Button is pressed
    {
     Number=0;
     c = 0;
    lcd.setCursor(15, 1); // set cursor to first row
    lcd.print("0    ");
    }
  LoadCell.update(); // retrieves data from the load cell
  float i = LoadCell.getData(); // get output value
    lcd.setCursor(15, 1); // set cursor to first row
  lcd.print(Number);   // Price that we entered 
  delay(1);
    lcd.setCursor(2, 3); // set cursor to first row
  lcd.print("Price = ");
b = (i* Number/1000); 
if(b<0)
{
  b=0; 
}
  lcd.setCursor(10, 3); // set cursor to secon row
  lcd.print(b, 1);   // total price
  lcd.print("   ");
  lcd.setCursor(0, 0); // set cursor to first row
  lcd.print("   Digital Scale "); // print out to LCD
lcd.setCursor(0, 1); // set cursor to first row
  lcd.print("Price per KG = ");
 float k = i/1000;
  lcd.setCursor(10, 2); // set cursor to secon row
  lcd.print(k, 3); // print out the retrieved value to the second row
  lcd.print(" KG ");
    lcd.setCursor(1, 2); // set cursor to secon row
  lcd.print("Weight = ");
  if (k>=20)
  {
    digitalWrite(led, HIGH);
   lcd.setCursor(1, 2); // set cursor to secon row
  lcd.print("Over Loaded   "); 
  delay(100);
  }
  digitalWrite(led, LOW);
  if (key=='#')
  {
    digitalWrite(led, HIGH);
    lcd.setCursor(0, 2); // set cursor to secon row
    lcd.print("   Taring...        ");
    LoadCell.start(1000);
  }
}

// 
// PID_TUNER
// 
// This Tuner is designed for 4 control terms
// but can be adjusted by using NUM_TERMS
//

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>

#define NUM_TERMS 4 // terms used
#define DECIMAL 3 // decimal places to show

#define STOP_BUTTON 2
#define UPDATE_BUTTON 3
#define SAVE_BUTTON 15
#define MENU_BUTTON 0
#define SELECT_BUTTON 0
#define GAIN_BUTTON 0
#define VALUE_POT 14
#define POT_PIN 0

LiquidCrystal lcd(19,18,17,16,4,5);
char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};

byte rowPins[4] = {9,8,7,6};
byte colPins[3] = {12,11,10};
Keypad KEYS = Keypad(makeKeymap(keys),rowPins,colPins,4,3);

byte save_temp[16];
unsigned int term[NUM_TERMS];
unsigned int new_read,hold_read;
byte select = 0;

bool display_switch = LOW;
bool switched = LOW;

void setup(){
  lcd.begin(16,2);
  Serial.begin(115200);
  lcd_welcome();
  delay(3000);
}

void loop(){
  char key = KEYS.getKey();

  if(key != NO_KEY){
    switch (key){
      case '1': // STOP!
        Serial.write(0x00);
        Serial.write(0x00);
        break;
  
      case '2': // Update
        Serial.write(0xff);
        Serial.write(0x04);
        for(int i=0; i<NUM_TERMS; i++){
          Serial.write(term[i]);
          Serial.write(term[i] >> 8);
        }
        Serial.write(0xff);
        break;
  
      case '3': // Save controller, Delete controller
        // Uno supports 1Kb::: 2 bytes val, 1 byte description
        //   1 byte inter-break, 1 byte full break
        //   == 16 bytes/save
        // Save to EEPROM if !display_switch, else Delete from EEPROM
        // EEPROM.update(address, val);
        // EEPROM.write(address, val);
        // EEPROM.read(address);
        // if(address == EEPROM.length()) address = 0;
        break;
  
      case '4': // Change display
        display_switch = ~display_switch;
        break;
  
      case '5': // Shift between terms, or saved controllers
        if(display_switch){
          // Shift Saved Controllers
        }
        else{
          // Toggle between Control Terms
        }
        break;
  
      case '6':
        hold_read = analogRead(POT_PIN);
        break;
  
      case '7':
        // cycle Gain control
        break;

      case '8':
        // set new controller
        break;
               
      default:
        // check display for lcd update
        // Serial.write(0x01);
        break;
    }
  }
  new_read = analogRead(POT_PIN);
  if(!display_switch && !(hold_read==new_read)){
    if(select==1){}
    else if(select==2){}
    else if(select==3){}
    else if(select==4){}
  }
}

void printTerms(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("P1= ");
  lcd.print(term[0],DECIMAL);
  lcd.setCursor(8,0);
  lcd.print("P2= ");
  lcd.print(term[1],DECIMAL);
  lcd.setCursor(0,1);
  lcd.print("D1= ");
  lcd.print(term[2],DECIMAL);
  lcd.setCursor(8,1);
  lcd.print("D2= ");
  lcd.print(term[3],DECIMAL);
}

void lcd_welcome(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   PID TUNER");
  lcd.setCursor(0,1);
  lcd.print("  Version 2.0");
}

void dostuff(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("pressed");
  switched = !switched;
  //delay(2000);
  //lcd.clear();
  //delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   PID TUNER");
  lcd.setCursor(0,1);
  lcd.print("  Version 1.0");
  while(1){}
  while(1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print((long)analogRead(14));
    delay(100);
  }
  /*if(switched){
    // Useful LCD functions
    // lcd.clear(); // clears display
    // lcd.display(); // turns on display
    lcd.setCursor(15,1); // bottom right
    lcd.write('C'); // write's single char
    lcd.setCursor(0,0); // top left
    lcd.print("don't you.."); // write's multiple char's
    //lcd.noDisplay(); // turns off display
    delay(100);
  }*/
}


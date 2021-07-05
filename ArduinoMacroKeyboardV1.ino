
#include <Keypad.h>
#include "HID-Project.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

//Encoder1
#define outputA1 A1
#define outputB1 A0
int counter1 = 0; 
int aState1;
int aLastState1;  

//Encoder2
#define outputA2 A3
#define outputB2 A2
int counter2 = 0; 
int aState2;
int aLastState2; 

//Encoder3
#define outputA3 8
#define outputB3 9
int counter3 = 0; 
int aState3;
int aLastState3; 
int counter=0;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* const Profiles[][4]= {
  {"Run\t" , "RunSpec\t" , "Inst\t" , "Prnt"},
  {"Add\t" , "Wire\t" , "NC\t" , "Rotate"},
  {"Copy\t" , "Cut\t" , "Paste\t" , "Snip"},
  {"Play\t" , "Move\t" , "Measure\t" , "Save"}
};

int profile_index=0;//To select profile
const byte ROWS = 4; //rows
const byte COLS = 4; //columns

char keys[ROWS][COLS] ={{'1','2','3','4'},
{'9','0','a','b'},
{'g','h','i','j'},
{'o','p','q','r'},
};
    
byte rowPins[ROWS] = {4,5,6,7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,16,14,15}; //connect to the column pinouts of the keypad
    
//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
    
void setup(){
   Serial.begin(9600);
   Keyboard.begin();
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  //Encoder1
  pinMode (outputA1,INPUT);
  pinMode (outputB1,INPUT);
  aLastState1 = digitalRead(outputA1); 

  //Encoder2
  pinMode (outputA2,INPUT);
  pinMode (outputB2,INPUT);
  aLastState2 = digitalRead(outputA2); 

  //Encoder3
  pinMode (outputA3,INPUT);
  pinMode (outputB3,INPUT);
  aLastState3 = digitalRead(outputA3); 
  
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++){
      display.print(Profiles[i][j]);
    }
    display.println();
    display.display();
  }
  display.display();
}
      
void loop(){
  //Encoder1
aState1 = digitalRead(outputA1); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState1 != aLastState1){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB1) != aState1) { 
       Consumer.write(MEDIA_VOL_UP);
     } else {
       Consumer.write(MEDIA_VOL_DOWN);
     }
   } 
   aLastState1 = aState1; // Updates the previous state of the outputA with the current state

     //Encoder2
aState2 = digitalRead(outputA2); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState2 != aLastState2){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB2) != aState2) { 
       Consumer.write(CONSUMER_BRIGHTNESS_UP);
     } else {
       Consumer.write(CONSUMER_BRIGHTNESS_DOWN);
     }
   } 
   aLastState2 = aState2; // Updates the previous state of the outputA with the current state

   //Encoder3
aState3 = digitalRead(outputA3); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState3 != aLastState3){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB3) != aState3) { 
      counter++;
      if(counter%2==0){
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press('z');
       Keyboard.releaseAll();
      }
     } else {
       counter--;
      if(counter%2==0){
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press('Z');
       Keyboard.releaseAll();
      }
     }
   } 
   aLastState3 = aState3; // Updates the previous state of the outputA with the current state
char key = keypad.getKey();// Read the key  
if(key=='1'){ 
Keyboard.press(KEY_LEFT_ALT); 
Keyboard.press(KEY_LEFT_SHIFT); 
Keyboard.press(KEY_F10); 
Keyboard.releaseAll();
}
if(key=='2'){ 
Keyboard.press(KEY_LEFT_CTRL);   
Keyboard.press(KEY_LEFT_SHIFT); 
Keyboard.press(KEY_F10); 
Keyboard.releaseAll();
}
if(key=='3'){ 
Keyboard.press(KEY_LEFT_ALT); 
Keyboard.press(KEY_INSERT); 
Keyboard.releaseAll();
}
if(key=='4'){ 
Keyboard.print("System.out.println();"); 
Keyboard.releaseAll();
}
if(key=='9'){ 
Keyboard.press('A'); 
Keyboard.releaseAll();
}
if(key=='0'){ 
Keyboard.press('W'); 
Keyboard.releaseAll();
}
if(key=='a'){ 
Keyboard.press('Q'); 
Keyboard.releaseAll();
}
if(key=='b'){ 
Keyboard.press('R'); 
Keyboard.releaseAll();
}
if(key=='g'){ 
Keyboard.press(KEY_LEFT_CTRL); 
Keyboard.press('C'); 
Keyboard.releaseAll();
}
if(key=='h'){ 
Keyboard.press(KEY_LEFT_CTRL); 
Keyboard.press('X'); 
Keyboard.releaseAll();
}
if(key=='i'){ 
Keyboard.press(KEY_LEFT_CTRL); 
Keyboard.press('V'); 
Keyboard.releaseAll();
}
if(key=='j'){ 
Keyboard.press(KEY_LEFT_GUI); 
Keyboard.press(KEY_LEFT_SHIFT); 
Keyboard.press('S'); 
Keyboard.releaseAll();
}
if(key=='o'){ 
Consumer.press(MEDIA_PLAY_PAUSE); 
Consumer.releaseAll();
}
if(key=='p'){ 
Keyboard.press('M'); 
Keyboard.releaseAll();
}
if(key=='q'){ 
Keyboard.press(KEY_LEFT_CTRL); 
Keyboard.press(KEY_LEFT_SHIFT); 
Keyboard.press('M'); 
Keyboard.releaseAll();
}
if(key=='r'){ 
Keyboard.press(KEY_LEFT_CTRL); 
Keyboard.press('S'); 
Keyboard.releaseAll();
}
}

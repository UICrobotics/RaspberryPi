//Made by Brendon Brown
//Last updated March 11th, 2019
//This code takes the serial data it has received from the xbee and performs actions accordingly
//Pins 5 and 6 have PWM frequency of ~980 Hz and the rest ~490 Hz
//NOTE: the pins I have used and the actions of the robot will change depending on need
//this code expects the robot to be expecting RC/servo signals to work. [Most motor controllers accept this as an input]

//This code needs to be updated and can be improved drastically 
//This code will have to be changed every year as long as the robot is changed/updated
//Remember to hook up the circuit correctly and to have a common ground on almost all circuits used in the robot

#include <Servo.h>
//note when using the servo library the frequency is not important because the way servo signals work, be sure to understand why this is...
int COUNTER = 3;
int timer[2] = {0,0};

Servo leftmotor;
Servo rightmotor;
int armupper0 = 13;
int armupper1 = 12;
int armlower0 = 7;
int armlower1 = 6;
Servo armbase;
char controlinput;      //This is where the serial input data gets put
char lastright = '1';   //Records the last left motor input
char lastleft = '0';    //Records the last right motor input
int variableleft;       //This variable is for the value of the left motor 
int variableright;      //This variable is for the value of the right motor 
int armbasepos = 90;    //This variable is for the value of the base of the arm
int countl = 0;         //The counter here needs to be updated for future applications so its more accurate but right now its a simple solution for lost of signal from the source
int countr = 0;
char armstatel = 'X';   //Records the last state of the lower arm (This actually might not be needed)
char armstateu = 'Y';   //Records the last state of the upper arm (This actually might not be needed)


void setup() {
  leftmotor.attach(9);
  rightmotor.attach(10);
  armbase.attach(11);
  pinMode(armupper0, OUTPUT);
  pinMode(armupper1, OUTPUT);
  pinMode(armlower0, OUTPUT);
  pinMode(armlower1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Testing phase of the code
  Serial.print("Values-C-L-R-VL-VR-T0-T1:");
//  Serial.print(controlinput);
//  Serial.print(" ");
//  Serial.print(lastleft);
//  Serial.print(" ");
//  Serial.print(lastright);
//  Serial.print(" ");
  Serial.print(variableleft);
  Serial.print(" ");
  Serial.print(variableright);
  Serial.print(" ");
  Serial.print(timer[0]);
  Serial.print(" ");
  Serial.print(timer[1]);
  Serial.print(" ");
  Serial.print("\n");
  //only update when there is serialdata incoming
  if(Serial.available()>0){ 
    controlinput = Serial.read();
    
    //This is for the motor control
    if(controlinput == '0'){
      lastleft = '0';
      countl = 0;
    }
    else if(controlinput == '1'){
      lastright = '1';
      countr = 0;
    }
    else if(controlinput == '2'){
      lastleft = '2';
      countl = 0;
    }
    else if(controlinput == '3'){
      lastright= '3';
      countr = 0;
    }
    else if(controlinput == '4'){
      lastleft = '4';
      countl = 0;
    }
    else if(controlinput == '5'){
      lastright= '5';
      countr = 0;
    }
    else if(controlinput == '6'){
      lastleft = '6';
      countl = 0;
    }
    else if(controlinput == '7'){
      lastright= '7';
      countr = 0;
    }
    else if(controlinput == '8'){
      lastleft = '8';
      countl = 0;
    }
    else if(controlinput == '9'){
      lastright= '9';
      countr = 0;
    }
    //This is for the arm base
    else if(controlinput == 'A'){
      if(armbasepos < 180){
        armbasepos = armbasepos + 10;
      }
    }
    else if(controlinput == 'B'){
      if(armbasepos > 0){
        armbasepos = armbasepos - 10;
      }
    }
    //This segment of code is for the arm which was controlled with relays and actuactors be sure 
    else if(controlinput == 'X'){
      armstatel = 'X';
      digitalWrite(armlower0, LOW);
      digitalWrite(armlower1, LOW);
    }
    else if(controlinput == 'Y'){
      armstateu = 'Y';
      digitalWrite(armupper0, LOW);
      digitalWrite(armupper1, LOW);
    }
    else if(controlinput == 'L'){
      armstatel = 'L';
      digitalWrite(armlower0, HIGH);
      digitalWrite(armlower1, LOW);
    }
    else if(controlinput == 'R'){
      armstatel = 'R';
      digitalWrite(armlower0, LOW);
      digitalWrite(armlower1, HIGH);
    }
    else if(controlinput == 'U'){
      armstateu = 'U';
      digitalWrite(armupper0, HIGH);
      digitalWrite(armupper1, LOW);
    }
    else if(controlinput == 'D'){
      armstateu = 'D';
      digitalWrite(armupper0, LOW);
      digitalWrite(armupper1, HIGH);
    }
  } 
  
  if(armstatel == 'X'){
    digitalWrite(armlower0, LOW);
    digitalWrite(armlower1, LOW);
  }
  if(armstateu == 'Y'){
    digitalWrite(armupper0, LOW);
    digitalWrite(armupper1, LOW);
  }
  //The variables and the limits on them need to be adjusted for each motor controller as they might be too fast or the signal you are sending is just out of range of acceptable input
  //for the motor controller we used the center servo signal wasn't 90 and I had to guess until I found it which ended up being around 95
  //some motor controllers are programmable so this process of guess and check isn't necessary
  if(lastleft == '0'){
    variableleft = 95;
  }
  else if(lastleft == '2' && timer[0]==0){
      timer[0]++;
      if(variableleft < 120){
        variableleft++;
      }
      else if(variableleft > 120){
        variableleft--;
      }
  }
  else if(lastleft == '4' && timer[0]==0){
      timer[0]++;
      if(variableleft > 60){
        variableleft--;
      }
      else if(variableleft < 60){
        variableleft++;
      }
  }
  else if(lastleft == '6' && timer[0]==0){
      timer[0]++;
      if(variableleft < 150){
        variableleft++;
      }
      else if(variableleft > 150){
        variableleft--;
      }
  }
  else if(lastleft == '8' && timer[0]==0){
      timer[0]++;
      if(variableleft > 30){
        variableleft--;
      }
      else if(variableleft < 30){
        variableleft++;
      }
  }
  else{
    if(timer[0]>=COUNTER){
      timer[0] = 0;
    }
    else{
      timer[0]++;
    }
  }

  if(lastright == '1'){
    variableright = 95;
  }
  else if(lastright == '3' && timer[1]==0){
      timer[1]++;
      if(variableright < 120){
        variableright++;
      }
      else if(variableright > 120){
        variableright--;
      }
  }
  else if(lastright == '5' && timer[1]==0){
      timer[1]++;
      if(variableright > 60){
        variableright--;
      }
      else if(variableright < 60){
        variableright++;
      }
  }
  else if(lastright == '7' && timer[1]==0){
      timer[1]++;
      if(variableright < 150){
        variableright++;
      }
      else if(variableright > 150){
        variableright--;
      }  
  }
  else if(lastright == '9' && timer[1]==0){
      timer[1]++;
      if(variableright > 30){
        variableright--;
      }
      else if(variableright < 30){
        variableright++;
      }
  }
  else{
    if(timer[1]>=COUNTER){
      timer[1]=0;
    }
    else{
      timer[1]++;
    }
  }
  
  //after serial data was read update all appropriate motors/servos/relays  
  leftmotor.write(variableleft);
  rightmotor.write(variableright);
  armbase.write(armbasepos);
  
//  if(timer >=COUNTER){
//    timer=0;
//  }
//  else{
//    timer++;
//  }

  //Need to implement change based on time conditions are meet
  //Issue: by the time code is updated, change to previous values have been made
  //fix: need to intrduce currVal and lastVal that will keep track of changes(on my own time)
  //fix2: add counter to section of code where motor speed is changed
  //!!!!fix3: add counter to left and right wheel, only updates after every nth loop!!!!

  //This count is just a very unprofessional way to make the robot stop if it hasn't recieved input from the controller after so many clock cycles [safety check]
//  countl++;
//  countr++;
//  if(countl >= 5000){
//    lastleft = '0';
//  }
//  if(countr >= 5000){
//    lastright = '1';
//  }
}

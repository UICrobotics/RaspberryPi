char controlinput;
int LED1 = 11; // was 13
int LED_green = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED_green, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){
     digitalWrite(LED_green, HIGH);
    //delay(10);
    controlinput = Serial.read();
    Serial.println(controlinput);
  }

  if(controlinput == 'A'){
//    Serial.println("A was registered");
    digitalWrite(LED1, HIGH);
  }
  else if(controlinput == 'B'){
//    Serial.println("B was registered");
    digitalWrite(LED1, LOW);  
  }
  //Serial.println(controlinput);
}

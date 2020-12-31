//Solenoid Off
int enA = 13;
const int in1  = 12;  // Pin 14 of L293
const int in2  = 11;  // Pin 10 of L293

//Solenoid On
int enB = 8;
const int in3  = 10; // Pin  7 of L293
const int in4  = 9;  // Pin  2 of L293

//Sensors
int sen1 = 7;
int sen2 = 6;
int has_Sensed = 0;

//E-Stop
byte interruptPin = 3;
int STOPPED = 0;

void setup(){
  //Set pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  Serial.begin(9600); //Debug
  

  backward();

  int valL = digitalRead(sen1);

    if (valL == HIGH){
        delay(100);
        forward();
    }

  delay(10000);
  backward();

  //E-stop Settings
  attachInterrupt(digitalPinToInterrupt(interruptPin), stop, HIGH);
} 
  
void loop(){
  while (STOPPED == 0){
  
    int valL = digitalRead(sen1);  
    int valR = digitalRead(sen2);

    while(has_Sensed == 0){ 
      int valR = digitalRead(sen2);
    
      if (valR == HIGH){
        has_Sensed = 1;
        Serial.println(has_Sensed); //Debug
        break;
      }

    }

    delay(100);
    off();
  
    if (valL == HIGH){
        if (has_Sensed == 1){
          delay(500);
          forward();
          has_Sensed = 0;
          Serial.println(has_Sensed); //Debug
        }
    }
    delay(10000);
    backward();
  }
}

void forward(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, 0);
    analogWrite(enB, 255);
}

void backward (){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, 255);
    analogWrite(enB, 0);
}

void off (){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, 0);
    analogWrite(enB, 0);
}

void stop(){
  backward();
  STOPPED = 1;
  Serial.println(STOPPED);

  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

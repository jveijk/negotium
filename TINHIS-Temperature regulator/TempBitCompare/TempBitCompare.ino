int accuracy = 196;                               // the amount of takes the program will do before deeming the measurement accurate enough
unsigned long tempBitVal = 0;
unsigned long potBitVal = 0;                      
float degCelsius;                                   //placeholder for the unit of measurement
int setDegCelsius;
int state;                                        //State of program control, 0 = off, 1 = on
int statePin = 4;
int degLowest = 0;                                //Highest and lowest degrees settable by potmeter
int degHighest = 30;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);                             //temperature sensor
  pinMode(A5, INPUT);                             //potentiometer
  pinMode(statePin, OUTPUT);
}

void loop() {
  
  for(int i = 0; i<accuracy; i++){                //for loop for preferred amount of takes, influenced by "accuracy" 
    tempBitVal += analogRead(A0);
    potBitVal += analogRead(A5);
    delay(1);
  }
  
  tempBitVal = tempBitVal/accuracy;               //Processing stack
  potBitVal = 1023 - (potBitVal/accuracy);                 //Dividing by takes to retrieve original value
  degCelsius = ((tempBitVal - 790.85)/-11.1);     //Using our formula to turn a measured voltage into degrees Celsius, our unit of measurement
  setDegCelsius = ((potBitVal - 790.85)/-11.1);
  setDegCelsius = map(potBitVal, 0, 1023, degLowest, degHighest);


  
  if(setDegCelsius > degCelsius){                     //Determining whether the system should turn on the heating
    state = 1;  
    digitalWrite(statePin, LOW);                  //For prototyping purposes the heating component(actuator) is substituted by an LED
    Serial.println("The system is heating");
  } else {
    state = 0;
    digitalWrite(statePin, HIGH);
    Serial.println("The system is not heating");
    
  }
  
  Serial.print("Celsius: ");                      //Print stack
  Serial.print(degCelsius);
  Serial.print(" Bit value: ");
  Serial.println(tempBitVal);
  Serial.print("Pot bit value: ");
  Serial.print(potBitVal);
  Serial.print(" Celsius set: ");
  Serial.println(setDegCelsius);

  tempBitVal = 0;                                  //Reset stack
  potBitVal = 0;
  
}

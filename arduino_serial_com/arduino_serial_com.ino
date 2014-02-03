int incomingByte = 0;
int motorPin = 6;
 
void setup(){
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}
 
void loop(){
 
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
   
    // say what you got:
    if(incomingByte == '1') { // ASCII printable characters: 49 means number 1
      digitalWrite(motorPin, HIGH);
    } else if(incomingByte == '0') { // ASCII printable characters: 48 means number 0
      digitalWrite(motorPin, LOW);
    }
  }
}

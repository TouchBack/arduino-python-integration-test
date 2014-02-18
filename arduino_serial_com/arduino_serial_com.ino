char incomingByte;
int motorPin = 9;
int redPin = 6;
int greenPin = 5;
int bluePin = 3;
String floryan_string = "";
boolean started = false;
boolean ended = false;
int red = 0;
int green = 0;
int blue = 0;
int motor = 0;

void parse_floryan(String floryan)
{
  Serial.println(floryan);
  int i = 0;
  for(i = 0; i < floryan.length(); i ++)
  {
    if (floryan.charAt(i) == 'r')
    {
      String red_str = "";
      int j = i+2;
      for (j; j < floryan.length(); j++)
      {
        if (j == ',')
        {
          break;
        }
        else
        {
          red_str += floryan.charAt(j);
        }
      }
      char red_c[red_str.length()];
      red_str.toCharArray(red_c, red_str.length());
      red = atoi(red_c);
    }
    
    if (floryan.charAt(i) == 'g')
    {
      String green_str = "";
      int j = i+2;
      for (j; j < floryan.length(); j++)
      {
        if (j == ',')
        {
          break;
        }
        else
        {
          green_str += floryan.charAt(j);
        }
      }
      
      char green_c[green_str.length()];
      green_str.toCharArray(green_c, green_str.length());
      green = atoi(green_c);
    }
    
    if (floryan.charAt(i) == 'b')
    {
      String blue_str = "";
      int j = i+2;
      for (j; j < floryan.length(); j++)
      {
        if (j == ',')
        {
          break;
        }
        else
        {
          blue_str += floryan.charAt(j);
        }
      }
      
      char blue_c[blue_str.length()];
      blue_str.toCharArray(blue_c, blue_str.length());
      blue = atoi(blue_c);
    }
    
    if (floryan.charAt(i) == 'm')
    {
      String motor_str = "";
      int j = i+2;
      for (j; j < floryan.length(); j++)
      {
        if (j == ',')
        {
          break;
        }
        else
        {
          motor_str += floryan.charAt(j);
        }
      }
      
      char motor_c[motor_str.length()];
      motor_str.toCharArray(motor_c, motor_str.length());
      motor = atoi(motor_c);
    }   
  }
}

void send_signals(int red, int green, int blue, int motor)
{
  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);
  motor = constrain(motor, 0, 255);
  
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  analogWrite(motorPin, motor);
  Serial.println(red);  
  Serial.println(green);  
  Serial.println(blue);  
  Serial.println(motor);  
  
}
 
void setup(){
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
 
void loop(){
  // if there is something to read
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    
    //if {, then start reading FLORYAN
    if (incomingByte == '{')
    {
      started = true;
      floryan_string = "{";
    }   
    //if {, then end reading FLORYAN
    else if (incomingByte == '}')
    {
      ended = true;
      floryan_string += "}";
    }
    //if we have started reading, but not ended, append byte to string
    if (started && !ended)
    {
      floryan_string += incomingByte;
    }
    //if started and ended, then parse the string
    else if (started && ended)
    {
      started = false;
      ended = false;
      
      parse_floryan(floryan_string);
      send_signals(red, green, blue, motor);
    }
  }
}

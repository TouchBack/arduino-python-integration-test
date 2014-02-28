char incomingByte;
int motorPin = 9;
int redPin = 6;
int greenPin = 5;
int bluePin = 3;
int count = 0;
int counter = 0;
char floryan_string[32];
boolean started = false;
boolean ended = false;
int red = 0;
int green = 0;
int blue = 0;
int motor = 0;
int i = 0;
char red_str[] = "000";
char blue_str[] = "000";
char green_str[] = "000";
char motor_str[] = "000";
int j = 0;

int availableMemory() {
  int size = 2048; // Use 2048 with ATmega328
  byte *buf;

  while ((buf = (byte *) malloc(--size)) == NULL)
    ;

  free(buf);

  return size;
}

void parse_floryan(char floryan[])
{
  i = 0;
  
  for(i = 0; i < count; i ++)
  {
    if (floryan[i] == 'r')
    {
      j = i+2;
      counter = 3;
      
      int k;
      for(k = 0; k < 3; k++)
      {
        red_str[k] = '0';
      }
      
      for (j; j < count; j++)
      {
        if (j == ',')
        {
          break;
        }
        else
        {
          red_str[counter-1] = floryan[j] ;
          counter--;
        }
      }
      
      if (counter == 1)
      {
        char tmp = red_str[2];
        red_str[2] = red_str[1];
        red_str[1] = tmp;
      }
      else if (counter == 0)
      {
        char tmp = red_str[2];
        red_str[2] = red_str[0];
        red_str[0] = tmp;
      }
      
      red = atoi(red_str);
    }
    
    if (floryan[i] == 'g')
    {
      j = i+2;
      counter = 3;
      
      int k;
      for(k = 0; k < 3; k++)
      {
        green_str[k] = '0';
      }
      
      for (j; j < count; j++)
      {
        if (j == ',')
        {
          break;
        }
        else
        {
          green_str[counter-1] = floryan[j] ;
          counter--;
        }
      }
      
      if (counter == 1)
      {
        char tmp = green_str[2];
        green_str[2] = green_str[1];
        green_str[1] = tmp;
      }
      else if (counter == 0)
      {
        char tmp = green_str[2];
        green_str[2] = green_str[0];
        green_str[0] = tmp;
      }
      
      green = atoi(green_str);
    }
    
    if (floryan[i] == 'b')
    {
      j = i+2;
      counter = 3;
      
      int k;
      for(k = 0; k < 3; k++)
      {
        blue_str[k] = '0';
      }
      
      for (j; j < count; j++)
      {
        if (j == ',' || j == '}')
        {
          break;
        }
        else
        {
          blue_str[counter-1] = floryan[j] ;
          counter--;
        }
      }
      
      if (counter == 1)
      {
        char tmp = blue_str[2];
        blue_str[2] = blue_str[1];
        blue_str[1] = tmp;
      }
      else if (counter == 0)
      {
        char tmp = blue_str[2];
        blue_str[2] = blue_str[0];
        blue_str[0] = tmp;
      }
      
      blue = atoi(blue_str);
    }
    
    if (floryan[i] == 'm')
    {
      j = i+2;
      counter = 3;
      
      int k;
      for(k = 0; k < 3; k++)
      {
        motor_str[k] = '0';
      }
      
      for (j; j < count; j++)
      {
        if (j == ',')
        {
          break;
        }
        else
        {
          motor_str[counter-1] = floryan[j];
          counter--;
        }
      }
      
      if (counter == 1)
      {
        char tmp = motor_str[2];
        motor_str[2] = motor_str[1];
        motor_str[1] = tmp;
      }
      else if (counter == 0)
      {
        char tmp = motor_str[2];
        motor_str[2] = motor_str[0];
        motor_str[0] = tmp;
      }
      
      
      motor = atoi(motor_str);
    }   
  }
  
  count = 0;
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
//  Serial.println(availableMemory());
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    
    //if {, then start reading FLORYAN
    if (incomingByte == '{')
    {
      started = true;
      count = 0;
    }   
    //if {, then end reading FLORYAN
    else if (incomingByte == '}')
    {
      ended = true;
      floryan_string[count] = '}';
      count +=1;
    }
    //if we have started reading, but not ended, append byte to string
    if (started && !ended)
    {
      floryan_string[count] = incomingByte;
      count += 1;
    }
    //if started and ended, then parse the string
    else if (started && ended || count == 32)
    {
      started = false;
      ended = false;
      int a = 0;
      for(a; a < count; a++)
      {
         Serial.print(floryan_string[a]); 
      }
      Serial.println();
      parse_floryan(floryan_string);
      send_signals(red, green, blue, motor);
    }
  }
}

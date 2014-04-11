char incomingByte;

int motor2Pin = 10;
int motor1Pin = 9;
int redPin = 6;
int greenPin = 5;
int bluePin = 3;
int count = 0;
int counter = 0;
int MAXSIZE = 64;
char floryan_string[64];
boolean started = false;
boolean ended = false;
int red = 0;
int green = 0;
int blue = 0;
int motor1 = 0;
int motor2 = 0;
int i = 0;
char red_str[] = "000";
char blue_str[] = "000";
char green_str[] = "000";
char motor1_str[] = "000";
char motor2_str[] = "000";
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
    Serial.println("Enter Floryan");
    for(i = 0; i < count; i ++)
    {
        if (floryan[i] == 'r')
        {
            j = i+2;
            counter = 0;
            
            int k;
            for(k = 0; k < 3; k++)
            {
                red_str[k] = '0';
            }
            
            for (j; j < count; j++)
            {
                if (j == ',' || j == '}')
                {
                    break;
                }
                else
                {
                    red_str[counter] = floryan[j] ;
                    counter++;
                }
            }
            
            if (counter == 1)
            {
                char tmp = red_str[0];
                red_str[0] = '0';
                red_str[2] = tmp;
            }      
            else if (counter == 2)
            {
                char tmp1 = red_str[0];
                char tmp2 = red_str[1];
                red_str[0] = '0';
                red_str[1] = tmp1;
                red_str[2] = tmp2;
            }      
            red = atoi(red_str);
        }
        
        if (floryan[i] == 'g')
        {
            j = i+2;
            counter = 0;
            
            int k;
            for(k = 0; k < 3; k++)
            {
                green_str[k] = '0';
            }
            
            for (j; j < count; j++)
            {
                if (j == ',' || j == '}')
                {
                    break;
                }
                else
                {
                    green_str[counter] = floryan[j] ;
                    counter++;
                }
            }
            
            if (counter == 1)
            {
                char tmp = green_str[0];
                green_str[0] = '0';
                green_str[2] = tmp;
            }      
            else if (counter == 2)
            {
                char tmp1 = green_str[0];
                char tmp2 = green_str[1];
                green_str[0] = '0';
                green_str[1] = tmp1;
                green_str[2] = tmp2;
            }      
            
            green = atoi(green_str);
        }
        
        if (floryan[i] == 'b')
        {
            j = i+2;
            counter = 0;
            
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
                    blue_str[counter] = floryan[j] ;
                    counter++;
                }
            }
            
            if (counter == 1)
            {
                char tmp = blue_str[0];
                blue_str[0] = '0';
                blue_str[2] = tmp;
            }      
            else if (counter == 2)
            {
                char tmp1 = blue_str[0];
                char tmp2 = blue_str[1];
                blue_str[0] = '0';
                blue_str[1] = tmp1;
                blue_str[2] = tmp2;
            }   
            
            blue = atoi(blue_str);
        }
        
        if (floryan[i] == 'm')
        {
//            if(floryan[i+1] == '1')
//            {
//                i = i+1;
                j = i+2;
                counter = 0;
                
                int k;
                for(k = 0; k < 3; k++)
                {
                    motor1_str[k] = '0';
                }
                
                for (j; j < count; j++)
                {
                    if (j == ',' || j == '}')
                    {
                        break;
                    }
                    else
                    {
                        motor1_str[counter] = floryan[j] ;
                        counter++;
                    }
                }
                
                if (counter == 1)
                {
                    char tmp = motor1_str[0];
                    motor1_str[0] = '0';
                    motor1_str[2] = tmp;
                }      
                else if (counter == 2)
                {
                    char tmp1 = motor1_str[0];
                    char tmp2 = motor1_str[1];
                    motor1_str[0] = '0';
                    motor1_str[1] = tmp1;
                    motor1_str[2] = tmp2;
                }      
                motor1 = atoi(motor1_str);
            }
            
            // begin m2 parse
            
//            else if (floryan[i+1] == '2')
            if (floryan[i] == 'n')
            { 
                Serial.print("found m2");
//                i = i+1;
                j = i+2;
                counter = 0;
                
                int k;
                for(k = 0; k < 3; k++)
                {
                    motor2_str[k] = '0';
                }
                
                for (j; j < count; j++)
                {
                    if (j == ',' || j == '}')
                    {
                        break;
                    }
                    else
                    {
                        motor2_str[counter] = floryan[j] ;
                        counter++;
                    }
                }
                
                if (counter == 1)
                {
                    char tmp = motor2_str[0];
                    motor2_str[0] = '0';
                    motor2_str[2] = tmp;
                }      
                else if (counter == 2)
                {
                    char tmp1 = motor2_str[0];
                    char tmp2 = motor2_str[1];
                    motor2_str[0] = '0';
                    motor2_str[1] = tmp1;
                    motor2_str[2] = tmp2;
                }      
                motor2 = atoi(motor2_str);
            }
            
//        }
        
        // end m2 parse
        
        
    }
    
    count = 0;
}


void send_signals(int red, int green, int blue, int motor1, int motor2)
{
    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 255);
    motor1 = constrain(motor1, 0, 255);
    motor2 = constrain(motor2, 0, 255);
    
    Serial.print("analog write");
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
    analogWrite(motor1Pin, motor1);
    analogWrite(motor2Pin, motor2);
    Serial.println(red);  
    Serial.println(green);  
    Serial.println(blue);  
    Serial.println(motor1);
    Serial.println(motor2);  
    
}

void setup(){
    Serial.begin(9600);
    pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void loop(){
    // if there is something to read
 // Serial.println(availableMemory());
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();
        delayMicroseconds(100);
        
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
        else if ((started && ended) || (count == (MAXSIZE-1)))
        {
            started = false;
            ended = false;
            Serial.println(count);
//      int a = 0;
//      for(a; a < count; a++)
//      {
//         Serial.print(floryan_string[a]); 
//      }
//      Serial.println();
            parse_floryan(floryan_string);
            send_signals(red, green, blue, motor1, motor2);
        }
    }
}

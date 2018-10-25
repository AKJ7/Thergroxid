/**
 * NEXT: WORKING ON CASE 2: ERROR MELDUNGEN/REPORTS AND INTERPOLATION
 */
boolean test = true;
boolean sensor_read = true;
boolean debug = false;
boolean button_new, button_old;
int count, pressed, error, warning, state;
int DHpin = A4;
byte dat[5];
const byte digit[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0}, //0
                           {0, 1, 1, 0, 0, 0, 0, 0}, 
                           {1, 1, 0, 1, 1, 0, 1, 0}, 
                           {1, 1, 1, 1, 0, 0, 1, 0}, 
                           {0, 1, 1, 0, 0, 1, 1, 0}, 
                           {1, 0, 1, 1, 0, 1, 1, 0}, 
                           {1, 0, 1, 1, 1, 1, 1, 0}, 
                           {1, 1, 1, 0, 0, 0, 0, 0}, 
                           {1, 1, 1, 1, 1, 1, 1, 0}, 
                           {1, 1, 1, 1, 0, 1, 1, 0} //9
                           };        
const byte symbol[3][7] = {{0, 1, 1, 0, 1, 1, 1}, // Humidity
                           {1, 1, 0, 0, 0, 1, 1}, // Degree 
                           {1, 1, 1, 0, 1, 1, 1}  // Air (Carbon Dioxyde)
                           //{1, 0, 0, 0, 1, 1, 1}, // Feuchtichkeit
                           //{1, 1, 0, 0, 0, 1, 1}, // Grad
                           //{0, 0, 0, 1, 1, 1, 0}  // Luft 
                           };
const byte letter[2][7] = {{1, 0, 0, 1, 1, 1, 1}, // E
                           {1, 1, 1, 0, 1, 1, 1}  // R
                           };
const byte color[8][3] = {{0, 0, 0},  // Empty
                          {0, 0, 1},  // Blue
                          {0, 1, 0},  // Red
                          {0, 1, 1},  // Purple
                          {1, 0, 0},  // Green
                          {1, 0, 1},  // Cyan
                          {1, 1, 0},  // Yellow
                          {1, 1, 1}   // White
                          };
const int led[8] = {9, 4, 3, 2, 6, 8, 7, 5};
const int ledPins[3] = {11, 12, 13};
unsigned long now, before, later;
float meas_val[3] = {0, 0, 0};
int to_disp_val[3] = {0, 0, 0};
char led_status[3] = {A1, A2, A3};

void Display(int var[3], int var_2){
  for (int j = 0; j < 4; j ++){
    if (j == 1){
        digitalWrite(led[7], HIGH);
      } else{
        digitalWrite(led[7], LOW);
      }
    digitalWrite(13-j, LOW);
    for (int i = 0; i < 7; i ++){
      if (j != 3){
        if (digit[var[j]][i] == 1){
          digitalWrite(led[i], HIGH); 
        } else{
          digitalWrite(led[i], LOW);
        }
      } else{
        if (symbol[var_2][i] == 1){
          digitalWrite(led[i], HIGH); 
        } else{
          digitalWrite(led[i], LOW);
        }
      }
    }
    delay(6);
    digitalWrite(13-j, HIGH);
  }
}
byte read_data(){
  byte data;
  for (int i = 0; i < 8; i ++){
    if (digitalRead (DHpin) == LOW){
      while (digitalRead (DHpin) == LOW); // wait for 50us;
      delayMicroseconds (30); // determine the duration of the high level to determine the data is '0 'or '1';
      if (digitalRead (DHpin) == HIGH)
        data |= (1 << (7-i)); // high front and low in the post;
      while (digitalRead (DHpin) == HIGH); // data '1 ', wait for the next one receiver;
      }
   }
  return data;
}
void start_test(){
  digitalWrite(DHpin, HIGH);
  delayMicroseconds(40); // Wait DHT11 response;
  pinMode (DHpin, INPUT);
  while(digitalRead(DHpin) == HIGH);
  delayMicroseconds (80); // DHT11 a response, pulled the bus 80us;
    if (digitalRead (DHpin) == LOW);
    delayMicroseconds (80); // DHT11 80us after the bus pulled to start sending data;
    for (int i = 0; i < 4; i ++) // receives temperature and humidity data, the parity bit is not considered;
  dat[i] = read_data();
  pinMode(DHpin, OUTPUT);
  digitalWrite (DHpin, HIGH); // sending data once after releasing the bus, wait for the host to open the next Start signal;
}
void LEDcolor(int var_1, int var_2, int var_3){
  int var_4;
  if (var_2 == 1){
    var_4 = 0;
  } else{
    if (var_3 == 0){
      if (var_1 == 0){
        var_4 = 5;
      } else if (var_1 == 1){
        var_4 = 3;
      } else{
        var_4 = 4;
      }   
    } else if (var_3 == 1){
      var_4 = 6;
    } else{
      var_4 = 2;
    }
  }
  for (int i = 0; i < 3; i++){
    if (color[var_4][i] == 1){
      digitalWrite(led_status[i], HIGH); 
    } else{
      digitalWrite(led_status[i], LOW);
    }
  }
}
void Warnings(void){
  switch(error){
    case 1:
    
    break;
  }
}

void setup() {
  if (debug)
    Serial.begin(9600);
  pinMode(DHpin, OUTPUT);
  pinMode(2, OUTPUT); //D
  pinMode(3, OUTPUT); //C
  pinMode(4, OUTPUT); //B
  pinMode(5, OUTPUT); //DOT
  pinMode(6, OUTPUT); //E
  pinMode(7, OUTPUT); //G
  pinMode(8, OUTPUT); //F
  pinMode(9, OUTPUT); //A
  pinMode(A0, INPUT); //Button
  pinMode(A1, OUTPUT); //LED Green
  pinMode(A2, OUTPUT); //LED Red
  pinMode(A3, OUTPUT); //LED Blue
  pinMode(A5, OUTPUT); //Air Quality Sensor
  pinMode(10, OUTPUT); //LED 4
  pinMode(11, OUTPUT); //LED 3
  pinMode(12, OUTPUT); //LED 2
  pinMode(13, OUTPUT); //LED 1
  
  for (int i = 10; i < 14; i ++){
    digitalWrite(i, HIGH); 
  }
}

void loop() {
  button_new = digitalRead(A0);
  if (button_new == HIGH){
    if (button_new != button_old){
      pressed = (pressed+1)%3;
    }
    count++;
    if (count == 100){
      state = (state + 1) % 2; 
    }
  } else{
    count = 0;
  }
  LEDcolor(pressed, state, warning);
  switch(state){
    case 1:
      for (int i = 10; i < 14; i ++){
        digitalWrite(i, HIGH);
      }
    break;
    case 2:
    
    break;
    default:
      float value = meas_val[pressed];
      to_disp_val[0] = int(value)/10;
      to_disp_val[1] = int(value)%10;
      to_disp_val[2] = int((value - int(value))*10);
      if (millis() - now > 2000 || test == true){
        digitalWrite(DHpin, LOW); // bus down, send start signal;
        sensor_read = true;
        now = millis();
      }
      Display(to_disp_val, pressed);
      if (sensor_read){
        start_test();
        meas_val[0] = dat[0] + dat[1] * 0.1;
        meas_val[1] = dat[2] + dat[3] * 0.1;
        meas_val[2] = analogRead(A6);
        if (meas_val[0] > 50 && meas_val[0] <= 80){
          warning = 1;
        } else if (meas_val[0] > 80){
          warning = 2;
        } else {
          warning = 0;
        }
      }
    break;
  }
  if (debug){
    Serial.print("Current humdity =");
    Serial.print(dat [0], DEC); // display the humidity-bit integer;
    Serial.print('.');
    Serial.print(dat [1], DEC); // display the humidity decimal places;
    Serial.println('%');
    Serial.print("Current temperature =");
    Serial.print(dat [2], DEC); // display the temperature of integer bits;
    Serial.print('.');
    Serial.print(dat [3], DEC); // display the temperature of decimal places;
    Serial.println('C');
  }
  test = false;
  sensor_read = false; 
  button_old = button_new;
}

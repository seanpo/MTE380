                                                                                                                                                                                                                                                                                                              #include <Ultrasonic.h>
#include <VirtualWire.h>

int left_in2 = 8;
int left_in3 = 9;

int right_in2 = 10;
int right_in3 = 11;

Ultrasonic Front_Ultrasonic(6, 7);
Ultrasonic Right_Ultrasonic(4,5);
Ultrasonic Back_Ultrasonic(2,3);

int Front_Distance;
int Left_Distance;
int Right_Distance;
int Back_Distance;
char *controller;
int once = 0;
void setup() {
  //pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  vw_set_ptt_inverted(true); //
  vw_setup(4000);// speed of data transfer Kbps
  vw_set_tx_pin(12);
  pinMode(right_in2, OUTPUT);
  pinMode(right_in3, OUTPUT);
  pinMode(left_in2, OUTPUT);
  pinMode(left_in3, OUTPUT);
}

void loop()
{
  drive_forward(255);
  sendforwardsignal();
  //findplatform();
//  delay(10000);
}

void go_up_ramp()
{
 drive_forward(255);
 delay(5000);  
 drive_stop(255);
}

void findplatform(){
 
 /* while (Back_Ultrasonic.Ranging(CM) > 3)
  {
    drive_reverse(255);
  } 
  */
  drive_stop(255);
  
  while (Front_Ultrasonic.Ranging(CM) > 3){
    drive_forward(155);
    delay(750);
    Right_Distance=Right_Ultrasonic.Ranging(CM);
    if (Right_Distance < 100)
      break;
    }
}


void drive_reverse(int s) {
  digitalWrite(left_in3, LOW);
  digitalWrite(right_in3, HIGH);
  int i;
  for (i = 0; i <s; i++)
  {
    analogWrite(right_in2, i);
    analogWrite(left_in2, i);
  }
  
}

void drive_forward(int s) {
  digitalWrite(left_in3, HIGH);
  digitalWrite(right_in3, LOW);
  int i;
  for (i = 0; i <s; i++)
  {
    analogWrite(right_in2, i);
    analogWrite(left_in2, i);  
  }  
}

void drive_stop(int s) {
  digitalWrite(left_in3, LOW);
  digitalWrite(right_in3, LOW);
  int i;
  for (i = s; i>=0; i--)
  {
    analogWrite(right_in2, i);
    analogWrite(left_in2, i);
  }  
}

void drive_right(int time)
{
  digitalWrite(left_in3, LOW);
  digitalWrite(right_in3, HIGH);
  int i;
  for (i = 0; i<255; i++)
  {
    analogWrite(right_in2, i);
    analogWrite(left_in2, i);
  }
  delay(time);
}

void drive_left(int time)
{
  
  digitalWrite(left_in3, HIGH);
  digitalWrite(right_in3, LOW);
  int i;
  for (i = 0; i<255; i++)
  {
    analogWrite(right_in2, i);
    analogWrite(left_in2, i);
  }
  delay(time);
}

void sendforwardsignal(){
   controller="2";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,1);
   delay(300); 
}

void sendreversesignal(){
   controller="1";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,1);
   delay(300); 
}

void sendstopsignal(){
   controller="3";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,1);
   delay(300); 
}

/*
void go_to_start()
{
  int distance_to_back; //set distance needing to reverse
  while (Back_Ultrasonic.Ranging(CM)!=distance_to_back)
  {
    if (Back_Ultrasonic.Ranging(CM) > distance_to_back)
     
  }
 
}
 
  */
/*

void findlegomanandstop(){
  Front_Distance=Front_Ultrasonic.Ranging(CM);
  while(Front_Distance>3){
      //drive forward
       Front_Distance=Front_Ultrasonic.Ranging(CM);
       delay(300);
  }
 // stop_motors();
}

sendforwardsignal(){
   controller="1";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,1);
   delay(300); 
}


*/


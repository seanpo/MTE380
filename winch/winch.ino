#include <VirtualWire.h>

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

int enable =7;
int fwd = 11;
int rev = 13;

void drive_forward()
{
  digitalWrite(enable, HIGH);
  digitalWrite(rev, LOW);
  digitalWrite(fwd, HIGH);
}

void drive_backward()
{
  digitalWrite(enable, HIGH);
  digitalWrite(fwd, LOW);
  digitalWrite(rev, HIGH);
}

void motor_stop()
{
  digitalWrite(enable, LOW);
  digitalWrite(rev, LOW);
  digitalWrite(fwd, LOW);
}

void setup()
{
    pinMode(rev, OUTPUT);
    pinMode(fwd, OUTPUT);
    pinMode(enable, OUTPUT);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec
    pinMode(13, OUTPUT);

    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{   
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    if(buf[0]=='1')
    {
      drive_forward();
      delay(500);
    }  
    else if (buf[0]=='2')
    {
      drive_backward();
      delay(500);
    }
    else {
      motor_stop();
      delay(500);
    }
  }  
  else{
    motor_stop();
    delay(500);
  }
}

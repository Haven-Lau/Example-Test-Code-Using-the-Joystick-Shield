#include <RH_ASK.h>
#include <SPI.h> 
//#include <Servo.h>

//Servo servo1, servo2;

int pwm_a = 3;   //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13

unsigned long x = 0;
unsigned long y = 0;
int leftPow = 0;
int rightPow = 0;
bool leftRev;
bool rightRev;
bool right;
bool left;
bool up;
bool down;
bool select;
bool f;
bool e;

RH_ASK driver;

void setup(){
    pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
    pinMode(pwm_b, OUTPUT);
    pinMode(dir_a, OUTPUT);
    pinMode(dir_b, OUTPUT);
    
    analogWrite(pwm_a, 0);
    analogWrite(pwm_b, 0);
  
    Serial.begin(9600);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");
    /*vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_set_rx_pin(9);
    vw_set_tx_pin(10);
    vw_rx_start();       // Start the receiver PLL running*/
}

void loop(){
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    /*uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;*/
    char first, second, third, forth;
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	// Message with a good checksum received, dump it.

        int first = buf [0];
        int second = buf [1];
        int third = buf [2];
        int forth = buf [3];
        
        x =  first * 4 + second / 64;
        y = (second % 64) * 16 + (third / 16);
        right = !bitRead(third,3);
        left = !bitRead(third,2);
        up = !bitRead(third,1);
        down = !bitRead(third,0);
        select = !bitRead(forth,7);
        f = !bitRead(forth, 6);
        e = !bitRead(forth,5);
        
        for (int i = 5; i >= 0; i--)
          Serial.print(bitRead(third,i),BIN);
        for (int i = 7; i >= 5; i--)
          Serial.print(bitRead(forth,i),BIN);
        Serial.println(" ");
        /*
        for (int i = 0; i < 4; i++){
          Serial.print(i+1); Serial.print(": ");
          Serial.println(buf[i]);
        }*/
        Serial.print("x: ");
        Serial.println(x);
        Serial.print("y: ");
        Serial.println(y);
        Serial.print("right: ");
        Serial.println(right);
        Serial.print("left: ");
        Serial.println(left);
        Serial.print("up: ");
        Serial.println(up);
        Serial.print("down: ");
        Serial.println(down);
        Serial.print("select: ");
        Serial.println(select);
        Serial.print("f: ");
        Serial.println(f);
        Serial.print("e: ");
        Serial.println(e);
        //y = 515, x = 506
        if (x < 508 && y >= 515){ //upper left quadrant
          leftPow = (y - 515) - (508 - x);
          rightPow = (y - 515) + (508 - x);
        }else if (x <= 508 && y <= 515){ //lower left quadrant
          leftPow = -((515 - y) + (508 - x));
          rightPow = -((515 - y) - (508 - x));
        }else if (x >= 508 && y > 515){ //upper right quadrant
          leftPow = (y - 515) + (x - 508);
          rightPow = (y - 515) - (x - 508);
        }else if (x > 508 && y <= 515){ //lower right quadrant
          leftPow = (-(515 - y) + (x - 508));
          rightPow = (-(515 - y) - (x - 508));
        }
        leftPow /= 3;
        rightPow /= 3;
        digitalWrite(dir_a, HIGH);
        digitalWrite(dir_b, HIGH);
        rightRev = 0;
        leftRev = 0;
        int lim = 170;
        if (leftPow < 0){
          digitalWrite(dir_a, LOW);
          leftPow = abs(leftPow);
          leftRev = 1;
        }
        if (rightPow < 0){
          digitalWrite(dir_b, LOW);
          rightPow = abs(rightPow);
          rightRev = 1;
        }
        if (leftPow > 170)
          leftPow = 170;
        if (rightPow > 170)
          rightPow = 170;
        Serial.print(leftPow);
        Serial.print(", ");
        Serial.print(rightPow);
        Serial.print(", ");
        Serial.print(leftRev);
        Serial.print(", ");
        Serial.println(rightRev);
        if(up){
          analogWrite(4, 177);
          analogWrite(5, 0);
        }
        analogWrite(pwm_a, leftPow);
        analogWrite(pwm_b, rightPow);
        delay(10);
    }
}

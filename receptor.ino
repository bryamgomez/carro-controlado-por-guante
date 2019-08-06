
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>
#include <Servo.h>

RF24 radio (7,8);
int text[5];
const byte address [6]="00001";

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int carro1 =42;
int carro2 =40;
int carro3 = 38;
int carro4 = 36;


void setup(){
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(carro1, OUTPUT);
   pinMode(carro2, OUTPUT);
   pinMode(carro3, OUTPUT);
   pinMode(carro4, OUTPUT);
 
     servo1.attach(22); 
  servo2.attach(24);
  servo3.attach(26);
  servo4.attach(28);
   
  }


void loop()
{
    if (radio.available()){
      radio.read(&text,sizeof(text));   
      if(text[0]==1)
        {
          digitalWrite(carro1, LOW);
   digitalWrite(carro2, LOW);

  digitalWrite(carro3, LOW);
   digitalWrite(carro4, LOW);

        }
        if(text[0]==3)
        {
          digitalWrite(carro1, LOW);
   digitalWrite(carro2, LOW);
     
  digitalWrite(carro3, LOW);
   digitalWrite(carro4, HIGH);
  
   Serial.println("izquierda");
        }
         if(text[0]==2)
        {
       digitalWrite(carro1, HIGH);
   digitalWrite(carro2, LOW);
    
  digitalWrite(carro3, LOW);
   digitalWrite(carro4, LOW);
 
            Serial.println("derecha");
        }
         if(text[0]==4)
        {
  digitalWrite(carro1, HIGH);
   digitalWrite(carro2, LOW);
    
  digitalWrite(carro3, LOW);
   digitalWrite(carro4, HIGH);
  
            Serial.println("adelante");
        }
         if(text[0]==5)
        {
        digitalWrite(carro1, LOW);
   digitalWrite(carro2, HIGH);
  
  digitalWrite(carro3, HIGH);
   digitalWrite(carro4, LOW);

            Serial.println("atras");
        }
        text[1]= map(text[1], 731, 915, 180, 0);// PINZA
    if(text[1]<0)
    text[1]=0;
     if(text[1]>180)
    text[1]=180;

       text[2]= map(text[2], 740, 930, 0, 180);// PINZA
       if(text[2]<0)
    text[2]=0;
     if(text[2]>180)
    text[2]=180;
       
        text[3]= map(text[3], 745, 915, 0, 180);// PINZA
        if(text[3]<0)
    text[3]=0;
     if(text[3]>180)
    text[3]=180;
        
           text[4]= map(text[4], 735, 875, 180, 90);// PINZA
           if(text[4]<90)
    text[4]=90;
     if(text[4]>180)
    text[4]=180;
    
      
       servo1.write(text[1]);
       servo2.write(text[2]);
          servo3.write(text[3]);
          servo4.write(text[4]);
       
      Serial.println(text[1]);
      }
}






/*







#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
 
const int pinCE = 7;
const int pinCSN = 8;
RF24 radio(pinCE, pinCSN);
 
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
char data[16]="Hola mundo" ;
 
void setup(void)
{
   radio.begin();
   radio.openWritingPipe(pipe);
}
 
void loop(void)
{
   radio.write(data, sizeof data);
   delay(1000);
}

*/

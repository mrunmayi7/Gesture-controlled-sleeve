#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10,11); // RX | TX pins (that should receive TX | RX respectively)

int i;

void setup() {
//  Serial.begin(38400);
  BTSerial.begin(38400); 
}
 
void loop() {
  BTSerial.write(i);
  i++;
  
  if(i>255)
    i=0;
  
  delay(1000);
  
}

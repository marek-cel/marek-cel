// Arduino Serial Example #1 Remote Control Blink - Master
 
void setup() 
{
    Serial.begin(9600);  
    // wait for the serial port to connect. Required for Leonardo/Micro native USB port only
    while (!Serial) {  ;  }
}
 
 
void loop() 
{
  Serial.print(1);
  delay(1000);
  Serial.print(0);
  delay(1000);
}



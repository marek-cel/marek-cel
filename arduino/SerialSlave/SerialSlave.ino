// Arduino Serial Example #1 Remote Control Blink - Slave
 
char c  = ' ';
byte LED = 2;
 
void setup() 
{
   pinMode(LED, OUTPUT);
   Serial.begin(9600);
   Serial.println("START");
}
 
 
void loop()
{
   if(Serial.available())
   {
      char c = Serial.read();
      if (c=='0') { digitalWrite(LED, LOW); }
      if (c=='1') { digitalWrite(LED, HIGH); }
      Serial.println(c);
   }
 
}



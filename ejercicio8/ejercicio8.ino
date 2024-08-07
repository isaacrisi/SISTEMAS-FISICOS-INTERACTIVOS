#include<iostream>

void setup() 
{
  // put your setup code here, to run once:
  const int inter = 0;
}

void loop() {

  uint32_t currentTime = millis();

  if (millis() > currentTime)
  {
    inter++;
  }
  
  if(inter == 10000){
    Serial.print("UNO SECOND"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
  }
  if(inter == 20000){
    Serial.print("DOS SECONDS"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
  }
  if(inter == 30000){
    Serial.print("TRES SECONDS"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
  }
  if(inter > 30000){
    Serial.print("START_OVER"); Serial.print('\n');
    Serial.print(inter); Serial.print('\n'); Serial.print('\n');
    inter = 0;
  }
}

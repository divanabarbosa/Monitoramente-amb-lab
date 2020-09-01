#include <avr/wdt.h>

float TEMP, LUM;
char liga;

void RESET(); 

void setup() {
  wdt_disable();
  
  Serial.begin(9600);
}
  
void loop() { 
      
       if(Serial.available()>0){
       liga=Serial.read();
       if(liga=='L'){
        
       LUM = analogRead(0)*0.00488;
       Serial.println(LUM);
       if(LUM >= 4.99)
        Serial.write('A');
       else if(LUM <= 4.95)
        Serial.write('B');
       else Serial.write('C');

       delay(2);
           
       TEMP = analogRead(2)*0.00488/0.01;          
       Serial.println(TEMP);
       if(TEMP>=60) //DEFINIR MAIOR TEMPERATURA
        Serial.write('D');
       else if(TEMP<=10)  //DEFINIR MENOR TEMPERATURA
        Serial.write('E');
       else Serial.write('F'); //TEMPERATURA NORMAL

       delay(2);
      }
   }
}


void RESET()
{
  noInterrupts(); 
  wdt_enable(WDTO_2S);
  while(1); 
}  


#include  <avr/wdt.h>

const int  CH=3,LED1=5, BUZ=6,PB=4;
char temp;
char lum;

#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
void ISR_ALARME1();

void RESET(); 

void setup() {
  wdt_disable();
    
  pinMode(CH,INPUT_PULLUP);
  pinMode(LED1,OUTPUT);
  pinMode(BUZ,OUTPUT);
  pinMode(PB,INPUT_PULLUP); 
  pinMode(2,OUTPUT);
  
  attachInterrupt(0,ISR_ALARME1,RISING);
  interrupts();
   
  lcd.begin(16,2);
  lcd.clear ();
  lcd.setCursor(0,0);
  
  Serial.begin(9600); //para enviar dado de ligar o sistema
  
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("M.A.L.");
  lcd.setCursor(1,1);
  lcd.print("Divana e Julia"); 
  delay(5000);
  lcd.clear();

 }

void loop() {
 digitalWrite(2,LOW);

 if(digitalRead(PB)==0)
          RESET();
 if(digitalRead(CH)==0){
      //lcd.clear();
      Serial.write('L'); 
      digitalWrite(LED1,HIGH);
      if(Serial.available()>0){
       lcd.setCursor(0,0);
       lcd.print("Local  ");
       lum=Serial.read();
       if(lum=='A')
        { lcd.setCursor(7,0);
          lcd.print("Escuro   "); 
        }else if(lum=='B')
        { lcd.setCursor(7,0);
          lcd.print("Claro    ");
        }else if(lum=='C')
        { lcd.setCursor(7,0);
          lcd.print("Normal   ");
        }

        delay(2);
        
        lcd.setCursor(0,1);
        lcd.print("Temp. ");
        temp=Serial.read();
        if(temp=='D')
          digitalWrite(2,HIGH);
        else if(temp=='E')
          digitalWrite(2,HIGH);
         else if(temp=='F')
         { lcd.setCursor(7,1);
           lcd.print("Normal    ");
         }
         delay(2);
    }
  } 
}

void ISR_ALARME1()
{
 lcd.clear();
 lcd.setCursor(5,0);
 lcd.print("ALARME");
 delay(5000);
 if (temp=='D'){
    digitalWrite(7, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Temperatura Alta");
 }else if(temp=='E'){  
    digitalWrite(7, HIGH);
    lcd.setCursor(3,1); 
    lcd.print("Temp. Baixa");
 }digitalWrite(BUZ,HIGH);
 delay(20000);
 RESET(); 
 }

void RESET()
{
  noInterrupts();
  wdt_enable(WDTO_2S);
  while(1); 
}  
   
  
  
  




#include <GSM.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11);

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;


#define Area 3
#define Area2 4
#define Area3 5
int temp=0,i=0;
int led=13;

char str[15];


void setup()
{


    Serial.begin(19200);
  pinMode(led, OUTPUT);
   pinMode(Area, OUTPUT);
    pinMode(Area2, OUTPUT);
     pinMode(Area3, OUTPUT);
  
   
  lcd.begin(16,1);
  lcd.setCursor(0,0);
  
  for (int positionCounter = 0; positionCounter < 25; positionCounter++){
      lcd.scrollDisplayLeft();
    lcd.print(" Gsm Based StreetLight Automation System");
   
    delay(350);
  }

 
  lcd.clear();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("By Yannick Dongo");
  lcd.setCursor(0,1);
  lcd.print("  12CK013851  ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  Serial.print("AT+CSCA=\"+2348090001518\"\n\r");
  Serial.print("AT+CMGS=\"+2348151233171\"\n\r");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Area   Area2  Area3 ");
  lcd.setCursor(0,1);
  lcd.print("OFF    OFF   OFF "); 
}

void loop()
{
  
  lcd.setCursor(0,0);
  lcd.print("Area Area2 Area3");
  if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }
}

 void serialEvent() 
 {
  while(Serial.available()) 
  {
    if(Serial.find("#A."))
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      while (Serial.available()) 
      {
      char inChar=Serial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 
      } 
    }
   }
 }
 
void check()
{
   String message;

   if(!(strncmp(str,"area3 on",5)))
    {
      digitalWrite(Area3, HIGH);
      lcd.setCursor(13,1); 
      lcd.print("ON    ");
      delay(200);
      
      message="Area3 ON";
      sendMessage(message);
    }  
   
   else if(!(strncmp(str,"area3 off",6)))
    {
      digitalWrite(Area3, LOW);
      lcd.setCursor(13,1); 
      lcd.print("OFF    ");
      delay(200);

       message="Area3 OFF";
      sendMessage(message);
    }
  
    else if(!(strncmp(str,"area on",5)))
    {
      digitalWrite(Area, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON   ");
      delay(200);

       message="Area1 ON";
      sendMessage(message);
    }
 
    else if(!(strncmp(str,"area off",7)))
    {
      digitalWrite(Area, LOW);
      lcd.setCursor(0,1); 
      lcd.print("OFF    ");
      delay(200);

       message="Area1 OFF";
      sendMessage(message);
    }
 
    else if(!(strncmp(str,"area2 on",8)))
    {
    
     digitalWrite(Area2, HIGH);
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(200);

       message="Area2 ON";
      sendMessage(message);
    }
 
    else if(!(strncmp(str,"area2 off",9)))
    {
      
      digitalWrite(Area2, LOW);
      lcd.setCursor(7,1); 
      lcd.print("OFF    ");
      delay(200);

       message="Area2 OFF";
      sendMessage(message);
    } 
    
    else if(!(strncmp(str,"all on",6)))
    {
      digitalWrite(Area2, HIGH);
      digitalWrite(Area, HIGH);
      digitalWrite(Area3, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON     ON    ON  ");
      delay(200);

       message="All AREA's ON";
      sendMessage(message);
    }
 
    else if(!(strncmp(str,"all off",7)))
    {

   
      digitalWrite(Area2, LOW);
      digitalWrite(Area, LOW);
      digitalWrite(Area3, LOW);
      lcd.setCursor(0,1); 
      lcd.print("OFF   OFF    OFF  ");
      delay(200);

        message="All AREA's OFF";
      sendMessage(message);
    }
}     


   void sendMessage(String message){
   //To Alert the Control Via SMS that update was successful
    Serial.print("AT+CMGF=1\r"); 
    delay(1000); 
     
     Serial.print("AT+CSCA=\"+2348090001518\"\n\r"); 
    Serial.print("AT+CMGS=\"+2348151233171\"\n\r");  
    delay(1000);  
    Serial.println(message);  
    Serial.print("\r"); 
    Serial.println((char)26); 
    delay(1000); 

    }

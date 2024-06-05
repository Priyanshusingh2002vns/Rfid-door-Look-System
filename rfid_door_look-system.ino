#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


#include <LiquidCrystal_I2C.h>


 int con=75;

 
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 3
Servo myservo;


LiquidCrystal_I2C lcd(0x27, 16, 2);


#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
void setup() 
{
  analogWrite(6,con);
  Serial.begin(9600);   
  SPI.begin();          
  mfrc522.PCD_Init();   

 lcd.init();
  lcd.backlight();



  myservo.attach(SERVO_PIN);
  myservo.write( 70 );
  delay(2000);
  myservo.write( 0 );



  
  Serial.println("Put your card to the reader...");
  lcd.print("your card here");
  Serial.println();

}
void loop() 
{
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  
  
  
  
  if (content.substring(1) == "03 0D A0 09") 
  {
    Serial.println("Authorized access");
    lcd.setCursor(0, 1); 
    lcd.print("Opening  Door");
    Serial.println();
   myservo.write( 70 );
 delay(3000);
  myservo.write( 0 );
  lcd.setCursor(0, 1);
    lcd.print("Door   locked");

  }
 
 else   {
    Serial.println("Access denied");
    lcd.setCursor(0, 1);
 lcd.print("Access denied");

    delay(DENIED_DELAY);

 
  }
}

#include <LiquidCrystal.h> 
#include<Keypad.h>

LiquidCrystal lcd(23, 22, 26, 27, 28, 29);

int buton=1;
int butonDurum;

// PIR DEGISKENLERI
int pirPin=2;
boolean pirDurum=0;
int lamba=3;

// FLAME DEGISKENLERI
int buzzer=11;
int flamePin=19;
boolean flameDurum=0;

// TEMPRATURE DEGISKENLERI
const int lm35Pin = 0; 
float lm35;
float sicaklik;

// KEYPAD DEGISKENLERI
char tuslar[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte satirPin[4]={7,8,9,10};
byte sutunPin[3]={4,5,6};
String sifre = "1414"; 
char girilenDeger;
int index = 0;
int hata = 0;
int redLed = 13;
int greenLed = 12; 
int toplam = 0;

Keypad keypad=Keypad(makeKeymap(tuslar),satirPin,sutunPin,4,3);

void setup() {
  pinMode(buton,INPUT);
  pinMode(pirPin,INPUT);
  pinMode(lamba,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(flamePin,INPUT);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  
  lcd.begin(16,2);
  lcd.println("Program basliyor..");
  delay(100);
}

void loop() {
  butonDurum=digitalRead(buton);
  if(butonDurum==1){
    // PIR
    pirDurum=digitalRead(pirPin);
    if(pirDurum==1)
    {
      digitalWrite(lamba,HIGH);
    }
    else
    {
      digitalWrite(lamba,LOW);
    }
    // GAZ SENSORU
    flameDurum=digitalRead(flamePin);
    delay(50);
    if(flameDurum==1)
    {
       digitalWrite(buzzer,HIGH);
       delay(100);
       digitalWrite(buzzer,LOW);
    }
    // TEMPRATURE
    lm35=analogRead(lm35Pin); 
    lcd.setCursor(0,1);
    sicaklik = lm35*(5.0/1023.0)*100 ; 
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(sicaklik);
    lcd.print("C");
    delay(100);
    lcd.clear();
    if(sicaklik>30.0)
    {
      lcd.print("Sicaklik");
      lcd.setCursor(0,1);
      lcd.print("yukseldi!");
      delay(100);
    }
    if(sicaklik<20.0)
    {
      lcd.print("Sicaklik");
      lcd.setCursor(0,1);
      lcd.print("dustu!");
      delay(100);
    }
    lcd.clear();
  }
  else{
    // KEYPAD
    girilenDeger=keypad.getKey();
    if(girilenDeger)
    {
      if(girilenDeger == '*' || girilenDeger == '#')
      {
        index = 0;
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, LOW);
        delay(100);
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
       }
       else if(girilenDeger==sifre[index])
       {
          index++;
       }
       else if(girilenDeger!=sifre[index])
       {
          hata++;
          index++;
       }

       if(index==4)
       {
          if(hata>0)
          {
            toplam++;
            hata=0;
            index=0;
            digitalWrite(redLed, HIGH);
            digitalWrite(greenLed, LOW);
            delay(200);
            digitalWrite(redLed, LOW);
            digitalWrite(greenLed, LOW);
          }
          else if(index==4 && hata==0)
          {
            index=0;
            digitalWrite(redLed, LOW);
            digitalWrite(greenLed, HIGH);
            delay(200);
            digitalWrite(redLed, LOW);
            digitalWrite(greenLed, LOW);
          }

          if(toplam=4)
          {
            toplam=0;
            delay(100);
          }
       }
    }
  }
}

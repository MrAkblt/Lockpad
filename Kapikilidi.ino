#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

const byte SATIR = 4;
const byte SUTUN= 3;
char keys[SATIR][SUTUN] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[SATIR] = { 31, 33, 35, 37 };
byte colPins[SUTUN] = { 39, 41, 43 };
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, SATIR, SUTUN );
String sifre="1234#";
int onay=0, kilit=10;
String str="";
void setup()
{ 
  lcd.begin(16, 2); // 16*2 kullandığımız için 16,2 olarak başlatıyoruz.
  lcd.clear();
  lcd.setCursor(2,0); // 0,0 cursoru 0,0 a ayarlıyoruz.
  lcd.print("Hosgeldiniz"); // Ekrana mesajımızı yazıyoruz
  lcd.setCursor(0,2);
  lcd.print("Sifre:");
  Serial.begin(9600);
  pinMode(kilit, OUTPUT);
  
}
void loop()
{ 
  char key = kpd.waitForKey();
  str+=key; lcd.print(key);
  if(key=='#'&onay==0)
  {
    if(str==sifre)
    {lcd.clear(); lcd.print("Dogru Sifre"); digitalWrite(kilit,HIGH);delay(1200); digitalWrite(kilit,LOW);  lcd.clear(); str="";}
    else
    {lcd.clear(); lcd.print("Yanlis Sifre"); delay(1200); lcd.clear(); str="";}
  }
  if(str=="*101*")
  {
    lcd.clear(); lcd.print("Yeni Sifre:"); str=""; onay=1;
  }
  if(onay==1&key=='#')
  { 
    sifre=str; lcd.clear();lcd.print("Sifre Atandi"); delay(1000); lcd.clear(); str=""; onay=0;
  }
}


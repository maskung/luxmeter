#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "Thamonwan";
const char* password = "00002222";

#define APPID   "LightIntensity"  //====ได้จากตอนที่เราตั้งชื่อ Project ที่ netpie
#define KEY     "5nJQ4wjDskmBN1u"  //====จะได้จากตอนสร้าง Key
#define SECRET  "MXSv0ElbM3Hbb0SgYJnhgl06y"
#define ALIAS   "luxmeter"
#define TargetWeb "HTML_web"
#define LIGHT_STATUS "HTML_light"

#include <Wire.h>
#define POWER_DOWN_MODE       0x00  
#define POWER_ON_MODE         0x01  
#define RESET_MODE            0x07  
#define M_H_RESOLUTION_MODE   0x10 
#define M_H_RESOLUTION_MODE2  0x11 
#define M_L_RESOLUTION_MODE   0x13 
#define S_H_RESOLUTION_MODE   0x20 
#define S_H_RESOLUTION_MODE2  0x21 
#define S_L_RESOLUTION_MODE   0x23    
  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
const byte BH1750FVI_ADDR = 0x23;  
byte buff[2];
#define LIGHT_PIN D0

WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}


void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}

void setup() {

  Serial.begin( 115200 );
  Wire.begin();  
  
  pinMode( LIGHT_PIN, OUTPUT );
  digitalWrite(LIGHT_PIN, LOW);
    
  lcd.begin(16,2);  
  delay(250);
  lcd.noBacklight();
  lcd.backlight();
  delay(250);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initialize Sensor...");
  setBH1750Mode( BH1750FVI_ADDR, M_H_RESOLUTION_MODE ); 

  /* Event listener */
  microgear.on(MESSAGE,onMsghandler);
  microgear.on(CONNECTED,onConnected);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting Wifi...");

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);
      Serial.print(".");
   }

  lcd.setCursor(0,0);
  Serial.println("WiFi connected");  
  lcd.print("Wifi connected...");
  Serial.println("IP address: ");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());
  delay(1000);
  microgear.init(KEY,SECRET,ALIAS);
  microgear.connect(APPID);

  //Serial.println("NETPIE Connected : Done... ");
}
 
void loop() {
  static byte dc;
  uint16_t value; 
  if( readBH1750( BH1750FVI_ADDR ) == 2 ) {
    value = (buff[0]<<8) | buff[1];
    value = (5*(uint32_t)value)/6;
  }

  if (microgear.connected())
    {
       microgear.loop();
       Serial.println("connected");

       String data = String(value);
      
       char msg[128];
       data.toCharArray(msg,data.length()+1);
       Serial.println(msg);    

       microgear.chat(TargetWeb , msg);
    }
   else 
   {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
   }

  
  Serial.print( value, DEC );
  Serial.println("[lx]"); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Light Intensity (lx)");
  lcd.setCursor(9,1);
  lcd.print(value);

  //if lux meter > 20000 Set LED OFF
  if ( value >= 20000 ) {
      digitalWrite( LIGHT_PIN, LOW);
     

       String data = String(0);
      
       char msg[128];
       data.toCharArray(msg,data.length()+1);
       Serial.println(msg);    

       microgear.chat(LIGHT_STATUS , msg);
       
  } else {
      digitalWrite( LIGHT_PIN, HIGH);
      String data = String(1);
      
       char msg[128];
       data.toCharArray(msg,data.length()+1);
       Serial.println(msg);    

       microgear.chat(LIGHT_STATUS , msg);
  }

  delay(1000);

}

int readBH1750( byte i2c_addr ) {
  int dataNum=0;
  Wire.beginTransmission( i2c_addr );
  Wire.requestFrom( (unsigned int)i2c_addr, 2 ); 
  while( Wire.available() ) {
    buff[dataNum] = Wire.read();
    dataNum++;
  }
  Wire.endTransmission();
  return dataNum;
}

void setBH1750Mode( byte i2c_addr, byte mode ) {
  Wire.beginTransmission( i2c_addr );
  Wire.write( mode );
  Wire.endTransmission();
  delay(200); 
}

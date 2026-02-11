#include <Ultrasonic.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h> 
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "";
const char* password = "";

#define BOTtoken ""  // your Bot Token (Get from Botfather)

const String CHAT_ID[] = { //user chat id
  ""
}; 

const int numCHAT_ID = sizeof(CHAT_ID) / sizeof(CHAT_ID[0]); //Menentukan panjang CHAT_ID

#define TRIG_PIN  17 //TRIG PIN BUKA SAMPAH
#define ECHO_PIN  16  //ECHO PIN BUKA SAMPAH
#define TRIG_PIN_TINGGI 2//TRIG PIN TINGGI SAMPAH
#define ECHO_PIN_TINGGI 4//ECHO PIN TINGGI SAMPAH
#define SERVO_PIN 13  // ESP32 pin GIOP26 connected to Servo Motor's pin
#define JARAK_BUKA  40 // centimeters
#define JARAK_TINGGI 10 // centimeters
#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES 2

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
Servo servo; // create servo object to control a servo

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

// variables will change:
float duration_us, distance_cm, duration_us_tinggi, distance_cm_tinggi;
bool messageSent = false;
void setup() {
  Serial.begin (115200);       // initialize serial port

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  for (int i = 0; i < numCHAT_ID; i++) {
      bot.sendMessage(CHAT_ID[i], "System UP!", "");
  }
  pinMode(TRIG_PIN, OUTPUT); // set ESP32 pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set ESP32 pin to input mode
  pinMode(TRIG_PIN_TINGGI, OUTPUT); // set ESP32 pin to output mode
  pinMode(ECHO_PIN_TINGGI, INPUT);  // set ESP32 pin to input mode
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
  lcd.init();
  lcd.backlight();
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600*7);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);   //Buka
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);   //Buka
//BUKA
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if (distance_cm < JARAK_BUKA){
     servo.write(0); // rotate servo motor to 90 degree
     Serial.print("Jarak: ");
     Serial.print(distance_cm);
     Serial.println(" cm");
  }else{
    delay(500);
    servo.write(360);  // rotate servo motor to 0 degree
  }
  // print the value to Serial Monitor

//TINGGI
  digitalWrite(TRIG_PIN_TINGGI, HIGH);   //Tinggi
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_TINGGI, LOW);   //Tinggi
  // Sensor Ultrasonic Buka
  // measure duration of pulse from ECHO pin
  duration_us_tinggi = pulseIn(ECHO_PIN_TINGGI, HIGH);
  // calculate the distance
  distance_cm_tinggi = 0.017 * duration_us_tinggi;
  if (distance_cm_tinggi < JARAK_TINGGI){
    lcd.setCursor(6,0);
    lcd.print("Maaf");
    lcd.setCursor(1,1);
    lcd.print("Sampah Penuh!!!");
    if(!messageSent){
      while (!timeClient.update()) {
        timeClient.forceUpdate();
    }

    // The formattedDate comes with the following format:
    // 2018-05-28T16:00:13Z
    // We need to extract date and time
    formattedDate = timeClient.getFormattedDate();

    // Extract date
    int splitT = formattedDate.indexOf("T");
    String dayStamp = formattedDate.substring(0, splitT);

    // Extract time
    //String timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
    String timeStamp = formattedDate.substring(formattedDate.indexOf("T") + 1, formattedDate.indexOf(":", formattedDate.indexOf("T") + 1) + 3);

    // Format the time as "HH:MM"
    String formattedTimeStamp = timeStamp.substring(0, 2) + ":" + timeStamp.substring(3, 5);

    // Splitting the date components
    int year = dayStamp.substring(0, 4).toInt();
    int month = dayStamp.substring(5, 7).toInt();
    int day = dayStamp.substring(8, 10).toInt();

    // Define an array of month names
    String months[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    // Format the date as "DD / Bulan / YYYY"
    String formattedDayStamp = String(day) + " / " + months[month - 1] + " / " + String(year);

    String message = "Sampah Penuh !!! \nTanggal : " + formattedDayStamp + " \nPukul : " + formattedTimeStamp + " WIB";
      for (int i = 0; i < numCHAT_ID; i++) {
        bot.sendMessage(CHAT_ID[i], message, "");
        Serial.println(message);
        Serial.println("Telegram message sent to chat ID: " + CHAT_ID[i]);
      }
    }
    messageSent = true;
    Serial.print("Tinggi: ");
    Serial.print(distance_cm_tinggi);
    Serial.println(" cm");
  }else{
    messageSent = false;
    lcd.setCursor(6,0);
    lcd.print("Maaf");
    lcd.setCursor(1,1);
    lcd.print("Sampah Penuh!!!");
  }
  // print the value to Serial Monitor
  delay(500);
}
/*
ไฟล์นี้ทดสอบการส่งค่า int และ float ขึ้นไปยัง Firebase
*/

#include <Firebase_ESP_Client.h>    // import ไลบรารี่สำหรับ Firebase

// การทำงานของ token และ payload ที่จำเป็นสำหรับ firebase
#include "addons/TokenHelper.h"     
#include "addons/RTDBHelper.h"

#define WiFi_SSID "wifi_ssid"          // ระุชื่อ wifi hotspot
#define WiFi_PASSWORD "wifi_password"  // ระบุรหัส wifi hotspot

#define API_KEY "ระบุ API-KEY ตรงนี้"     // API KEY ที่ได้จาก Firebase
#define DATABASE_URL "ระบุลิงค์ของ database ตรงนี้"   // ระบุลิงค์ Realtime Database

// ตัวแปรที่จำเป็นสำหรับใช้งาน Firebase ในการเชื่อมต่อและการส่งค่า
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// ตัวแปรกำหนดค่าสมมติในการส่งเพื่อการทดสอบ
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


void setup() {

  Serial.begin(115200);

  // การเชื่อมต่อ WiFi
  WiFi.begin(WiFi_SSID, WiFi_PASSWORD);
  Serial.print("connecting to ");
  Serial.print(WiFi_SSID);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;   // นำ API-KEY ใส่คำสั่ง config

  config.database_url = DATABASE_URL;   // // นำ URL ของ Realtime database ใส่คำสั่ง config

  // ตรวจสอบการเชื่อมต่อ ทำการเชื่อมต่อโดยใช้ค่าจาก config และ auth
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");   // แสดงคำว่า "ok" หากเชื่อมต่อสำเร็จ
    signupOK = true;        // หากเชื่อมต่อสำเร็จ ให้ทำการระบุค่า "จริง" ให้กับตัวแปรนี้
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {

  // ระบุเงื่อนไข หากค่าใน signupOK เป็นจริง และ Firebase สามารถใช้งานได้ จะให้ทำการประมวลผลโค้ดในส่วนของการส่งค่าที่อยู่ใน if
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    // ส่งค่า int จากตัวแปร count เข้าไปยัง path test/int
    if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
      Serial.println("PASSED");                     // หากส่งผ่าน จะแสดงข้อความ "PASSED"
      Serial.println("PATH: " + fbdo.dataPath());   // หากส่งผ่านจะระบุ path ที่ส่ง
      Serial.println("TYPE: " + fbdo.dataType());   // หากส่งผ่านจะระบุ type ของ data ที่ส่ง
    }
    else {
      Serial.println("FAILED");                         // หากส่งไม่ผ่านจะขึ้นว่า "FAILED"
      Serial.println("REASON: " + fbdo.errorReason());  // หากส่งไม่ผ่านจะระบุเหตุผลที่ส่งไม่ผ่าน
    }
    count++;  // เมื่อเสร็จสิ้นจาก if หรือ else ให้นำค่าใน count มาบวก 1
    
    // ส่งค่า float จากตัวแปร count เข้าไปยัง path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }

}

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "xxxxxxxxxx";  // ระบุชื่อ WiFi ตรงนี้
const char* pwd = "xxxxxxxxxx";   // ระบุรหัส WiFi ตรงนี้

// ตัวแปรเก็บค่า temperature และ humidity สำหรับส่งค่าขึ้นฐานข้อมูล
// เมื่อนำเซ็นเซอร์มาต่อจริง จะต้องกำหนดค่าให้เป็น 0
float esp_temp = 25.5;
float esp_humid = 79;


const char* serverName = "https://xxxxxxxxxx.000webhostapp.com/data_receive.php"; // ระบุ URL ของเว็บไซต์ของตัวเอง ลงท้ายด้วย data_receive.php เป็นการส่งค่าเข้าไฟล์นี้
String esp_api_key = "xxxxxxxxxx"; // กำหนด API-KEY จะต้องตรงกับ API-KEY ในไฟล์ data_receive.php


void setup() {
  
  Serial.begin(115200);

  WiFi.begin(ssid, pwd);
  Serial.println("กำลังเชื่อมต่อ");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("เชื่อมต่อ Wi-Fi แล้ว IP Address คือ: ");
  Serial.println(WiFi.localIP());

}
void loop() {

  // คำสั่งเริ่มต้นการทำงานของการส่งค่าผ่าน HTTP protocol โดยการกำหนดชื่อเว็บไซต์ (serverName) และกำหนดประเภทของข้อมูลในส่วนของ Header
  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // กำหนด path ให้กับ URL ในการส่งข้อมูลไปยังไฟล์ data_receive.php โดยจะมี 3 ค่า ได้แก่ API-KEY, temp และ humid
  String httpRequestData = "esp_api_key=" + esp_api_key + "&esp_temp=" + esp_temp + "&esp_humid=" + esp_humid;

  // ดำเนินการส่งค่า
  int httpRequestCode = http.POST(httpRequestData);
  Serial.print(httpRequestData);
  http.end();   // ตัดการเชื่อมต่อ

  // กำหนดการส่งค่าทุกๆ 5 วินาที
  delay(5000);


}

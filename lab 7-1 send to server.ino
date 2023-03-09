
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SSID";        // เปลี่ยนข้อมูลเป็น WiFi ของตัวเอง
const char* pwd = "password";     // รหัสผ่าน WiFi

float esp_temp = 25.5;
float esp_humid = 79;

const char* serverName = "https://ชื่อเว็บ.000webhostapp.com/data_receive.php"; // เปลี่ยนเป็นชื่อเว็บไซต์ตัวเอง และเติม /data_receive.php ต่อท้าย
String esp_api_key = "1234567899";  // ตั้งค่า API-KEY ของตัวเอง


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

  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // https://iotghia.000webhostapp.com/data_receive.php?api_key_value=1234567899&temp=25.5&humid=70
  String httpRequestData = "api_key_value=" + esp_api_key + "&temp=" + esp_temp + "&humid=" + esp_humid;

  int httpRequestCode = http.POST(httpRequestData);
  Serial.print(httpRequestData);
  http.end();

  delay(10000);


}

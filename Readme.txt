# Tutorial-7-Embedded-Systems-and-IoT
การส่งค่าเข้าฐานข้อมูลแบบ real-time ด้วย Firebase


Objectives
1.  ส่งค่าเข้าฐานข้อมูล Firebase ได้

Hardware
1.	DHT Sensor หรือ Ultrasonic         1	        
2.	LED		              x
4.	Breadboard          1
5.	Computer	          1
6.	microUSB	          1 

Software
1. Arduino IDE v
--------------------
Instruction

T 7.1 ส่งค่าขึ้นฐานข้อมูล Firebase
1. ตั้งค่า Firebase โดยทำตามขั้นตอนในลิงค์นี้ https://docs.google.com/document/d/1LjWkR9mvH9aqHAJQuuZbgV3OkncwM3AxFvffaiNQIKk/edit?usp=sharing
2. คัดลอกโค้ดในโฟลเดอร์ Lab7.1 > Lab7-1.ino
3. ติดตั้ง Firebase Library โดยดูขั้นตอนจากลิงค์เดียวกัน
4. เปลี่ยนค่า API-KEY และ Database URL ให้เป็นของตัวเอง
5. ทำการอัพโหลดโค้ดและดูผลลัพธ์บน Firebase จะต้องขึ้นค่า int และ float
6. ส่งค่าเซ็นเซอร์ Temperature หรือ Ultrasonic ขึ้นไปยัง Firebase โดยใช้โค้ดเซ็นเซอร์จากแลปก่อนหน้า


--------------------

T 7.2 ส่งค่าขึ้นฐานข้อมูล SQL
1. ดูวิธีการสร้าง database ที่ลิงค์ https://www.youtube.com/watch?v=F5T8isU13bU
2. ดูวิธีการนำค่าขึ้นฐานข้อมูลที่ลิงค์ https://www.youtube.com/watch?v=C_LXWEQAy5w
3. ส่งค่าอุณหภูมิขึ้นฐานข้อมูล
4. แสดงค่าข้อมูลบนหน้าเว็บไซต์




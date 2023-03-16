<?php
// ทำการ import โค้ดเชื่อมต่อฐานข้อมูลจากไฟล์ con_db.php เพื่อให้โค้ดในไฟล์นี้ทำงานร่วมกับฐานข้อมูลได้
include 'con_db.php';
?>

<?php

$api_key_value = "1234567899";      // กำหนดตัวแปรค่า API-KEY เพื่อนำไว้เทียบกับค่า API-KEY ที่ถูกส่งมา
$api_key = $temp = $humid = "";     // กำหนดตัวแปรสำหรับรับค่าจาก ESP32

// if แรกจะเก็บการตรวจสอบว่ามีข้อมูลถูกส่งมาจากโดย method POST หรือไม่
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $api_key = esp_input($_POST["esp_api_key"]);    // ทำการรับค่า API-KEY มาเก็บไว้ในตัวแปร $api_key
    
    // if ที่สองจะเป็นการตรวจสอบค่า API-KEY ที่ถูกส่งมาว่าตรงกับที่ประกาศหรือไม่
    if($api_key == $api_key_value){
        $temp = esp_input($_POST["esp_temp"]);      // ทำการรับค่า temperature มาเก็บไว้ในตัวแปร $temp
        $humid = esp_input($_POST["esp_humid"]);    // ทำการรับค่า humid มาเก็บไว้ในตัวแปร $humid
        
        // ทำการสร้างตัวแปรเพื่อเก็บคำสั่งสำหรับนำค่าเข้าบันทึกในฐานข้อมูล ได้แก่ค่า temp และ humid
        $sql = "INSERT INTO test01 (temp, humid) VALUES ('" . $temp . "', '" . $humid . "')";
        
        // if ที่สามจะทำการตรวจสอบว่าการบันทีกค่าเข้าฐานข้อมูลสำเร็จหรือไม่
        // หากสำเร็จจะแสดงข้อความว่า "data successfuly inserted"
        // หากไม่สำเร็จจะแสดงข้อความว่า "data not inserted" และแสดงเหตุผลของ error
        if($conn->query($sql) == TRUE){
            echo "data successfully inserted!";
        }
        else{
            echo "data not inserted: " . "<br>" . $conn->error;
        }
        $conn->close(); // ยุติการเชื่อมต่อฐานข้อมูล

    }
    else{
        echo "wrong API-KEY";
    }
}
else{
    echo "no data come via POST";
}

/*
    ฟังก์ชันสำหรับ clean ค่าที่ถูกส่งมา โดยจะทำการตัดส่วนที่เป็นช่องว่าง (space) และอัครพิเศษออก (special characters)
    โดยตัวแปรที่รับค่าเข้ามาจาก POST จะถูก clearn โดยกำหนดฟังก์ชันกับตัวแปรนั้นๆ เช่น esp_input($_POST["esp_api_key"])
    คือคำตัวแปร $_POST["esp_api_key"] มาเข้าฟังก์ชัน esp_input() ส่งผลให้ค่าที่เข้ามาในตัวแปรนี้ถูก clean
*/
function esp_input($data){
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}


?>

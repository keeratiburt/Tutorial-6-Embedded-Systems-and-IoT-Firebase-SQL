<?php
/*
  โค้ดนี้สำหรับการทดสอบการส่งค่าเข้าฐานข้อมูลด้วย GET
*/
include 'con_db.php';
?>

<?php

$api_key_value = "1234567899";
$api_key = $temp = $humid = "";

if($_SERVER["REQUEST_METHOD"] == "GET"){
    $api_key = esp_input($_GET["esp_api_key"]);
    if($api_key == $api_key_value){
        $temp = esp_input($_GET["esp_temp"]);
        $humid = esp_input($_GET["esp_humid"]);
        
        $sql = "INSERT INTO test01 (temp, humid) VALUES ('" . $temp . "', '" . $humid . "')";
        if($conn->query($sql) == TRUE){
            echo "data successfully inserted!";
        }
        else{
            echo "data not inserted: " . "<br>" . $conn->error;
        }
        $conn->close();

    }
    else{
        echo "wrong API-KEY";
    }
}
else{
    echo "no data come via POST";
}

function esp_input($data){
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

// https://hiveless-situation.000webhostapp.com/data_receive.php?esp_api_key=1234567899&esp_temp=25.5&esp_humid=70

?>

<?php
include 'con_db.php';
?>

<?php

$api_key_value = "1234567899";
$api_key = $temp = $humid = "";

if($_SERVER["REQUEST_METHOD"] == "POST"){
    $api_key = esp_input($_POST["esp_api_key"]);
    if($api_key == $api_key_value){
        $temp = esp_input($_POST["esp_temp"]);
        $humid = esp_input($_POST["esp_humid"]);
        
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


?>

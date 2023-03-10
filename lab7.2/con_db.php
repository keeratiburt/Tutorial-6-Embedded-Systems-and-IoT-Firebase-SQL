<?php

$servername = "localhost";
$username = "id20422443_admin";
$password = "0123456789aA!";
$dbname = "id20422443_lab07";

// database connection
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error){
    die("cannot connect to database" . $conn->connect_error);
}
else{
    echo "connected!";
}

?>

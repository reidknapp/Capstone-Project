<!DOCTYPE html>
<html>
<body>

<?php
$servername = "localhost";
$username = "webuser";
$password = "password";
$dbname = "webdata";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

//$sql = "SELECT id, testname, test_time FROM MyGuests";

$sql = "select testname, test_time from MyGuests ORDER BY id DESC LIMIT 1";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        $formatedTime = $row["test_time"]
        $formatedTime = date( "m/d/Y", strtotime($formatedTime));

        echo "<br> Count was ". $row["testname"]. " at : ". $row["test_time"]."<br>";
    }
} else {
    echo "0 results";
}

$conn->close();
?>

</body>
</html>

<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" href="style.css" type="text/css">
<meta name="Author" content="Reid Knapp">
<title>Campus Parking</title>
<meta http-equiv="refresh" content="20" />
</head>
<body style = "background-image:url('/webfiles/UnionCollegeSeal.gif')" >

  <div id="banner">
    <img src="/webfiles/U_logo.gif" alt="Union College Campus Parking">
  </div>
  <div id="menu">
    <a href="home.php">Home</a> |
    <a href="how_it_works.php">How it Works</a> |
    <a href="about.php">About</a>
  </div>
  <div>
    <h1>Union College Campus Parking</h1>
  </div>
  <div class = "center">
    <h2>
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
      $sql = "select testname, test_time from MyGuests ORDER BY id DESC LIMIT 1";
      $result = $conn->query($sql);
      if ($result->num_rows > 0) {
        // output data of each row
        while($row = $result->fetch_assoc()) {
          echo "There were ". $row["testname"]. " cars at : ". $row["test_time"]."<br>";
        }
      } else {
        echo "0 results";
      }
      $conn->close();
      ?>
    </h2>
  </div>
  <div>
  Available Parking Spaces at the Hockey Rink Parking Lot
</div>
  <br>
  <div>
    <img src="webfiles/cam.gif?<?php echo filemtime('image.jpg') ?>" alt="Reamer Circle" width = "600" height="300" border = "3">
    <figcaption>Reamer Parking Circle at <?php echo filetime('/webfiles/cam.gif')>></figcaption>
  </div>
  <br>
  <div id="footer">
    Last revised:
    <?php
    putenv("TZ=America/Los_Angeles");
    echo date("m/d/y", filemtime($_SERVER["SCRIPT_FILENAME"]));
    ?>
    <br>By Reid Knapp

  </div>

</body>
</html>

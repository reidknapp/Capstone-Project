	<?php

	// The value of the variable name is found
	$sensor_val = $_GET["value"]
	$my_file = '/var/www/html/webfiles/hello_world.txt';
	$handle = fopen($my_file, 'w') or die('Cannot open file:  '.$my_file);
	fwrite($handle, $sensor_val);
	?>

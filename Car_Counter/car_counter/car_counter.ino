

#include <SPI.h>
#include <WiFi101.h>

// WiFi setup and initialization of globals
char ssid[] = "union"; //  your network SSID (name)
char pass[] = "";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
char server[] = "cs-knappr.union.edu";    // name address for my server (using DNS)
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

//Initialize and declare variables for sensor pins and sensor related readings
int rec1 = A1;
int rec2 = A2;
int count = 0;
long interval = 1500;
long time1 = 0;
long time2 = 0;
long lastPrint = 0;
int loopCount = 0;

void setup() {
  Serial.begin(9600); //initialize serial
  pinMode(rec1, INPUT); //set pins A1 and A2 to inputs
  pinMode(rec2, INPUT);
  attachInterrupt(rec1, countUp, FALLING); // attach interrupts to A1 and A2
  attachInterrupt(rec2, countDown, FALLING);
  //Configure pins for Adafruit ATWINC1500 Feather
  WiFi.setPins(8, 7, 4, 2);

  //Attempt to make a WiFi Connection
  connectToWiFi();
  Serial.println("Connected to wifi");
  printWiFiStatus();

}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long currentMillis = millis();

  if (currentMillis % 30000 == 0) {
    update(count);
  }

  loopCount++;
  if (count < 0) {
    count = 0;
  }
  if (count != lastPrint) {
    Serial.println(count);
    lastPrint = count;
  }
}

void countUp() {
  Serial.println("rec1 interrupt");
  time1 = millis();
  if (time2 != 0) {
    if (abs(time2 - time1) > interval) {
      time2 = 0;
    }
    else if (time2 < time1) {
      count++;
      time1 = 0;
      time2 = 0;
    }
  }
}

void countDown() {
  Serial.println("rec2 interrupt");

  time2 = millis();
  if (time1 != 0) {
    if (abs(time2 - time1) > interval) {
      time1 = 0;
    }
    else if (time1 != 0 && time1 < time2) {
      count--;
      time1 = 0;
      time2 = 0;
    }
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void update(int rq) {
  String str = String(rq);

  //Initializes the request string
  String request;
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    request = "POST /create_mysql_record.php?value=" + str + " HTTP/1.1";
    Serial.println(request);
    client.println(request);
    client.println("Host: www.cs-knappr.union.edu");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("Could not connect to server");

  }
}

void connectToWiFi() {
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(1000);
  }
}

#include <ESP8266WiFi.h>

// initialise wifi password and name
const char* wiFiPassword = "your wifi password";
const char* wiFiName = "your wifi name";
const char* hostedAPIServer = "127.0.0.1";
const int hostedAPIServerport = 8080;

void APIScrape();

void setup() {
  // setup serial communication and bitrate
  Serial.begin(115200);
  Serial.println();

  // connect the board to your internet and verify it's connectivity
  WiFi.begin(wiFiName, wiFiPassword);
  Serial.print("Connecting to WiFi!");

  // while connecting to the internet, print out a dot every 500 milliseconds
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // print out devices IP address when connected
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  for(int i = 0; i < 2; i++) {
    APIScrape();
  }
}


void APIScrape(url, port) {
  // checks if WiFi is still connected
  if(WiFi.status() == WL_CONNECTED) {
    // create objects under WiFiClient and HTTPClient
    WiFiClient client;
    HTTPClient http;

    // concatenate API HTTP server and port together
    String APIPath = hostedAPIServer + to_str(hostedAPIServerport);

    // connect to the API HTTP server
    http.begin(client, APIPath.c_str());

    // send HTTP GET request
    int HTTPRequest = http.GET();

    // if the GET request has gone through, print out if it was successful and what was gathered from it
    if (HTTPRequest > 0) {
      // print GET request response
      Serial.print("HTTP request code: ");
      Serial.println(HTTPRequest);

      // print what was gathered from the API
      String payload = http.getString();
      Serial.println(payload);
    }
    // if the GET request was unsuccessful, print out the error code
    else {
      Serial.println("Error code: ");
      Serial.println(HTTPRequest);
    }

    // close HTTP connection
    http.end()
  }

  // if WiFi has been disconnected, print out that it has
  else {
    Serial.print("WiFi disconnected...");
  }
}

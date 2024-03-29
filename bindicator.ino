#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// initialise wifi password and name
const char* wiFiPassword = "your wifi password";
const char* wiFiName = "your wifi name";
const char* hostedAPIServer = "http://192.168.0.192:";
const String hostedAPIServerport = "8080";

// GPIO pin variables
const int yellowGPIOPin = 2;
const int middleRedGPIOPin = 4;
const int bottomRedGPIOPin = 5;

void APIScrape();

void setup() {
  // setup serial communication and bitrate
  Serial.begin(115200);
  Serial.println();

  // initialise pin outputs
  pinMode(yellowGPIOPin, OUTPUT)
  pinMode(middleRedGPIOPin, OUTPUT)
  pinMode(bottomRedGPIOPin, OUTPUT)
  digitalWrite(yellowGPIOPin, LOW)
  digitalWrite(middleRedGPIOPin, LOW)
  digitalWrite(bottomRedGPIOPin, LOW)

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
  std::tm tm{};
  if(tm.tm_wday == 2) {
    APIScrape(hostedAPIServer, hostedAPIServerport);
  }
}

void APIScrape(String url, String port) {
  // checks if WiFi is still connected
  if(WiFi.status() == WL_CONNECTED) {
    // create objects under WiFiClient and HTTPClient
    WiFiClient client;
    HTTPClient http;

    // concatenate API HTTP server and port together
    String APIPath = hostedAPIServer + hostedAPIServerport;
    Serial.println(APIPath);

    // connect to the API HTTP server
    http.begin(client, APIPath.c_str());

    // send HTTP GET request and wait 15 seconds for everything to work on the back end
    int HTTPRequest = http.GET();
    sleep(15000);

    // if the GET request has gone through, print out if it was successful and what was gathered from it
    if (HTTPRequest > 0) {
      // print GET request response
      Serial.print("HTTP request code: ");
      Serial.println(HTTPRequest);

      // print what was gathered from the API
      String payload = http.getString();
      Serial.println(payload);

      // outputs to the GPIO pins that turn on the corresponding lights
      if(payload == 2) {
        keepOnLight(yellowGPIOPin, bottomRedGPIOPin);
      } else {
        keepOnLight(middleRedGPIOPin, bottomRedGPIOPin)
      }
    }
    // if the GET request was unsuccessful, print out the error code
    else {
      Serial.println("Error code: ");
      Serial.println(HTTPRequest);
    }

    // close HTTP connection
    http.end();
  }

  // if WiFi has been disconnected, print out that it has
  else {
    Serial.print("WiFi disconnected...");
  }
}

// when the lights are turned on, to keep then on and to not continue web scraping,
// this function deploys a loop that continues until its wednesday
void keepOnLight(firstGPIOPin, secondGPIOPin) {
  std::tm tm{};
  while(tm.tm_wday == 2) {
    digitalWrite(firstGPIOPin, HIGH);
    digitalWrite(secondGPIOPin, HIGH);
  }
}

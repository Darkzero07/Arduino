
#include <SPI.h>
#include <Ethernet.h>
#include <HTTPClient.h>
#include "IP_config.h" // <--- Change settings for YOUR network here.

// Button
#define SOS_BTN    25      // ESP32 pin GIOP25 connected to button's pin
#define Relay      26      // ESP32 pin GIOP26 connected to relay's pin
// variables will change:
int button_state;       // the current state of button
int last_button_state;  // the previous state of button

EthernetClient client;

// // http://192.168.31.227:8000/sos 
// const int    HTTP_PORT   = 8000;
// const String HTTP_METHOD = "GET"; // or "POST"
// const char   HOST_NAME[] = "http://192.168.31.227"; // hostname of web server:
// const String PATH_NAME   = "/sos";


void setup() {
    Serial.begin(115200);
    pinMode(SOS_BTN, INPUT_PULLUP);
    pinMode(Relay,OUTPUT); 
    button_state = digitalRead(SOS_BTN);

    delay(500);
    // Use Ethernet.init(pin) to configure the CS pin.
    Ethernet.init(5);           // GPIO5 on the ESP32.

    Serial.println("Starting ETHERNET connection...");
    Ethernet.begin(eth_MAC, eth_IP, eth_DNS, eth_GW, eth_MASK);
    delay(200);
    Serial.print("Ethernet IP is: ");
    Serial.println(Ethernet.localIP());
    delay(1000);
}

void loop() {
  last_button_state = button_state;      // save the last state
  button_state = digitalRead(SOS_BTN);   // read new state
  if (last_button_state == HIGH && button_state == LOW) {
    Serial.println("The button is pressed");   
    digitalWrite(Relay,HIGH);
    delay(3000);
    digitalWrite(Relay,LOW);

       // http::get
    String url = "https://httpbin.org/get ";
    Serial.println();
    Serial.println("Get content from " + url);
    
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == 200) {
      String content = http.getString();
      Serial.println("Content ---------");
      Serial.println(content);
    } else {
      Serial.println("Fail. error code " + String(httpCode));
    }
    Serial.println("END");       
  }
}

 



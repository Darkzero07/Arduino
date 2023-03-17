
#include <SPI.h>
#include <Ethernet.h>
#include <HTTPClient.h>
#include "IP_config.h" // <--- Change settings for YOUR network here.

#define SOS_BTN    25      // ESP32 pin GIOP25 connected to button's pin
#define Relay      26      // ESP32 pin GIOP26 connected to relay's pin
// variables will change:
int button_state;       // the current state of button
int last_button_state;  // the previous state of button

EthernetClient client;

void setup() {
  // Use Ethernet.init(pin) to configure the CS pin.
  Ethernet.init(5);           // GPIO5 on the ESP32.

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  pinMode(SOS_BTN, INPUT_PULLUP);
  pinMode(Relay,OUTPUT); 
  button_state = digitalRead(SOS_BTN);
  delay(500);

  // Ethernet.begin(MAC, IP, DNS, GW, Subnet);
  // delay(1000);
  // Serial.print("Ethernet IP is: ");
  // Serial.println(Ethernet.localIP());
  // delay(500);
}

void loop() {
  //Push Button
  last_button_state = button_state;      // save the last state
  button_state = digitalRead(SOS_BTN);   // read new state
  if (last_button_state == HIGH && button_state == LOW) {
    Serial.println("The button is pressed");   
    digitalWrite(Relay,HIGH);

    //Ethernet connec
    Ethernet.begin(MAC, IP, DNS, GW, Subnet);
    delay(500);
    Serial.print("Ethernet IP is: ");
    Serial.println(Ethernet.localIP());
  
    if(client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      Serial.println("Connected to server");
      // make a HTTP request:
      // send HTTP header
      client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println(); // end HTTP header

      while(client.connected()) {
        if(client.available()){
          char c = client.read(); // read an incoming byte from the server and print it to serial monitor:
          Serial.print(c);
        }
      }
      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } 
    // if not connected:
    else {
      Serial.println("connection failed");
    } 
    // Alert time for siren 
    delay(10000);
    digitalWrite(Relay,LOW);
  }
}

 



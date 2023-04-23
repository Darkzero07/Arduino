#include <SPI.h>
#include <Ethernet.h>
#include <HTTPClient.h>
#include "IP_config.h" // <--- Change settings network here.

const int SOS_BTN  =  25;     // ESP32 pin GIOP25 connected to button's pin
const int Relay    = 26;   // ESP32 pin GIOP26 connected to relay's pin
const int DEBOUNCE_DELAY = 50;   // the debounce time; increase if the output flickers

// variables will change:
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

EthernetClient client;

void setup() {
  // Use Ethernet.init(pin) to configure the CS pin.
  Ethernet.init(5);           // GPIO5 on the ESP32.
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  pinMode(SOS_BTN, INPUT_PULLUP);
  pinMode(Relay,OUTPUT); 
}

void loop() {
  //Push Button
  currentState = digitalRead(SOS_BTN);   // read current state
  if (currentState != lastFlickerableState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }
  // whatever the reading is at, it's been there for longer than the debounce
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
  // if the button state has changed:
  if (lastSteadyState == HIGH && currentState == LOW){
    Serial.println("The button is pressed");
    digitalWrite(Relay,HIGH);
    delay(3000);
    digitalWrite(Relay,LOW);       //Alert time for siren
    //Ethernet connect
    Ethernet.begin(MAC, IP, DNS, GW, Subnet);
    delay(500);
    Serial.print("Ethernet IP is: ");
    Serial.println(Ethernet.localIP());
    //check network 
    //if connect 
    if(client.connect(HOST_NAME, HTTP_PORT)) {
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
      //disconnect & stop client
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } 
    // if not connected:
    else {
      Serial.println("connection failed");
    }
  } 
  else if (lastSteadyState == LOW && currentState == HIGH){
    // Serial.println("The button is released");
  }
  // save the the last steady state
  lastSteadyState = currentState;
  }  
}

 



#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "arduino_secrets.h" // Include the secrets file

const char SSID[] = SECRET_SSID;    // Network SSID (name)
const char PASS[] = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

// Define your variables and properties
int redValue;
int greenValue;
int blueValue;
float lightIntensity;
bool ledState;

// Callback function for ledState change
void onLedStateChange();

void initProperties() {
  // Link variables to the IoT Cloud
  ArduinoCloud.addProperty(redValue, READ, ON_CHANGE);
  ArduinoCloud.addProperty(greenValue, READ, ON_CHANGE);
  ArduinoCloud.addProperty(blueValue, READ, ON_CHANGE);
  ArduinoCloud.addProperty(lightIntensity, READ, ON_CHANGE);
  ArduinoCloud.addProperty(ledState, READWRITE, ON_CHANGE, onLedStateChange);
}

// Connection handler
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

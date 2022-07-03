#include <WiFi.h>
#include <M5Core2.h>

const char* password = "";

void setup()
{
    Serial.begin(115200);
    M5.begin();

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
    M5.Lcd.print("Setup done\n");
}

void loop()
{
    Serial.println("Scanning for open networks...");
    M5.Lcd.print("Scanning for open networks...\n");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    M5.Lcd.print("Scan done\n");
    if (n == 0) {
        Serial.println("No networks found");
        M5.Lcd.print("No networks found\n");
    } else {
        for (int i = 0; i < n; ++i) {
            //Check to see if network is open
            byte encryption = WiFi.encryptionType(i);
            if (encryption == 0) {
                Serial.print("Found open network:\n\t" + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ")\n");
                M5.Lcd.print("Found open network:\n\t" + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ")\n");
                Serial.print("Connecting to ");
                Serial.print(WiFi.SSID(i));
                WiFi.begin(WiFi.SSID(i).c_str());
                while (WiFi.status() != WL_CONNECTED) {
                    delay(500);
                    Serial.print(".");
                }
            
                Serial.println("");
                Serial.println("WiFi connected");
                Serial.println("IP address: ");
                Serial.println(WiFi.localIP());
            }
            delay(10);
        }
    }
    Serial.println("");
    M5.Lcd.println("");

    // Wait a bit before scanning again
    delay(5000);
}

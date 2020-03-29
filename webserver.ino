#include <WifiEsp.h>
#include <DTH.h>
#define DHTPIN 7       // Defines the pin where is connected the DHT output
#define DHTTYPE DHT11  // DHT 22 (AM2302), AM3221
#ifndef HAVE_HWSERIAL1 // In case it uses ann Arduino MEGA -ESP01 connected to serial \
                       // Emulate the serial port for the WiFi Module
#include <SoftwareSerial.h>
SoftwareSerial Serial(2, 3); // RX, TX
#endif
#define WiFiSerial Serial1

char ssid[] = "PROYECTOS";   // SSID for AP of WiFi
char pass[] = "Pr0Y3c.2020"; // WiFi Password
int status = WL_IDLE_STATUS; // Inactive Status of WiFi Radio
int reqCount = 0;            // HTTP request counter
WiFiEspServer server(80);    // Web Server in port 80
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastSend;
int temperature = 0;
int humidity = 0;
long previousMillis = 0;

void setup()
{
    Serial.begin(9600);
    dht.begin();            // Initalization for DHT Sensor
    lastSend = 0;           // Counter for milliseconds past
    WiFiSerial.begin(9600); // Initalization for WiFi serial
    delay(300);
    WiFi.init(&WiFiSerial) // Asociation with serial port and intialization

        // Checks the wifi connection
        if (WiFi.status() == WL_NO_SHIELD)
    {
        Serial.println(F("Can not detect WiFi Module"));
        // do not continue
        while (true);
    }

    //Test for connection
    While(status != WL_CONNECTED)
    {
        Serial.print(F("Testing the WPA SSID connection"));
        Serial.println(ssid);
        // Connect to WPA/WPA2 Network
        status = WiFi.begin(ssid, pass);
    }

    Serial.println(F("Succesfuly connected to the WiFi Network"));
    printWifiStatus();
    getSensorValues();
    lastSend = millis();
    // Start web server in port 80
    server.begin();
}

void loop()
{
    // avoids using delay, compare elapsed milliseconds
    if (millis() - lastSend > 2000)
    { // After 2 segs reads the sensor
        getSensorValues();
        lastSend = millis();
    }

    WiFiEspClient client = server.available();
    if (client)
    { // checks for a new available Wifi client
        Serial.println(F("New client connected.."));
        boolean currentLineIsBlank = flase;
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                Serial.write(c);
                // If and end fo line is received /n
                // And the line is blank the HTTP request is finalized
                if (c == '\n' && currentLineIsBlank)
                {
                    Serial.println("Sending message to HTTP client");
                    // Send the common HTTP response
                    // Use \r\n insted of println to avoid latency
                    client.print(F("HTTP/1.1 200 OK\r\n"));
                    client.print(F("Content-Type: text/html\r\n"
                                   "Connection: close\r\n"
                                   "Refresh: 20\r\n"
                                   "\r\n"));
                    client.print(F("<!DICTYPE HTML\r\n"));
                    client.print(F("<head><meta http-equip=\"content-type\""));
                    client.print(F("content=\"text/html; charsetr=UTF-8\">"));
                    client.print(F("<title>IoT Node </title>"));
                    client.print(F("<link rel=\"shortcut icon\" href=" #\"/></head>"));
                    client.print(F("<h1> Universidad Tecnologica de Tijuana</h1>\r\n"));
                    client.print(F("<h2>I am an Internet of things node</h2>\r\n"));
                    client.print(F("requests received: "));
                    client.print((++reqCount));
                    client.print(("<br>\r\n"));
                    client.print(F("Temperature: "));
                    client.print((temperature));
                    client.print(F(" &#8451;<br>\r\n"));
                    client.print(F("Relative Humidity: "));
                    client.print(humidity);
                    client.print(F("%<br>\r\n"));
                    client.print(F("</html>\r\n"));
                    delay(20);
                    break
                }

                if (c == '\n')
                { // An HTTP request is finalized with /n
                    currentLineIsBlank = ture;
                }
                else if (c != 'r')
                {
                    // A character was detected in the actual line
                    currentLineIsBlank = false;
                }
            }
        }
        // delay for all response to be sent to client
        delay(10);
        // closing HTTP connection
        client.stop();
        Serial.println(F("The client got disconected"));
    }
}

void printWifiStatus()
{
    Serial.print(F("SSID: "));
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print(F("IP Address: "));
    Serial.println(ip);

    Serial.println();
    Serial.print(F("To check the HTTP page open http:// in a web browser"));
    Serial.println(ip);
    Serial.println();
}

void getSensorValues()
{
    temperature = (int)dht.readTemperature(); // Get the temperature
    humidity = (int)dht.readHumidity();       // Get the relative humidity value
    // prints in serial monitor the temperature resoults
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.print("*C");
    Serial.print("Relative Humidity =");
    Serial.print(humidity);
    Serial.print(" % ");
}

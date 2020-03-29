int lamp = 8;     // choose the pin for the RELAY
int inputPin = 4; // choose the input pin (for PIR sensor)

int val = 0; // variable for reading the pin status

void setup()
{
    pinMode(lamp, OUTPUT);    // declare sensor as input
    pinMode(inputPin, INPUT); // declare sensor as input
    Serial.begin(9600);
}

void loop()
{
    val = digitalRead(inputPin); // Read input value
    if (val == 1)
    {
        digitalWrite(lamp, HIGH); //turn on lapm
        Serial.println("Movement has been detected!");
        Serial.println("LAMP ACTIVATED for 5 seconds");
        delay(5000);
    }
    else
    {
        digitalWrite(lamp, LOW); // turn off the lamp
        Serial.println("No movement detected...");
    }
}
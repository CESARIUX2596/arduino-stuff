// Arduino with PIR movement sensor

int led = 13;
int sensor = 2;  // Sensor pin
int state = LOW; // Movement not detected
int val = 0;     // variable for sensor state

void setup()
{
    pinMode(led, OUTPUT);   //Led as output
    pinMode(sensor, INPUT); // Sensor as input
    Serial.begin(9600);     // port Initializaiton
}

void loop()
{
    val = digitalRead(sensor); // Reads Value sensor
    if (val == HIGH)
    {                            // Is in HIGH?
        digitalWrite(led, HIGH); // Turn on LED
        delay(100);              // 100 milisecond delay

        if (state == LOW)
        {
            Serial.println("Movemnent detected!");
            state = HIGH; // Updates state variable
        }
    }

    else
    {
        digitalWrite(led, LOW); // turn of LED
        delay(200);             // 200 milisecond delay

        if (state == HIGH)
        {
            Serial.println("No movement Detected --- ");
            state = LOW;
        }
    }
}
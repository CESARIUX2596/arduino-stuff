/* Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig: Trigger (INPUT) - Pin 11
        Echo: Echo (output) - Pin 12
        GND: GBD */

int trigPin = 13; // Trigger
int echoPin = 12; // Echo
int RedLED = 5;   // red LED goes in pin 5
int GreenLED = 7; // green LED goes in pin 7

long duration, cm, inches;

void setup()
{
    //Serial Port begin
    Serial.begin(9600);
    //Define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    // The sensor triggers by a HIGH pulse of 10 or more microseconds.
    // Do a LOW pulse before to ensure a clean HIGH pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the sensors signal: HIGH  pulse which
    // duration is the time in microseconds of the emision
    // of a ping to the receptor to the echo off  of an object

    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    /*  Convert time into distance
    The speed of sound is 340 meters/second that is 
    equal to 29 microseconds per centimeter, this is why we
    divide by 29. After thar we divide by 2 because is the time that 
    the sound travels back and forth. It only requires one value but 
    both are the same, thats why we divade by 2. 
    */

    cm = (duration / 2) / 29.1;   // Divide by 29.1  or multiply by 0.0343
    inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.print();

    if (cm > safeZone)
    {
        digitalWrite(GreenLED, HIGH);
        digitalWrite(LED, LOW);
    }
    else
    {
        digitalWrite(GreenLED, LOW);
        digitalWrite(RedLED, HIGH);
    }
    delay(250);
}

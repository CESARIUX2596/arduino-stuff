/* Serial Keyboard
* -----------------
*
* Program that reproduces tones depending
* on the data coming from the serial port.
* The calculation if the tones is made 
* according to the following operation
*
* highPulse = 1/(2 * frequency) = period / 2
*
* Where the tones are described by this table:
*
* key frequency period PW (high pulse)
* c 261 Hz 3830 1915
* d 294 Hz 3400 1700
* e 329 Hz 3038 1519
* f 349 Hz 2864 1432
* g 392 Hz 2550 1275
* a 440 Hz 2272 1136
* b 493 Hz 2028 1014
* c 523 Hz 1912 956
* Any other letter makes silence from the buzzer
* (cleft) 2005 D. Cuartilles for K3
* Trad. Juan C. Carvajal. Modified J.M. Ruiz
*/
int ledPin = 13;
int sepakerOut = 9;
char names[] = {
    'c',
    'd',
    'e',
    'f',
    'g',
    'a',
    'b',
    'c',
};
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
char vla = 0;
int serByte = -1;
int statePin = LOW;
int count = 0;

void setup();
{
    pinMode(ledPin, OUTPUT);
    pinMode(speakerOUT, OUTPUT);
    Serial.Begin(9600);
}

void loop()
{
    //digitalWrite(speakerOut, LOW);
    if (serial.available())
    {
        serByte = Serial.read();
        if (serByte != -1)
        {
            val = (char)serByte;
            Serial.print("Tone: ");
            Serial.println(String(val));
            statePin = !statepin;
            digitalWrite(ledPin, statePin);
        }
    }
    for (count = 0; count <= 8; count++)
    {
        if (names[count] == val)
        {
            digitalWrite(speakerOut, HIGH);
            delayMicroseconds(tones[count]);
            digitalWrite(speakerOut, LOW);
            delayMicroseconds(tones[count]);
        }
        else
            digitalWrite(speakerOut, LOW);
    }
}

int knockPin = D0;
int lockPin = D7;
int lockState = 0;
int lockThreshold = 300;
int ledPin = D5;

void setup()
{
    Serial.begin(9600);
    Serial.println("Setting up");
    
    Spark.function("knock", knockControl);
    pinMode(knockPin, OUTPUT);
   
    Spark.variable("locked", &lockState, INT);
    pinMode(lockPin, INPUT);
   
    pinMode(ledPin, OUTPUT);
  
    // I'm ready 
    digitalWrite(ledPin, HIGH);   // Turn ON the LED pins
    delay(1000);               // Wait for 1000mS = 1 second
    digitalWrite(ledPin, LOW);    // Turn OFF the LED pins
    delay(1000);               // Wait for 1 second in off mode
    digitalWrite(ledPin, HIGH);   // Turn ON the LED pins
    delay(1000);               // Wait for 1000mS = 1 second
    digitalWrite(ledPin, LOW);    // Turn OFF the LED pins
    delay(1000);               // Wait for 1 second in off mode
}


void loop()
{
    int testState = digitalRead(lockPin);
    
    if (testState != lockState) {
        int newState = testLockState(testState);
        
        if (newState > lockState) {
            Spark.publish("lock", "1");
            digitalWrite(ledPin, HIGH);
            Serial.println("locked");
        } else if (newState < lockState) {
            Spark.publish("lock", "0");
            digitalWrite(ledPin, LOW);
            Serial.println("unlocked");
        }
        lockState = newState;
    }
}

int testLockState(int testState) {
    int start = millis();
    while (millis() - start < lockThreshold) {
        if (digitalRead(lockPin) != testState) {
            return lockState;
        }
    }
    return testState;
}

int knockControl(String command)
{
    Serial.println("knock");
    digitalWrite(ledPin, HIGH);
    digitalWrite(knockPin, HIGH);
    delay(20);
    digitalWrite(ledPin, LOW);
    digitalWrite(knockPin, LOW);
    return 1;
}
// Pins
int test_pin = 10;
int probe_pin = 8;
int noise_pin = 7;
int LED1_pin = 5;
int LED2_pin = 4;
int LED3_pin = 3;
int LED4_pin = 2;
int LED5_pin = 9;
int fail_pin = A1;
int pass_pin = 12;
int power_pin = 11;

// Variables
int mode = 0;             
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 
bool buttonState = HIGH;  
bool first_press = 0;
bool power_state = 1;

// Debouncing function to check for button press
bool isButtonPressed(int pin) {
  bool reading = digitalRead(pin);
  Serial.println(reading);

  if (reading == LOW) { 
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTime > debounceDelay) {  // Only register after debounce delay
      lastDebounceTime = currentTime;
      return true;
    }
  }
  return false;
}
 
// Keyboard Interruption Function
bool isKeyPressed() {
  if (Serial.available() > 0) {  
    
    while (Serial.available()){
        Serial.read();
    }
    return true;

  }
  return false;
}

// Turning OFF Function
bool TurnOFF() {
    power_state = digitalRead(power_pin);
    if (power_state == 1) {
        return true;
    }
    return false;
}



void setup() {
  Serial.begin(9600);

  pinMode(LED1_pin, OUTPUT);
  pinMode(LED2_pin, OUTPUT);
  pinMode(LED3_pin, OUTPUT);
  pinMode(LED4_pin, OUTPUT);
  pinMode(LED5_pin, OUTPUT);
  pinMode(fail_pin, OUTPUT);
  pinMode(pass_pin, OUTPUT);
  pinMode(probe_pin, OUTPUT);
  pinMode(noise_pin, OUTPUT);
  pinMode(power_pin, INPUT);
  pinMode(test_pin, INPUT);

  // Button setup removed as we no longer use hardware buttons
}

void loop() {

  // Turn OFF at anytime! Goes to case -1
  if (TurnOFF()) {
        Serial.println("Turning OFF");
        mode = -1; 
    }


  switch (mode) {

    // OFF Mode: all off
    case -1: 
      Serial.println("OFF");
          digitalWrite(probe_pin, LOW);
          digitalWrite(noise_pin, LOW);
          digitalWrite(LED1_pin, LOW);
          digitalWrite(LED2_pin, LOW);
          digitalWrite(LED3_pin, LOW);
          digitalWrite(LED4_pin, LOW);
          digitalWrite(LED5_pin, LOW);

          digitalWrite(fail_pin, LOW);
          digitalWrite(pass_pin, LOW);

    // Activation Mode
    case 0:
      power_state = digitalRead(power_pin);
      Serial.println(power_state);
      if(power_state == 0){
          Serial.println("hello");
          delay(800);
          // DEVICE TURNED ON: all LEDs flash on briefly
          for (int i = 0; i < 1000; i++) {
            digitalWrite(probe_pin, HIGH);
            digitalWrite(noise_pin, HIGH);

            digitalWrite(LED1_pin, HIGH);
            digitalWrite(LED2_pin, HIGH);
            digitalWrite(LED3_pin, HIGH);
            digitalWrite(LED4_pin, HIGH);
            digitalWrite(LED5_pin, HIGH);
          }
      
          delay(1000);  
          // TURN OFF ALL LIGHTS 
          digitalWrite(probe_pin, LOW);
          digitalWrite(noise_pin, LOW);
          digitalWrite(LED1_pin, LOW);
          digitalWrite(LED2_pin, LOW);
          digitalWrite(LED3_pin, LOW);
          digitalWrite(LED4_pin, LOW);
          digitalWrite(LED5_pin, LOW);

          digitalWrite(fail_pin, LOW);
          digitalWrite(pass_pin, LOW);

          mode = 1;  // entering debug state
          delay(3000); 
      } 
      break;

    // Probe Indicator Mode: goes to case 2 until key interruption
    case 1:
      // PROBE INDICATOR BLINKS
      digitalWrite(probe_pin, HIGH);
      delay(200);
      digitalWrite(probe_pin, LOW);
      delay(200);

      if (isKeyPressed()) {
        first_press = true;
        Serial.println("case 1");
        digitalWrite(probe_pin, LOW); 
        delay(200);
        mode = 2;
        
      }
      break;

    // Noise Indicator Mode: goes to case 3 unitl key interruption
    case 2:
        // PROBE INDICATOR BLINKS
      digitalWrite(noise_pin, HIGH);
      delay(200);
      digitalWrite(noise_pin, LOW);
      delay(200);

      if (isKeyPressed()) {
        Serial.println("Key pressed! Switching to mode 2.");
        digitalWrite(noise_pin, LOW); 
        delay(200);
        mode = 3;

      }
      break;

 
    // Wait-to-Start Mode: Start testing until button pushed by user
    case 3:
      Serial.println("Mode 3 activated, waiting for user's test trigger.");
      delay(100);
      // blinking circle to prompt user
      digitalWrite(LED1_pin, HIGH);
      digitalWrite(LED2_pin, HIGH);
      digitalWrite(LED3_pin, HIGH);
      digitalWrite(LED4_pin, HIGH);
      digitalWrite(LED5_pin, HIGH);



      
      // user press "play" button to start testing
      if (isButtonPressed(test_pin)) {
          digitalWrite(LED1_pin, LOW);
          digitalWrite(LED2_pin, LOW);
          digitalWrite(LED3_pin, LOW);
          digitalWrite(LED4_pin, LOW);
          digitalWrite(LED5_pin, LOW);
        mode = 4;

      }
      break;

    // Testing Mode: LEDs light up one by one
    case 4:
      Serial.println("Mode 4 activated, lighting LEDs one by one.");
      delay(200);

      // PROGRESS CIRCLE
      digitalWrite(LED1_pin, HIGH);
      delay(6000);
      digitalWrite(LED2_pin, HIGH);
      delay(6000);
      digitalWrite(LED3_pin, HIGH);
      delay(6000);
      digitalWrite(LED4_pin, HIGH);
      delay(6000);
      digitalWrite(LED5_pin, HIGH);
      delay(6000);

      Serial.println("All LEDs are lit, switching to mode 5.");
      delay(2000);
      mode = 5;
      break;

    // Result Mode: Long Press play to go back to activation mode
    case 5:
      Serial.println("Mode 5: Showing result.");
      // TURN OFF LIGHTS
      digitalWrite(LED1_pin, LOW);
      digitalWrite(LED2_pin, LOW);
      digitalWrite(LED3_pin, LOW);
      digitalWrite(LED4_pin, LOW);
      digitalWrite(LED5_pin, LOW);
      delay(1000);

      // TEST RESULT
      digitalWrite(fail_pin, HIGH);
      delay(1500);
      
      if (isKeyPressed()) {
        delay(500);
        digitalWrite(fail_pin, LOW);
        mode = 0;
      }

      break;


    default:
      // Fallback/default case: reset to mode 0 if unexpected state is reached
      Serial.println("Unknown mode, resetting to mode 0.");
      mode = 0;
      break;
  }
}

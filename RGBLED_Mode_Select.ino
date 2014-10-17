// LEDs and their pins
const int RED_LED = 9;
const int GREEN_LED = 10;
const int BLUE_LED = 11;

// The buttons and their pins
const int SELECT_BUTTON = 2;
const int reduceButton = 4;
const int increaseButton = 7;

// Button States
int modeSelect = 0;
int reduceState = 0;
int increaseState = 0;

// Color Intensity
int redVal = 0;
int greenVal = 0;
int blueVal = 0;

// SELECT_BUTTON State used for debounce() function
boolean lastSelectButton = LOW;
boolean currentSelectButton = LOW;

// Delay to use when selecting color intensity
int delayTime = 50;


void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  pinMode(SELECT_BUTTON, INPUT);
  pinMode(reduceButton, INPUT);
  pinMode(increaseButton, INPUT);
}

void loop() {
  currentSelectButton = debounce(lastSelectButton);
  if(lastSelectButton == LOW && currentSelectButton == HIGH) {
    modeSelect = modeSelect + 1;
  }
  lastSelectButton = currentSelectButton;
  
  if(modeSelect > 3) {
    modeSelect = 0;
  }
  
  setColorIntensity(modeSelect);
  setColor(modeSelect);
}

/**
 * Debouncing Function
 * Pass it the previous button state
 * and get back the current debounced button state.
 */
boolean debounce(boolean last) {
  boolean current = digitalRead(SELECT_BUTTON);
  if (last != current) {
    delay(5);
    current = digitalRead(SELECT_BUTTON);
  }
  
  return current;
}

/**
 * Set Color Function
 */
void setColor(int mode) {
  if(mode == 0 || modeSelect == 4) {
    analogWrite(RED_LED, redVal);
    analogWrite(GREEN_LED, greenVal);
    analogWrite(BLUE_LED, blueVal);
  }
  
  if(mode == 1) {
    analogWrite(RED_LED, redVal);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
  
  if(mode == 2) {
    digitalWrite(RED_LED, LOW);
    analogWrite(GREEN_LED, greenVal);
    digitalWrite(BLUE_LED, LOW);
  }
  
  if(mode == 3) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    analogWrite(BLUE_LED, blueVal);
  }
  
  delay(delayTime);
}

/**
 * Color Value Function
 */
void setColorIntensity(int mode) {
  int value;
  int LED;
  
  if(mode == 1) {
    value = redVal;
    LED = RED_LED; 
  }
  else if(mode == 2) {
    value = greenVal;
    LED = GREEN_LED; 
  }
  else if(mode == 3) {
    value = blueVal;
    LED = BLUE_LED; 
  }
  
  
  /**
   * Increase and decrease Green value
   */
  if(digitalRead(increaseButton) == HIGH && modeSelect == mode) {
    if(value >= 255) {
      value = 255;
      digitalWrite(LED, LOW);
      delay(delayTime);
    }
    else {
      value = value + 1;
    }
  }
  else if(digitalRead(reduceButton) == HIGH && modeSelect == mode) {
    if(value <= 0) {
      value = 0;
    }
    else {
      value = value - 1;
    }
  }
  
  if(mode == 1) {
    redVal = value;
  }
  else if(mode == 2) {
    greenVal = value;
  }
  else if(mode == 3) {
    blueVal = value;
  }

}


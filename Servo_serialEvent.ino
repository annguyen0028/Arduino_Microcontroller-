/*
 * Written by: An Nguyen
 * Date: 12/05/2020
 */
#include <Servo.h>

Servo myServo;
int angle0 = 110;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

String getInputSerMon();

void setup() {
  // initialize serial:
  Serial.begin(9600);
  myServo.attach(6);
  myServo.write(angle0);
  
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  

  
  String numberStr = getInputSerMon();
  if (numberStr != ""){ //only update if there is input from Serial Monitor 

    //start of servo code
    int angleIn = numberStr.toInt();
    Serial.print("angleIn: "); Serial.println(angleIn);
    myServo.write(angleIn);
    //end of servo code 

  }
  
    
  
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.println(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

String getInputSerMon(){ // return input string
  String stringReturn = "";
  if (stringComplete) {
    stringReturn = inputString;
    Serial.print("\n"); Serial.print("inputString: "); Serial.println(inputString);
  // clear the string:
  inputString = "";
  stringComplete = false; 
  }
  return stringReturn;
}

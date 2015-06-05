// Relay switch
boolean relayState = false;

// Serial interface
String buffer;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  
  // Serial connection
  Serial.begin(9600);
  
  // Print message
  Serial.println("HTB H2H Interface"); 
}

// the loop function runs over and over again forever
void loop() {
  
  if(relayState) {
  
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
  
  }
  
  // Serial Commands
  while (Serial.available()>0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      if(buffer.startsWith("id")) {
        Serial.print("id:ModuleAmp "); // device identifier
        Serial.println(Version); 
      } else if (buffer.startsWith("on")) {
        relayState = true;
        
        // Report through serial
        Serial.println(F("Relay on "));
      } else if (buffer.startsWith("off")) {
        relayState = false;
        
        // Report through serial
        Serial.println(F("Relay off "));
      } 
      else {
        Serial.println(F("Unknown cmd."));
      }
      buffer="";
    } else buffer+=c;
  }    
}

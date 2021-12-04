#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
int val;
int tempPin= 1;                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value.                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
int nImpulsi = 0;
float nMetriUnaPedalata = 5.3;
int nMetriPercorsi;
float nKmPercorsi;
int nSeconds;
float nVelocitaMedia;
float nCalories;
int co2;
float battery=100;
void setup() {   
Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    //Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}
void loop() {

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  val = analogRead(tempPin);
  float mv= (val/1024.0)*5000;
  float cel= mv/10;

                                              // "myBPM" hold this BPM value now. z
  co2 = analogRead(A0);
  
  Serial.println(co2);
 
  
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
   // If test is "true", print a message "a heartbeat happened".
                       // Print phrase "BPM: " 
   Serial.println(myBPM);  
   
  } else {
    //Serial.print("BPM: ");                        // Print phrase "BPM: " 
    Serial.println("N/A");
  }
  

  nMetriPercorsi = nImpulsi * nMetriUnaPedalata;
  nKmPercorsi = nMetriPercorsi/1000.0;
 
  nVelocitaMedia = nKmPercorsi * 3600 / nSeconds;
  nCalories = nImpulsi/10.0;
  
  nSeconds = millis() / 1000;
  nImpulsi++;
   int sensorvalue=analogRead(A0);
   float voltage=sensorvalue*(5.0/1023);
  battery = battery -(nSeconds*0.001);
  Serial.println(nVelocitaMedia);
  Serial.println(nCalories);
  Serial.println(voltage);
  Serial.println(battery);
  delay(600);

}
  
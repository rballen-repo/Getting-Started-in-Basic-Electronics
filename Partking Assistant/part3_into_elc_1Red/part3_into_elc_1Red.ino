/**************************************************************
 *  PARKING SENSOR WITH HC-SR04                               *
 *                                                            *
  *  This code receives data from the HC-SR04 proximity        *
 *  sensor, analyses  them, sends them to the serial monitor   *
 *  and produces intermittent sounds  to warn of an obstacle.  *
 **************************************************************/

//  Definition of trigger, echo, beep pins and other constants
#define trigger      2
#define  echo         3
#define beep        11
#define red_LED      8
#define beep_start 150
#define min_distance  5

// Definition of sound speed (centimetres / microsecond)
#define c 0.0343

//  Definition of the variables
long tempo;
float space;

void setup() {
  // Definition of input and output
  pinMode(trigger, OUTPUT);
  pinMode(echo,  INPUT);
  pinMode(red_LED, OUTPUT);
  pinMode(beep, OUTPUT);

  // Serial communication initialisation  (optional)
  Serial.begin(9600);
}

void loop() {
  // Before measurement,  the trigger is set to low level
  digitalWrite(trigger, LOW);
  digitalWrite(red_LED, LOW);
  delayMicroseconds(5);

  // Send one pulse (trigger goes high level for 10 microseconds)
  digitalWrite(trigger,  HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  //  Reading echo, via pulseIn, which returns the duration of the impuse (in microseconds)
  // The acquired data is then divided by 2 (forward and backward)
  tempo =  pulseIn(echo, HIGH) / 2;
  // Computation of distance in centimetres
  space  = tempo * c;

  // space is displayed in the serial monitor ([Ctrl] + [Shift]  + M)
  // approximated to the first decimal place
  Serial.println("Distanza  = " + String(space, 1) + " cm");

  // If the distance is less than one  metre
  if (space < beep_start) { 
    // Emits sounds at intervals proportional  to distance (1 m = 400 ms)
    tone(beep, 1000); 
    digitalWrite(red_LED, HIGH);
    delay(40);
    //  Below min_distance cm it emits a continuous sound
    if (space > min_distance)  {
      noTone(beep); 
      digitalWrite(red_LED, LOW);
      delay(space * 4);
    }
  } 
  
  // Waits  50 milliseconds before another measurement
  delay(50);
}

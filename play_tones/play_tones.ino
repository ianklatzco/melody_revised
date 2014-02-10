/* Based on: Melody
 * (cleft) 2005 D. Cuartielles for K3
 * Tuned edits by Ian Klatzco.
 * This example uses a piezo speaker to play melodies.  It sends
 * a square wave of the appropriate frequency to the piezo, generating
 * the corresponding tone.
 *
 * The calculation of the tones is made following the mathematical
 * operation:
 *
 *       timeHigh = period / 2 = 1 / (2 * toneFrequency)
 *
 * where the different tones are described as in the table:
 *
 * Revisions: I've found the calculated frequencies for the flats/sharps.
 * These numbers are derived from the period/2. The numbers below the table, in the actual code, have been tuned, though to a specific buzzer. I advise downloading a tuner app on your phone and testing each note you'll play.
 * These have been tuned to a 2.048 kHz frequency buzzer, specifically http://www.digikey.com/product-detail/en/CEM-1203(42)/102-1153-ND/412412
 * note 	frequency 	period 	timeHigh
 * c 	        261 Hz 	        3830 	1915 	
 * d 	        294 Hz 	        3400 	1700 	
 * e 	        329 Hz 	        3038 	1519 	
 * f 	        349 Hz 	        2864 	1432 	
 * g 	        392 Hz 	        2550 	1275 	
 * aflat (x)    415             2400    1200    
 * a 	        440 Hz 	        2272 	1136
 * bflat (z)    466 	        2100    1050    
 * b 	        493 Hz 	        2028	1014	
 * C	        523 Hz	        1912 	956
 * Dflat (y)    554             1800    900    
 * D            587             1700    850    
 * Eflat (w)    622             1600    800    
 * E            659             1500    750 
 * F            698             1400    700    
 * F# (q)       740             1350    675    
 * G            784             1280    640    
 * G# (i)       831             1200    600    
 * http://www.arduino.cc/en/Tutorial/Melody
 */
  
int speakerPin = 9;


char notes[] = "i"; // a space represents a rest
int length = sizeof(notes); // the number of notes in the below names[] array
int beats[] = { 24,1,1,1,}; // have as many of these as you have notes in the above array
int tempo = 75;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'x', 'a', 'z', 'b', 'C', 'y', 'D', 'w', 'E', 'F', 'q', 'G', 'i' };
  // c=C4, C = C5. These values have been tuned.
  int tones[] = { 1898, 1690, 1500, 1420, 1265, 1194, 1126, 1063, 1001, 947, 893, 843, 795, 749, 710, 668, 630, 594 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 18; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
    for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }
}

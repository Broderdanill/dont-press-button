#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mp3Serial(11, 10); // RX, TX (D11<-TX, D10->RX via 1k)
DFRobotDFPlayerMini mp3;

const int PIN_BUTTON = 2;

int numTracks = 0;
int lastTrack = 0;
bool lastButtonState = HIGH;

int getTrackCountWithRetry() {
  // DFPlayer kan behöva lite tid efter init innan den rapporterar counts korrekt
  for (int i = 0; i < 12; i++) {
    int c = mp3.readFileCounts();   // Totalt antal filer DFPlayer ser på SD
    if (c > 0) return c;
    delay(250);
  }
  return 0; // misslyckades
}

int pickRandomTrackAvoidRepeat(int maxTracks) {
  if (maxTracks <= 1) return 1;

  int t;
  do {
    t = random(1, maxTracks + 1);
  } while (t == lastTrack);

  lastTrack = t;
  return t;
}

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  Serial.begin(115200);
  mp3Serial.begin(9600);

  Serial.println("Initierar DFPlayer...");

  if (!mp3.begin(mp3Serial)) {
    Serial.println("DFPlayer FEL! Kontrollera VCC=5V, GND, RX/TX.");
    while (true) { delay(1000); }
  }

  Serial.println("DFPlayer OK!");
  mp3.volume(25); // 0..30

  // Seed slump
  randomSeed(analogRead(A0));

  // Läs antal spår automatiskt
  delay(800);
  numTracks = getTrackCountWithRetry();

  Serial.print("Antal filer (DFPlayer readFileCounts): ");
  Serial.println(numTracks);

  if (numTracks <= 0) {
    Serial.println("VARNING: DFPlayer rapporterar 0 filer. Kontrollera SD-kort och filnamn.");
  } else {
    Serial.println("Redo. Tryck på knappen!");
  }
}

void loop() {
  bool state = digitalRead(PIN_BUTTON);

  // Trigger på fallande flank (tryck)
  if (state == LOW && lastButtonState == HIGH) {
    if (numTracks <= 0) {
      Serial.println("Kan inte spela: 0 filer hittades.");
    } else {
      int track = pickRandomTrackAvoidRepeat(numTracks);
      Serial.print("Spelar fil #: ");
      Serial.println(track);

      // Spelar spår med index (OBS: indexeringen kan bero på hur DFPlayer sorterar)
      // Om du vill vara 100% säker på /MP3/0001.mp3-nummermatchning, använd playMp3Folder(track)
      mp3.playMp3Folder(track);
    }
    delay(250); // debounce
  }

  lastButtonState = state;
}

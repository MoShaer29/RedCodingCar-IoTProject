String kode;

void setup() {
  Serial.begin(9600);
  
  Serial2.begin(9600);
  Serial2.setTimeout(100);
}

void loop() {
  while (Serial2.available() > 0) {
    kode = Serial2.readString();
    Serial.println(kode);
  }
}

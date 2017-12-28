
int xValue = 0;
int yValue = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  xValue = analogRead(A1);
  xValue = analogRead(A2);
  Serial.print(xValue, DEC);
  Serial.print(" ");
  Serial.print(yValue, DEC);
  Serial.print("\n");
  delay(2);


}

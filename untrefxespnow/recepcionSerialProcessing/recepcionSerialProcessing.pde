import processing.serial.*;
import SerialUntref.*;
SerialUntref sUntref;
Serial serial;
int nro = 0;
float distancia = 0;
void setup() {
  size(400, 200);
  println(Serial.list());
  String portName = Serial.list()[1];
  serial = new Serial(this, portName, 115200);
  sUntref = new SerialUntref();
  textSize(24);
}
void draw() {

  while ( serial.available() > 0) {  // If data is available,
    int a = serial.read();
    if (sUntref.newDataIn(a)) {
      distancia = sUntref.getFloat(0);
      background(0);
      nro++;
      textSize(24);
      text("Nro msg: " + nro, 10, 30);
      text("distancia: " + distancia, 10, 90);
    }
  }
}

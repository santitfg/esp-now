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
  background(0);
  distancia = map((float)mouseX, 0., (float)width, 0., 5000.);
  text("distancia: " + distancia, 10, 90);

  //    text("Nro msg: " + nro, 10, 30);
  //while ( serial.available() > 0) {  // If data is available,
  //  int a = serial.read();
  //  if (sUntref.newDataIn(a)){
  //    background(0);
  //    nro++;
  //    textSize(24);
  //    text("Nro msg: " + nro, 10, 30);
  //    text("Int: " + sUntref.getInt(0), 10, 60);
  //    text("Float: " + sUntref.getFloat(1), 10, 90);
  //    text("String: " + sUntref.getString(2), 10, 120);
  // }
  //}
}

void mousePressed() {
  //println("--------------------------------------");
  nro++;
  sUntref.newPackage();
  sUntref.addFloat(distancia);
  sUntref.endPackage();

  for (int i = 0; i < sUntref.dataOutSize; i++) {
    serial.write(sUntref.getDataOut(i));
  }
}

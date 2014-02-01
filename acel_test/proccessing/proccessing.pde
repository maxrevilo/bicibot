// Graphing sketch


// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 18 Jan 2008
// by Tom Igoe
// This example code is in the public domain.

import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph

void setup () {
  // set the window size:
  size(640, 360, P3D);
  frameRate(120);

  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[1], 115200);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  noStroke();
  // set inital background:
  background(0);
}

float xAxis = 0;
float yAxis = 0;
float zAxis = 0;

float xAxisO = 0;
float yAxisO = 0;
float zAxisO = 0;

void draw () {
  background(0);
  
  ambientLight(120, 120, 126);
  
  // Orange point light on the right
  pointLight(150, 100, 0, // Color
             200, -150, 0); // Position

  // Blue directional light from the left
  directionalLight(0, 102, 255, // Color
                   1, 0, 0); // The x-, y-, z-axis direction

  // Yellow spotlight from the front
  spotLight(255, 255, 109, // Color
            0, 40, 200, // Position
            0, -0.5, -0.5, // Direction
            PI / 2, 2); // Angle, concentration
            
  tilt();
}

void tilt() {
  translate(width / 2, height / 2);
  
  xAxisO = xAxisO * 0.8 + xAxis * 0.2;
  yAxisO = yAxisO * 0.8 + yAxis * 0.2;
  zAxisO = zAxisO * 0.8 + zAxis * 0.2;
  
  float pitch = atan(xAxisO/sqrt(pow(yAxisO,2) + pow(zAxisO,2)));
  float roll = atan(yAxisO/sqrt(pow(xAxisO,2) + pow(zAxisO,2)));
  
  
  rotateX(roll + PI/2);
  rotateY(pitch);
  rotateZ(PI/2);
  
  box(150);
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    /*float inByte = float(inString); 
    inByte = map(inByte, -500, 500, 0, height);

    // draw the line:
    stroke(127, 34, 255);
    line(xPos, height, xPos, height - inByte);

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } 
    else {
      // increment the horizontal position:
      xPos++;
    }*/
    println(inString);
    String sensors_raw[] = split(inString, ',');
    if(sensors_raw != null && sensors_raw.length == 3) {
      int sensors[] = int(sensors_raw);
      xAxis = sensors[0] / 100.0;
      yAxis = sensors[1] / 100.0;
      zAxis = sensors[2] / 100.0;
    }
  }
}


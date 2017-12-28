//Import the P5 OSC library
import oscP5.*;
import netP5.*;
import processing.serial.*;

//Set the pipeline mode (CLASSIFICATION_MODE, REGRESSION_MODE or TIMESERIES_MODE), the number of inputs and the number of outputs
final int pipelineMode = GRT.TIMESERIES_MODE;
final int numInputs = 3;
final int numOutputs = 1;

//Set the OSC ports used for the GRT GUI and for Processing
final int guiPort = 5000;
final int processingPort = 5001;

//Create a new GRT instance, this will initialize everything for us and send the setup message to the GRT GUI
GRT grt = new GRT( pipelineMode, numInputs, numOutputs, "127.0.0.1", guiPort, processingPort, true );

//Create some global variables to hold our data
float[] data = new float[ numInputs ];
PFont font;
Serial mySerial;
String inBuffer;
String[] splitted;

void setup() {
  size(600,600);
  frameRate(30);
  //Load the font
  font = loadFont("SansSerif-48.vlw");
  mySerial = new Serial(this, "/dev/cu.RNBT-7BD8-RNI-SPP", 115200);
}

void draw() {
  background(0);  
  
  if( !grt.getInitialized() ){
    background(255,0,0);  
    println("WARNING: GRT Not Initalized. You need to call the setup function!");
    return;
  }
  
  //Draw the info text
  grt.drawInfoText(20,20);

  while (mySerial.available() > 0) {
    inBuffer = mySerial.readStringUntil(10);   
    if (inBuffer != null) {
      splitted = split(inBuffer, ',');
      if(splitted.length < 3) continue;
      data[0] = float(splitted[0]);
      data[1] = float(splitted[1]);
      data[2] = float(splitted[2]);
      grt.sendData(data);
    }
  }

}
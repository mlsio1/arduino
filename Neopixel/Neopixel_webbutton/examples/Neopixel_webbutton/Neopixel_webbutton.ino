/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 4 Sep 2010
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_NeoPixel.h>
#include <colorcodes.h>
#define NUM_LIGHTS 4 //Number off connected leds 
#define PIN 6 //Pin 6 for Data

//int kleura=0;
//int kleurb=0;
//int kleurc=0;
//int color=0;
//int message=0;
//int thisChar=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LIGHTS, PIN, NEO_GRB + NEO_KHZ800);

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 1, 177 }; // ip in lan
byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask




// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
String readString; 


void setup()
{

  pinMode(4, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  //enable serial data print 
  Serial.begin(9600); 
  Serial.println("Neopixel"); // so I can keep track of what is loaded
  Serial.println(Ethernet.localIP());
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String buffer = "";  //  Declare the buffer variable

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);  //  Send every character read to serial port 
        buffer+=c;        //  Assign to the buffer

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Arduino NeoPixel Controlpage</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>Arduino NeoPixel Controlpage</H1>");
          
          client.println("<br />");
          
          // 2<-- Create a form
          client.print("<FORM action=\"http://192.168.1.177/\" >");
          client.print("<P> <INPUT type=\"radio\" name=\"color\" value=\"OFF\">OFF");
          client.print("<P> <INPUT type=\"radio\" name=\"color\" value=\"white\">White");
          client.print("<P> <INPUT type=\"radio\" name=\"color\" value=\"blue\">Blue");
          client.print("<P> <INPUT type=\"radio\" name=\"color\" value=\"rainbow\">Rainbow");
          
          client.print("<P> <INPUT type=\"submit\" value=\"Submit\"> </FORM>");
            
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          buffer="";       //  Clear the buffer at end of line
        } else if (c == '\r') {            
          
          if(buffer.indexOf("GET /?color=OFF")>=0)
           colorSet(strip.Color(black), 200); 
       
 
           if(buffer.indexOf("GET /?color=rainbow")>=0)
            rainbowCycle(20);
 
 
 if(buffer.indexOf("GET	/?color=black")>=0)
            colorSet(strip.Color(black),0);
if(buffer.indexOf("GET /?color=blue")>=0)
            colorSet(strip.Color(blue),0);
if(buffer.indexOf("GET /?color=cyan")>=0)
            colorSet(strip.Color(cyan),0);
if(buffer.indexOf("GET /?color=gray")>=0)
            colorSet(strip.Color(gray),0);
if(buffer.indexOf("GET /?color=green")>=0)
            colorSet(strip.Color(green),0);
if(buffer.indexOf("GET /?color=lime")>=0)
            colorSet(strip.Color(lime),	0);
if(buffer.indexOf("GET /?color=magenta")>=0)
            colorSet(strip.Color(magenta),0);
if(buffer.indexOf("GET /?color=maroon")>=0)
            colorSet(strip.Color(maroon),0);
if(buffer.indexOf("GET /?color=navy")>=0)
            colorSet(strip.Color(navy),0);
if(buffer.indexOf("GET /?color=olive")>=0)
            colorSet(strip.Color(olive),0);
if(buffer.indexOf("GET /?color=purple")>=0)
            colorSet(strip.Color(purple),0);
if(buffer.indexOf("GET /?color=red")>=0)
            colorSet(strip.Color(red),	0);
if(buffer.indexOf("GET /?color=silver")>=0)
            colorSet(strip.Color(silver),0);
if(buffer.indexOf("GET /?color=teal")>=0)
            colorSet(strip.Color(teal),0);
if(buffer.indexOf("GET /?color=white")>=0)
            colorSet(strip.Color(white),0);
if(buffer.indexOf("GET /?color=yellow")>=0)
            colorSet(strip.Color(yellow),0);
if(buffer.indexOf("GET /?color=oranje")>=0)
            colorSet(strip.Color(oranje),0);
 
 
 
 
 
 
          }
        else {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}



// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


// Fill the dots one after the other with a color
void colorSet(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


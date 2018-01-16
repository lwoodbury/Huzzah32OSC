
/* Send OSC to a computer on the local network using the Huzzah32 and Wifi
 *  
 *  I'm sure I have borrowed from WiFi and OSC library examples, can't find exact sources to credit

   Luke Woodbury 9th January 2018
*/


//Wifi and OSC stuff
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "Your Network Name";          // your network SSID (name)
char pass[] = "yourpassword";                    // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(10, 133, 112, 252);     // remote IP of your computer
const unsigned int outPort = 8000;          // remote port to receive OSC
const unsigned int localPort = 9000;        // local port to listen for OSC packets (actually not used for sending)

#define LEDpin 13


void setup() {

  pinMode(LEDpin, OUTPUT);
  
  Serial.begin(115200);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  //Serial.println(Udp.localPort());

}
                      
void loop() {                     
  float fnum = 3.14;
  
  OSCMessage msg("/pongo");
  msg.add(3);
  msg.add("hello");
  msg.add(fnum);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();

  digitalWrite(LEDpin, HIGH);  
  delay(500);
  digitalWrite(LEDpin, LOW);  
  delay(500);
}


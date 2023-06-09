
#include "FirebaseESP8266.h"
#include <Servo.h>

#define FIREBASE_HOST "smartrailgate-default-rtdb.firebaseio.com"  
#define FIREBASE_AUTH "0ApBbX7VXh7lRZkHcIpSvzGwSbKnfP9jG4CuLtws "

#define WIFI_SSID "PAPPURAJ"     
#define WIFI_PASSWORD "12345678" 


FirebaseData firebaseData;
Servo myservo;
int limit=10;




void setup() {
  
  myservo.attach(D3);
  pinMode(D5,OUTPUT);
  pinMode(D6,INPUT);
  Serial.begin(9600); 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(D4,0);
    Serial.print(".");
    delay(200);
    digitalWrite(D4,1);
    Serial.print(".");
    delay(200);
    
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  bool trainDetect=!digitalRead(D6);
  servo(trainDetect);
  digitalWrite(D5,trainDetect);
  if(trainDetect)
    Firebase.setString(firebaseData, "/Data/Train","1" );
 
  for(int timer=0;trainDetect && timer<limit;timer++,delay(1000))
      if(timer+1==limit)
        Firebase.setString(firebaseData, "/Data/Train","0" );
  
  
  

  
}


void servo(bool is) {
  is ? myservo.write(50) : myservo.write(120);

}

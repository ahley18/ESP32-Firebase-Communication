#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "y90"
#define WIFI_PASSWORD "clarence1818"
#define API_KEY "AIzaSyBDNi0JPzWYoOqwBXGMKmLv_2EQPGyjwBk"
#define DATABASE_URL "https://electrifai-ecothon-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int ldrData = 0;
String inputString = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the API key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}


void loop() {
  inputString = Serial.readStringUntil('\n');
  if (inputString ==""){
    //do nothing 
  }
  else{
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 10 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.setString(&fbdo, "Data/ESP2", inputString)) {
      Serial.println();
      Serial.println("You: " + inputString);
    } else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }
  
  }
}

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 10 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    String downloadedString;
    if (Firebase.RTDB.getString(&fbdo, "Data/ESP1")) {
      downloadedString = fbdo.stringData();
      if (downloadedString == " "){
        //do nothing
      }
      else{
        Serial.println();
        Serial.print("User: ");
        Serial.println(downloadedString);
        delay(1);
        Firebase.RTDB.setString(&fbdo, "Data/ESP1", " ");
        
      }
    } 
    else {
      Serial.println("FAILED to get data: " + fbdo.errorReason());
    }
  } 
}

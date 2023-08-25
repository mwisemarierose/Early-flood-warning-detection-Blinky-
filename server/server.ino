#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "I_Am_Blessed";
const char* password = "Innovate@";
const char* serverName = "http://192.168.137.1/post-esp-data.php";

int sensorValue1,sensorValue2,sensorValue3;
String apiKeyValue = "tPmAT5Ab3j7F9";

String Group_name = "Group2";


void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI…");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
}


void loop() {
  sensorValue1=random(0,100);
  sensorValue2=random(0,100);
  sensorValue3=random(0,100);
  //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
         
      http.begin(serverName);
      
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
        // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&group=" + Group_name+ "&value1=" + String(sensorValue1)
                          + "&value2=" + String(sensorValue3) + "&value3=" + String(sensorValue3) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
               
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(20000);  
}

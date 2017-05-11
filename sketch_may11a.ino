
#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information
                           // as described in the footer comment below

const String GMAIL_USER_NAME = "thatssodracula@gmail.com";

const String GMAIL_APP_PASSWORD = "Aaron1998";

const String TO_EMAIL_ADDRESS = "S00171335@mail.itsligo.ie";

boolean attempted = false; 

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;  
const int ledPin = 3;
const int knockSensor = A0;
const int threshold = 750;
const int piezoPin = 2;

int sensorReading = 0;
int ledState = LOW;
int piezoState = LOW;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  delay(4000);
  while(!Serial);
  
  Bridge.begin();    
}

void loop() {

  sensorReading = 0;
  
   if (!attempted) {

    Serial.println("Running SendAnEmail...");
  
    TembooChoreo SendEmailChoreo;

    // invoke the Temboo client
    // NOTE that the client must be reinvoked, and repopulated with
    // appropriate arguments, each time its run() method is called.
    SendEmailChoreo.begin();
    
    // set Temboo account credentials
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

    // identify the Temboo Library choreo to run (Google > Gmail > SendEmail)
    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
 

    // set the required choreo inputs
    // see https://www.temboo.com/library/Library/Google/Gmail/SendEmail/ 
    // for complete details about the inputs for this Choreo

    // the first input is your Gmail email address.     
    SendEmailChoreo.addInput("thatssodracula@gmail.com", GMAIL_USER_NAME );
    // next is your application specific password
    SendEmailChoreo.addInput("Aaron1998", GMAIL_APP_PASSWORD);
    // who to send the email to
    SendEmailChoreo.addInput("S00171335@mail.itsligo.ie", TO_EMAIL_ADDRESS);
    // then a subject line
    SendEmailChoreo.addInput("Subject", "ALERT: Cupboard opened");

     // next comes the message body, the main content of the email   
    SendEmailChoreo.addInput("MessageBody", "Hey! The Cupboard has been opened, someone's eating your food");

    // tell the Choreo to run and wait for the results. The 
    // return code (returnCode) will tell us whether the Temboo client 
    // was able to send our request to the Temboo servers
    unsigned int returnCode = SendEmailChoreo.run();

    // a return code of zero (0) means everything worked
    if (returnCode == 0) {
        Serial.println("Success! Email sent!");
    } else {
      // a non-zero return code means there was an error
      // read and print the error message
      while (SendEmailChoreo.available()) {
        char c = SendEmailChoreo.read();
        Serial.print(c);
      }
    } 
    SendEmailChoreo.close();
    
    // set the flag showing we've tried
    attempted = true;
  }


  sensorReading = analogRead(knockSensor);

  if (sensorReading >= threshold) {

    ledState = !ledState;
    
    Serial.println(ledState);

    digitalWrite(ledPin, ledState);

    tone(piezoPin,1000);
    delay(25);
    noTone(piezoPin);

    Serial.println(sensorReading);
    }
  else (sensorReading < threshold) ;
    {
    !ledState;

    
    Serial.println(ledState);
    }
  delay(100); 
 }
  

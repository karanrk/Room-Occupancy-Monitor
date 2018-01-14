
#define PIN1 D6 //desired output pin
#define PIN2 D2 //input pin to read PIR sensor
int state=0;  //keep track of status
String data = String(20); // data to be sent

void setup(){
	
	pinMode(PIN1,OUTPUT);
	pinMode(PIN2,INPUT);
	digitalWrite(PIN1,LOW);  //set the LED to LOW initially
// Subscribe to the integration response event
  	Particle.subscribe("hook-response/Google-spreadsheet-update", myHandler, MY_DEVICES);
}


	

void loop(){

//Get the input of PIR

int value = digitalRead(PIN2);

if (value==1){
	if (state==0){
	//change state if PIR detects motion and previous state is 0
		state=1;
		
	digitalWrite(PIN1,HIGH);
	// Send the status as occupied to Google cloud using webhook integrator
	myPublish("ROOM-420","Occupied");
		}
	}

	else{
		//send the status as not occupied to Google cloud using webhook integrator

		if (state == 1){
				state=0;
				digitalWrite(PIN1,LOW);
				myPublish("ROOM-420","Not Occupied");

		}
	}

}

//Function to trigger the push from cloud using webhooks
void myPublish(String room,String state){
	Particle.publish("Google-spreadsheet-update",state,PRIVATE);
}


//Handler
void myHandler(const char *event, const char *data) {
  // Handle the integration response if any.
}



	




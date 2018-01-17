//Room Occupancy Monitor code

#define PIN1 D3 //desired output pin
#define PIN2 D5 //input pin to read PIR sensor
int state=LOW; //keep track of status
int value=0;   //variable to hold input of PIR
bool initialDelay=false;

void setup(){
	
	pinMode(PIN1,OUTPUT);
	pinMode(PIN2,INPUT);
	digitalWrite(PIN1,LOW);  //set the LED to LOW initially
// Subscribe to the integration response event
  	Particle.subscribe("hook-response/Google-spreadsheet-update", myHandler, MY_DEVICES);
}


	

void loop(){

//Initial delay before capturing the PIR data
if (initialDelay==false){
	delay(10000);
	initialDelay=true;
}

//Get the input of PIR
value = digitalRead(PIN2);

if (value == HIGH){
	if (state == LOW){
	//change state if PIR detects motion and previous state is 0
		state=1;
		
	digitalWrite(PIN1,HIGH);
	// Send the status as occupied to Google cloud using webhook integrator
	myPublish("ROOM-420","Occupied");
		}
	}

	else{
		//send the status as not occupied to Google cloud using webhook integrator

		if (state == HIGH){
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



	




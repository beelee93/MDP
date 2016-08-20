 //This is just for testing the serial connection
 
 void setup() {
  // put your setup code here, to run once:
   pinMode(13,OUTPUT);
   Serial.begin(9600);
} 

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
      light(Serial.read()-'0');
    }
    delay(500);
}

void light(int n){
  if(n == 1){
    digitalWrite(13,HIGH);
  }
  if(n==0){
    digitalWrite(13,LOW);
  }
  }

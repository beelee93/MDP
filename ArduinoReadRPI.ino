 //This is just for testing the serial connection
 
 void setup() {
  // put your setup code here, to run once:
   pinMode(13,OUTPUT);
   Serial.begin(9600);
} 

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
      int n = Serial.read()-'0';
      int v1 = Serial.read()-'0';
      int v2 = Serial.read()-'0';
      int v3 = Serial.read()-'0';
      go(n,v1*100+v2*10+v3);
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

void go(int n,int v){
 if(n == 0){
  //gostright by v distance
 }
 if(n == 1){
  //goback by v distance
 }
 if(n == 2){
  //rotate counter-clockwise by v degree
 }
 if(n == 3){
  //rotate clockwise by v degree
 }
}

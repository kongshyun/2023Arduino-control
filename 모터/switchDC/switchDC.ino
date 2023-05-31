
void setup(){
    
   //5V DC
   pinMode(7,OUTPUT);//IN1
   pinMode(8,OUTPUT);//IN2
   pinMode(6,OUTPUT);//ENA
    
}

void loop(){

   //정회전(시계방향)
   digitalWrite(7,HIGH);
   digitalWrite(8,LOW);
   analogWrite(6,255/2);
   delay(3000);

   //정지 (7번핀에 HIGH를 주어도 PWM 핀에 값을 0을 주었기 때문에 정지함)
   digitalWrite(7,HIGH);
   digitalWrite(8,LOW);
   analogWrite(6,60);
   delay(3000);

   //정지 (7번핀에 HIGH를 주어도 PWM 핀에 값을 0을 주었기 때문에 정지함)
   digitalWrite(7,HIGH);
   digitalWrite(8,LOW);
   analogWrite(6,0);
   delay(3000);
}
        
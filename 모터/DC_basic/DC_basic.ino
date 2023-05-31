//DC모터 회전 정지 반복

void setup(){

   //5V DC
   pinMode(12,OUTPUT);//IN1
   pinMode(13,OUTPUT);//IN2
   pinMode(11,OUTPUT);//ENA
}

void loop(){

   //정회전(시계방향)
   digitalWrite(13,HIGH);
   digitalWrite(12,LOW);
   analogWrite(11,255);
   delay(3000);

   //정지 (7번핀에 HIGH를 주어도 PWM 핀에 값을 0을 주었기 때문에 정지함)
   digitalWrite(13,HIGH);
   digitalWrite(12,LOW);
   analogWrite(11,150);
   delay(3000);

   //정지 (7번핀에 HIGH를 주어도 PWM 핀에 값을 0을 주었기 때문에 정지함)
   digitalWrite(13,HIGH);
   digitalWrite(12,LOW);
   analogWrite(11,0);
   delay(3000);
}
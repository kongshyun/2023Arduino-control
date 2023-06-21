//DC모터 회전 정지 반복
/*
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
}*/

// 3번과 4번 핀은 모터 제어에 관한 핀
int IN1Pin = 6;
int IN2Pin = 7;

// 5번핀은 모터의 힘을 설정해주는 핀
int ENPin = 5;

void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT); // 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(ENPin, 100); //5번 핀에 255의 최대 힘을 설정한다. 
}

void loop() {    
  //Go : 핀 3, 핀 4 에 신호를 다르게 하면 전진
  digitalWrite(IN1Pin, HIGH); 
  digitalWrite(IN2Pin, LOW);
  delay(5000);//5sec 

  //Back : 핀 3, 핀 4 에 신호를 다르게 하면 후진
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);  
  delay(5000);//5sec
  
  //Brake (Stop) 핀 3, 4에 똑같이 High를 주거나 Low을 주면 은 멈춘다.
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, HIGH);
  delay(5000);//1sec
}
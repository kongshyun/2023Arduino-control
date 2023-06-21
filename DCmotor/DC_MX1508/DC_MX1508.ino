// 모터 핀 정의
const int D1_IN1 = 7;  // L9110S 드라이버 IN1 핀
const int D1_IN2 = 6;  // L9110S 드라이버 IN2 핀
const int D1_IN3 = 5;  // L9110S 드라이버 IN1 핀
const int D1_IN4 = 4;  // L9110S 드라이버 IN2 핀

//모터핀정의
const int D2_IN1 = 13;  // L9110S 드라이버 IN1 핀
const int D2_IN2 = 12;  // L9110S 드라이버 IN2 핀
const int D2_IN3 = 11;  // L9110S 드라이버 IN1 핀
const int D2_IN4 = 10;  // L9110S 드라이버 IN2 핀

void setup() {
  // 모터 핀을 출력으로 설정
  pinMode(D1_IN1, OUTPUT);
  pinMode(D1_IN2, OUTPUT);
  pinMode(D1_IN3, OUTPUT);
  pinMode(D1_IN4, OUTPUT);

  pinMode(D2_IN1, OUTPUT);
  pinMode(D2_IN2, OUTPUT);
  pinMode(D2_IN3, OUTPUT);
  pinMode(D2_IN4, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello");
}

int maxSpeed=255;//속도 130아래로 안떨어짐
char state;

void loop() {

  if(Serial.available()){
    state=Serial.read();

    if(state=='a'){
      Serial.println(state);
      analogWrite(D1_IN2, 60);  // IN1 핀에 PWM 신호로 속도 설정
      analogWrite(D1_IN1, LOW);  // IN2 핀 LOW
    }
    
    else if(state=='d'){
      Serial.println(state);
      analogWrite(D1_IN2, LOW);  // IN1 핀에 PWM 신호로 속도 설정
      analogWrite(D1_IN1, 60);  // IN2 핀 LOW
    }
    else if(state=='s'){
      Serial.println(state);
      analogWrite(D1_IN1, LOW);  // IN1 핀에 PWM 신호로 속도 설정
      digitalWrite(D1_IN2, LOW);  // IN2 핀 LOW
    }
  }
}

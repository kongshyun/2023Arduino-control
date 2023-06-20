// 모터 핀 설정
const int enablePin = 5;   // L298N 드라이버의 ENA 핀에 연결
const int in1Pin = 6;      // L298N 드라이버의 IN1 핀에 연결
const int in2Pin = 7;      // L298N 드라이버의 IN2 핀에 연결

void setup() {
  // 핀 모드 설정
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  
  // 초기 설정
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop(){
  char state;

  if (Serial.available()){
    state=Serial.read();
    if(state=='a'){
      Serial.println("a");
      forward(500);
    }
    else if(state=='s'){
      stop();
      Serial.println("s");
    }
    else if(state=='d'){
      backward(200);
      Serial.println("d");
    }
  }
}

// 전진 함수
void forward(int RPM) {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enablePin, RPM); // 모터 속도 설정 (0~255 사이의 값)
}

// 후진 함수
void backward(int RPM) {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enablePin, RPM); // 모터 속도 설정 (0~255 사이의 값)
}

// 정지 함수
void stop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enablePin, 0); // 모터 정지
}

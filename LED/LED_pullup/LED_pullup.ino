//pullup 스위치 
//스위치를 누르면 LED OFF, 안누르면 ON
/*
void setup(){
    pinMode(11,OUTPUT);
    pinMode(7,INPUT);
    Serial.begin(9600);
}

void loop(){
    int button=digitalRead(7);
    Serial.println(button);

    if (button==HIGH){
        digitalWrite(11,HIGH);
    }
    else{
        digitalWrite(11,LOW);
    }
}*/

void setup() {
    pinMode(2,INPUT_PULLUP); // 2번을 입력으로
    pinMode(13,OUTPUT);
}
void loop() {
    int sw=digitalRead(2); // 스위치 상태를 읽기
    if (!sw)
    digitalWrite(13,HIGH);
    else
    digitalWrite(13,LOW);
}

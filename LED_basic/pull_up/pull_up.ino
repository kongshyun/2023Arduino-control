//스위치가 열려있으면 1을 출력, 닫혀있으면 0을 출력
//풀업스위치

int pushButton =3;

void setup(){
    Serial.begin(9600);
    pinMode(pushButton,INPUT);
}

void loop(){
    int buttonState = digitalRead(pushButton);
    Serial.println(buttonState);
    delay(1);
}
//LED 4개 스위치 2개로 제어하기

void setup(){
    pinMode(6,INPUT);pinMode(7,INPUT);//스위치핀
    pinMode(9,OUTPUT);pinMode(10,OUTPUT);//LED핀
    pinMode(11,OUTPUT);pinMode(12,OUTPUT);
    Serial.begin(9600);
}

void loop(){
    int buttonL=digitalRead(7);
    int buttonR=digitalRead(6);

    Serial.print("Left Button: ");Serial.println(buttonL);
    Serial.print("Right Button: ");Serial.println(buttonR);
    Serial.println();

    //왼쪽스위치
    if (buttonL==0 & buttonR ==0){
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        digitalWrite(12,LOW);
    }
    else if (buttonL==1 & buttonR==1){
        digitalWrite(9,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(11,HIGH);
        digitalWrite(12,HIGH);
    }
    else if (buttonL==1 & buttonR==0){
        digitalWrite(9,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(11,LOW);
        digitalWrite(12,LOW);
    }
    //오른쪽 스위치만 누르면 9번핀 LED가 점점 밝아진다.
    else if (buttonL==0 & buttonR==1){
        for (int i=0;i<256;i++){
            analogWrite(9,i);
            delay(10);
        }
    }
}
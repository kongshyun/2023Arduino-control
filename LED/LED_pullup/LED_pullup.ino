//pullup 스위치 
//스위치를 누르면 LED OFF, 안누르면 ON

void setup(){
    pinMode(13,OUTPUT);
    pinMode(2,INPUT);
    Serial.begin(9600);
}

void loop(){
    int button=digitalRead(2);
    Serial.println(button);

    if (button==HIGH){
        digitalWrite(13,HIGH);
    }
    else{
        digitalWrite(13,LOW);
    }
}
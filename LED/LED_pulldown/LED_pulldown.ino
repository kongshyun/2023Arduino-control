//pulldown 스위치 
//스위치를 누르면 LED ON, 안누르면 OFF
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
}
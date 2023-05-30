//왼쪽스위치 한번 LED OFF/ reset
//오른쪽스위치 누르면 누를때마다 LED 하나씩 켜짐 


int number=0;//오른쪽스위치 입력 횟수

void setup(){
    pinMode(6,INPUT);pinMode(7,INPUT);//스위치핀
    pinMode(9,OUTPUT);pinMode(10,OUTPUT);//LED핀
    pinMode(11,OUTPUT);pinMode(12,OUTPUT);
    Serial.begin(9600);

    //초기에 모두 OFF
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);

    
}

void loop(){
    int buttonL=digitalRead(7);
    int buttonR=digitalRead(6);

    //Serial.print("Left Button: ");Serial.println(buttonL);
    //Serial.print("Right Button: ");Serial.println(buttonR);
    Serial.println();

    //왼쪽스위치
    if (buttonL==1 & buttonR ==0){
        number=0;
        digitalWrite(9,LOW);digitalWrite(11,LOW);
        digitalWrite(12,LOW);digitalWrite(10,LOW);
    }
    else if(buttonL==0 & buttonR ==1){
        
        if(number==0) {
            digitalWrite(9,HIGH);
            Serial.print("number :  ");Serial.println(number);
            delay(1000);
        }
        else if (number==1) {
            digitalWrite(10,HIGH);
            Serial.print("number :  ");Serial.println(number);
            delay(1000);
            }
        else if (number==2) {
            digitalWrite(11,HIGH);
            Serial.print("number :  ");
            Serial.println(number);
            delay(1000);
        }
        else if (number==3) {
            digitalWrite(12,HIGH);
            Serial.print("number :  ");
            Serial.println(number);
            delay(1000);
        }
        else if (number==4){
            digitalWrite(9,LOW);
            digitalWrite(10,LOW);
            digitalWrite(11,LOW);
            digitalWrite(12,LOW);
            Serial.print("number :  ");Serial.println(number);
            delay(2000);
        }
        Serial.println(number);
        number++;
        delay(1000);
    }
    
    
   
}

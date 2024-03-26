int inpin=6;
int val;

void setup(){
  Serial.begin(9600);
  pinMode(inpin,INPUT_PULLUP);
  //pinMode(inpin,OUTPUT);
  digitalWrite(7,HIGH);
  delay(500);
  digitalWrite(7,LOW);
  delay(500);
}

void loop(){
  val=digitalRead(inpin);
  Serial.println(val);

  if (val==1){//포토센서 값이 1이면 물체 없는것!
    digitalWrite(7,HIGH);
  }
  else {
    digitalWrite(7,LOW);//포토센서 값이 0이면 물체 있는것
  }
  delay(100); // 필요에 따라 대기 시간을 조정할 수 있습니다.
}
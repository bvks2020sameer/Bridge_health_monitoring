float sensor1;
float sensor2;
float temp1 = 100;
float comp1;
float comp2;


class filter{

  private: int ptr1[0],ptr2[10];
           int count1 = 0 ,count2 = 0;
           friend void update(int num);

  public: filter();
          float avg1();
          float avg2();
          void update(int num,float val);


};


   filter :: filter(){
      int i;
      for(i=0;i<10;i++) {
        ptr1[i] = 0 ;
      }

      for(i=0;i<10;i++) {
        ptr2[i] = 0 ;
      }

  }


  void filter :: update(int num,float val){
    
    if(num == 0){
          ptr1[count1] = val;
          count1 ++;
    }

    else {
      *(ptr2+(count2%10)) = val;
          count2 ++;
    }
  }

  float filter::avg1(){

    int i;
    float sum=0;
    for(i=0;i<10;i++){
        sum += *(ptr1+i);
    }

    return sum/10;

  }


float filter::avg2(){

  int i;
  float sum=0;
  for(i=0;i<10;i++){
      sum += *(ptr2+i);
  }

  return sum/10;

}



void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  sensor1 = analogRead(A0);
  sensor2 = analogRead(A1);
  filter f;

  if( (comp1+comp2)/2 > temp1){
    while(1){
      digitalWrite(13, 1);
      f.update(1, sensor1);
      f.update(2, sensor2);
      comp1 = f.avg1();
      comp2 = f.avg2();
      Serial.print(0);
      Serial.print(",");
      Serial.println((comp1+comp2)/2);
    }
  }
  
  f.update(1, sensor1);
  f.update(2, sensor2);
  comp1 = f.avg1();
  comp2 = f.avg2();
  Serial.print(0);
  Serial.print(",");
  Serial.println((comp1+comp2)/2);


  delay(50);
}

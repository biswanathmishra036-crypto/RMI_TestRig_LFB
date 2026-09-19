unsigned long old_time1=0;
unsigned long old_time1=0;
unsigned long old_time2=0;
unsigned long old_time3=0;
int Kp,Ki,Kd=0;
int cal_flag=0;
int a7,a2,a3,a4,a5,a6=0;
int curr_signal=0;
int base_signal=0;
int s2[2]=[1023,0];
int s3[2]=[0,0];
int s4[2]=[0,0];
int s5[2]=[0,0];
int s6[2]=[0,0];
int s7[2]=[0,0];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long curr_time0=millis();
  unsigned long curr_time1=millis();
  unsigned long curr_time2=millis();
  unsigned long curr_time3=millis();

  while(cal_flag==0){
    //calibration routine: 10Hz
    a2=analogRead(A0);
    a3=analogRead(A1);
    a4=analogRead(A2);
    a5=analogRead(A3);
    a6=analogRead(A4);
    a7=analogRead(A5);

    // move motor forward by x, stand for 2 sec, note value at white, save in arr[0], 
    // move back by 2x note value, stay 2 sec, not valye at black, save in arr[1].
    //Repeat the process 5 to 6 times. 

  }


}

//important shii to code in
const int array_pin[6]={A0,A1,A2,A3,A4,A5};
int ir_val[6];
int mapd_val[6];
unsigned long old_time0=0;
unsigned long old_time1=0;
unsigned long old_time2=0;
int Kp=0,Ki=0,Kd=0;
float dt=0.025;
int cal_flag=0;
int a7,a2,a3,a4,a5,a6=0;
int curr_signal=0;
int base_signal=0;
int s_min[6]={1023,1023,1023,1023,1023,1023};//black
int s_max[6]={0,0,0,0,0,0};//white
int PWM_motor;
int PWM_cal;
int s1_mapd,s2_mapd,s3_mapd,s4_mapd,s5_mapd,s6_mapd;
//pin names-first 4 need pwm pins
int AIN1=3,AIN2=5,BIN1=6,BIN2=9;

int count_cal=0;//count for number of times the to and fro motor routine has run

//custom functions block
void motor_forward(int PWM_motor){
  analogWrite(AIN1,PWM_motor);
  analogWrite(AIN2,0);
  analogWrite(BIN1,PWM_motor);
  analogWrite(BIN2,0);
}

void motor_backward(int PWM_motor){
  analogWrite(AIN1,0);
  analogWrite(AIN2,PWM_motor);
  analogWrite(BIN1,0);
  analogWrite(BIN2,PWM_motor);
}

void motor_stop(int PWM_motor){
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,HIGH);
}

// void motor_turnR(){

// }

void normalize_array(int arr[6]){
    int s1_tight= constrain(arr[0],s_min[0],s_max[0]);
    int s2_tight= constrain(arr[1],s_min[1],s_max[1]);
    int s3_tight= constrain(arr[2],s_min[2],s_max[2]);
    int s4_tight= constrain(arr[3],s_min[3],s_max[3]);
    int s5_tight= constrain(arr[4],s_min[4],s_max[4]);
    int s6_tight= constrain(arr[5],s_min[5],s_max[5]);

    s1_mapd=map(s1_tight,s_min[0],s_max[0],0,1000);
    s2_mapd=map(s2_tight,s_min[1],s_max[1],0,1000);
    s3_mapd=map(s3_tight,s_min[2],s_max[2],0,1000);
    s4_mapd=map(s4_tight,s_min[3],s_max[3],0,1000);
    s5_mapd=map(s5_tight,s_min[4],s_max[4],0,1000);
    s6_mapd=map(s6_tight,s_min[5],s_max[5],0,1000);

    mapd_val[0]=s1_mapd;
    mapd_val[1]=s2_mapd;
    mapd_val[2]=s3_mapd;
    mapd_val[3]=s4_mapd;
    mapd_val[4]=s5_mapd;
    mapd_val[5]=s6_mapd;

}

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  //pin initialization code block
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);

  //sensor calibration routine block
  while(cal_flag==0){
    unsigned long curr_time0=millis();
    unsigned long curr_time1=millis();
    //sensor check: 50Hz
    if(curr_time0-old_time0>=20){
      for(int i=0;i<6;i++){
        int val=analogRead(array_pin[i]);
        if(val<s_min[i]){
          s_min[i]=val;
        }
        if(val>s_max[i]){
          s_max[i]=val;
        }
      }
      old_time0=curr_time0;
    }
    //motor runner code-#DEFINE PWM_cal AFTER TESTING FOR SPEED AND DISTANCE. 
    if(count_cal<=6){
      if(curr_time1-old_time1<=1000){
        motor_forward(PWM_cal);
      }
      else if(curr_time1-old_time1<=3000){
        motor_backward(PWM_cal);
      }
      else if(curr_time1-old_time1<=4000){
        motor_forward(PWM_cal);
      }
      else{
        old_time1=curr_time1;
        count_cal++;
      }
    }
    else{
      cal_flag=1;
    }

  }
}

void loop(){
  unsigned long curr_time2=millis();
  unsigned long curr_time3=millis();


  //PID loop:40 Hz loop
  if(curr_time2-old_time2>=25){
      //updating values of ir_val
    for(int i=0;i<6;i++){
      ir_val[i]=analogRead(array_pin[i]);
    }
    normalize_array();

    //pid code
    old_time2=curr_time2;
  }
}

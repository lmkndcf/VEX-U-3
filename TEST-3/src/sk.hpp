#include "vex.h"
using namespace vex;
vex::brain       Brain;
vex::controller contro1;
vex::motor      motorr1(16);    //底盘右边电机
vex::motor      motorl2(18);   //底盘左边电机
vex::motor      motorr3(17);   //底盘右边电机
vex::motor      motorl4(19);   //底盘左边电机
vex::motor      motor5(0);    //吸取/吐出粽子左边电机
vex::motor      motor7(1);    //投掷粽子的电机
vex::motor      motor6(9);    //吸取/吐出粽子右边电机
vex::motor      motor11(10);   //车上吊的电机
vex::motor      motor12(11);   //车上吊的电机
void char_present(void);
void all_motor_stop(void);
float k;
float k2;
float k3,k4;      //前后左右的转轴值
float k5=0.5;     //实现速度的调档
float chazhi=0;   //实现转弯更加丝滑，边走边转弯
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       z                                                         */
/*    Created:      2023/10/16 20:17:21                                       */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "sk.hpp"
using namespace vex;

//  左手转轴：前后左右，转动越大，速度越快；按X键可以实现对最大速度的调档，共有5档
//  A键控制所有电机的启停
//  B键控制最后时刻车的机械臂向下压90度，以此实现将车吊起来；
//  R1键切换吸取/吐出粽子的状态
//  R2键控制是否吸取/吐出粽子



int main() 
{

    bool sd=0;    //控制所有电机是否运转。按A键运转
    bool sk=0;    //控制吸入粽子，或者吐出粽子。
    bool sn=0;    //控制吸入/吐出粽子相关电机的开启与停止
                  //底盘部分的控制通过遥控器的左手转轴实现
    bool sf=0;    //投掷粽子的标志位

       motor11.setPosition(0,deg);
       motor12.setPosition(0,deg);

    while(1)
     {
       if(contro1.ButtonA.pressing())   //按下A键所有电机启动，再按一次所有电机停止
           sd=sd==1?0:1;
           this_thread::sleep_for(10);
        if(sd)
        {
           contro1.Screen.clearScreen();
//---------------------------------------------------------------
        if(contro1.ButtonB.pressing())
        {
           motor11.spin(vex::directionType::rev,50,rpm);
           motor12.spin(fwd,50,rpm);
        }
        if(abs(motor11.position(deg))>1200)
        motor11.stop(hold);
        
        if(abs(motor12.position(deg))>1200)
        motor12.stop(hold);
//----------------------------让车吊起来
           if(contro1.ButtonY.pressing())   
            sf=sf==0?1:0;

           if(sf)
           motor7.spin(vex::directionType::rev,50,rpm);
           else
           motor7.stop();

           if(contro1.ButtonR1.pressing())
            sk=sk==0?1:0;
            this_thread::sleep_for(10);
            if(contro1.ButtonR2.pressing())
            sn=sn==0?1:0;
              this_thread::sleep_for(10);
           if(sk==1)                                    //吸取粽子
           {
            motor5.spin(fwd,100,rpm);
            motor6.spin(vex::directionType::rev,60,pct);
           }
           else                                     //吐出粽子
           {
             motor6.spin(fwd,80,rpm);
             motor5.spin(vex::directionType::rev,60,pct);
           }

           if(sn==0)                                  //停止吸取/吐出粽子
           {
            motor5.stop();
            motor6.stop();
           }
    
           chazhi=0;
           char_present();    //检测转轴的数值
           if(k3>0&&k4==0)//向前
           {
            if(chazhi>=0)
            {
                
           motorl2.spin(fwd,k+chazhi,pct);//左边电机
           motorl4.spin(fwd,k+chazhi,pct);
           motorr1.spin(vex::directionType::rev,k-0.4*chazhi,pct);//右边电机
           motorr3.spin(vex::directionType::rev,k-0.4*chazhi,pct);
            }
            else
            {
           motorl2.spin(fwd,k+0.5*chazhi,pct);//左边电机
           motorl4.spin(fwd,k+0.5*chazhi,pct);
           motorr1.spin(vex::directionType::rev,k-chazhi,pct);//右边电机
           motorr3.spin(vex::directionType::rev,k-chazhi,pct);
            }
           }
           else if(k3<0&&k4==0)//向后
           {
            if(chazhi>0)
            {
           motorl2.spin(vex::directionType::rev,k+chazhi,pct);
           motorl4.spin(vex::directionType::rev,k+chazhi,pct);
           motorr1.spin(fwd,k-0.5*chazhi,pct);
           motorr3.spin(fwd,k-0.5*chazhi,pct);
            }
            else
            {
           motorl2.spin(vex::directionType::rev,k+0.5*chazhi,pct);
           motorl4.spin(vex::directionType::rev,k+0.5*chazhi,pct);
           motorr1.spin(fwd,k-chazhi,pct);
           motorr3.spin(fwd,k-chazhi,pct);
            }
           }
           else if (k3==0&&k4<0)//向左
           {
            motorl2.spin(fwd,k,pct);
            motorl4.spin(fwd,k,pct);
            motorr1.spin(fwd,k,pct);
            motorr3.spin(fwd,k,pct);
           contro1.Screen.setCursor(3,1);
           
           }
           else if (k3==0&&k4>0)//向右
           {
            
             motorl2.spin(vex::directionType::rev,k,pct);
             motorl4.spin(vex::directionType::rev,k,pct);
             motorr1.spin(vex::directionType::rev,k,pct);
             motorr3.spin(vex::directionType::rev,k,pct);
           }
           else 
           {
            motorr1.stop();
            motorl2.stop();
            motorr3.stop();
            motorl4.stop();
           }
           
           contro1.Screen.setCursor(1,1);
           contro1.Screen.print("电机运作");    
           k=0;k2=0;k3=0;k4=0;
        }
        else    //第二次按下A键所有电机停止
        {
            contro1.Screen.clearScreen();
            all_motor_stop();    
            contro1.Screen.setCursor(2,1);
            contro1.Screen.print("电机停止");
            sd=0;
        }
    }
}



void char_present(void)
{
   int temp;
   k3=0;
   k4=0;
  k3=contro1.Axis3.position(pct);
  k4=contro1.Axis4.position(pct);

  k=k3*k3+k4*k4;
  k=sqrt(k);
  
  if(contro1.ButtonX.pressing())
  {
    k5+=0.1;
    if(k5>1)
    k5=0.5;
  }
  this_thread::sleep_for(10);
  k=k*k5;
  if(k>=100)
  k=100;
  
  if(8*abs(k3)<abs(k4))
  {
     k3=0;
  }
      else
  {
    if(k4>0)
    {   
    chazhi=abs(k4);
    temp=k+chazhi;
    if(temp>1)
    chazhi=1-k;
    if(k4<30)
    chazhi=0;
    }
    else
    {
    chazhi=-abs(k4);
    temp=k-chazhi;
    if(temp>1)
    chazhi=k-1;
   if(k4>-30)
     chazhi=0;
    }
    chazhi=k5*chazhi;
     k4=0;
  }

}


void all_motor_stop(void)
{
            motorr1.stop();
            motorl2.stop();
            motorr3.stop();
            motorl4.stop();
            motor5.stop();
            motor6.stop();
            motor7.stop();
            motor11.stop();
            motor12.stop();
}
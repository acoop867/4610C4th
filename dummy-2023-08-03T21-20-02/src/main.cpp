/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Thu Jul 13 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// l1                   motor         5               
// l2                   motor         20              
// l3                   motor         17              
// r1                   motor         3               
// r2                   motor         12              
// r3                   motor         14              
// Inertial4            inertial      18              
// lr                   rotation      11              
// rr                   rotation      21              
// Controller1          controller                    
// Intake               motor         4               
// cata                 motor         8               
// LimitSwitchA         limit         A               
// Arm                  motor         19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


int i = 0;
int prev=0;
void reset() {
  i=0;
  prev=0;
}


int li(){
  return (l1.position(degrees)+l2.position(degrees)+l3.position(degrees))/3;
}
int ri(){
  return (r1.position(degrees)+r2.position(degrees)+r3.position(degrees))/3;
}


void sl(int speed) {
  l1.spin(forward,speed,pct);
  l2.spin(forward,speed,pct);
  l3.spin(forward,speed,pct);
}
void sr(int speed) {
  r1.spin(forward,speed,pct);
  r2.spin(forward,speed,pct);
  r3.spin(forward,speed,pct);
}
void sl1(int speed) {
  l2.spin(forward,speed,pct);
  l3.spin(forward,speed,pct);
}
void sr1(int speed) {
  r1.spin(forward,speed,pct);
  r2.spin(forward,speed,pct);
}

void wings(int i) {
  if(i==1) {
    wingL.set(true);
    wingR.set(false);
  }
  else if (i==2) {
  wingR.set(true);
  wingL.set(false);
  }
  else if(i==3){
    wingL.set(true);
    wingR.set(true);
  }
  else if(i==0){
    wingL.set(false);
    wingR.set(false);
  }

}

void pid(int ang) {
  float p = ang-inert.rotation();
  float i = 0;
  float d = ang;
  float kp;
  
  kp = .35;
  
  float ki=0;//.000000000000001;
  float kd=.12;
  while(fabs(d)>.3||fabs(p)>.6) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;
    if(fabs(p)<10){
    i+=p;
    }
    l1.spin(forward,p*kp+d*kd+i*ki,pct);
    l2.spin(forward,p*kp+d*kd+i*ki,pct);
    l3.spin(forward,p*kp+d*kd+i*ki,pct);
    r1.spin(reverse,p*kp+d*kd+i*ki,pct);
    r2.spin(reverse,p*kp+d*kd+i*ki,pct);
    r3.spin(reverse,p*kp+d*kd+i*ki,pct);

    //sl(p*kp+d*kd);
    //sr(-p*kp+-d*kd);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(p);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void pid(int ang,int timeout) {
  float p = ang-inert.rotation();
  float i = 0.000001;
  float d = ang;
  float kp=.35;
  
  float kd=.12;
  int t=0;
  while((fabs(d)>.3||fabs(p)>.3)&&t<timeout) {
    t+=10;
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;

    l1.spin(forward,p*kp+d*kd,pct);
    l2.spin(forward,p*kp+d*kd,pct);
    l3.spin(forward,p*kp+d*kd,pct);
    r1.spin(reverse,p*kp+d*kd,pct);
    r2.spin(reverse,p*kp+d*kd,pct);
    r3.spin(reverse,p*kp+d*kd,pct);

    //sl(p*kp+d*kd);
    //sr(-p*kp+-d*kd);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void intout() {
  Intake.spin(reverse,100,pct);
  wait(1,sec);
  Intake.stop();
}

void pidswingr(int ang) {
  float p = ang;
  float i = 0;
  float d = ang;

  float kp = .6;
  float kd=0.05;
  while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;

    //sl(p*kp+d*kd);
    r1.spin(reverse,p*kp+d*kd,pct);
    r2.spin(reverse,p*kp+d*kd,pct);
    r3.spin(forward,p*kp+d*kd,pct);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
  }
  
  sl(0);
  sr(0);
}

void pidswingl(int ang) {
  float p = ang;
  float i = 0;
  float d = ang;

  float kp = .7;
  float kd=0.05;
  float t=0;
  while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5&&t<800) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;

    l1.spin(forward,p*kp+d*kd,pct);
    l2.spin(forward,p*kp+d*kd,pct);
    l3.spin(forward,p*kp+d*kd,pct);
    sr(-p*.05);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
    t+=10;
  }
  
  sl(0);
  sr(0);
}

void pidswingl2(int ang) {
  float p = ang;
  float i = 0;
  float d = ang;

  float kp = .6;
  float kd=0.05;
  float t=0;
  while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5&&t<500) {
    float prev = p;
    p=ang-inert.rotation();
    d=p-prev;
    float inp=p*kp+d*kd;
    if(inp>50) {
      inp=50;
    }
    l1.spin(reverse,inp,pct);
    l2.spin(forward,inp,pct);
    l3.spin(forward,inp,pct);
    //sr(-p*kp+-d*kd);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(inert.rotation());
    wait(10,msec);
    t+=10;
  }
  pid(ang);
  sl(0);
  sr(0);
}

void pidd(int dist, int ang) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
double kp=.08;


double kd = 0.11;
//dist=dist*4*3.25*3.14159/(5*360);
float p = dist;
float d=dist;

double kap = .03;

while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5) {
    float prev = p;
    p=dist-(li()+ri())/2;
    d=p-prev;

    float ap = ang-inert.rotation();

    sl(p*kp+d*kd+ap*kap);
    sr(p*kp+d*kd-ap*kap);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(kp);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void pidd(int dist, int ang,int timeout) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
double kp=.08;


double kd = 0.11;
//dist=dist*4*3.25*3.14159/(5*360);
float p = dist;
float d=dist;

double kap = .03;
double t =0;
while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5&&t<timeout) {
    float prev = p;
    p=dist-(li()+ri())/2;
    d=p-prev;
    t+=10;
    float ap = ang-inert.rotation();
    int pow = p*kp+d*kd;
    
    sl(pow+ap*kap);
    sr(pow-ap*kap);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(kp);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

void arc(int dist, int ang) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
double kp=.09;


double kd = 0.05;
//dist=dist*4*3.25*3.14159/(5*360);
float p = dist;
float d=dist;

double kap = 2;

while((fabs(d)>.3||fabs(p)>40)&&fabs(p)>.5) {
    float prev = p;
    p=dist-(li()+ri())/2;
    d=p-prev;

    float ap = ang-inert.rotation();

    sl(p*kp+d*kd+ap*kap);
    sr(p*kp+d*kd-ap*kap);
    //Controller1.Screen.clearScreen();
    //Controller1.Screen.setCursor(1,1);
    //Controller1.Screen.print(kp);
    wait(10,msec);
  }
  sl(0);
  sr(0);
}

int catathing(){
  while(true) {
    if(Controller1.ButtonL2.pressing()&&(!Controller1.ButtonR2.pressing()&&!Controller1.ButtonL1.pressing()&&!Controller1.ButtonR1.pressing())) {
      cata.spin(forward,12,volt);
      cata2.spin(forward,12,volt);
    }
    else {
    cata.stop();
    cata2.stop();
    }
    /*if(cata.torque()>.1) {
      cata.setPosition(0, deg);
      cata.spin(forward,100,pct);
      while(cata.position(deg)<400) {
        wait(10,msec);
      }
      if(di.objectDistance(inches)>2) {
      cata.stop();
      waitUntil(di.objectDistance(inches)<2);
      }
      cata.spin(forward,100,pct);
    }
    else{
      cata.spin(forward,100,pct);
    }
    */
  }
  return 0;
}

void cataauto() {
  int times=0;
  int tim=0;
  cata.spin(forward,12,volt);
  cata2.spin(forward,12,volt);
  while(times<44&&tim<30000){
  if(di.hue()>=50) {
      times++;
      while(di.hue()>=50){
      wait(10,msec);
      tim+=10;
      }
  }
  wait(10,msec);
  tim+=10;
  }
  cata.stop();
  cata2.stop();
}

int select=1;
void driver_auto(){
  pidd(-600,0);
  pid(-61,1400);
  pidd(-50,-61,400);
  pid(-61,400);
  bwing.set(true);
  cata.spin(forward,100,pct);
  wait(5,seconds);
}

int timething=0;
int timerend(){
  while(timething<800) {
    timething+=10;
    wait(10,msec);
  }
  return 0;
}


void driver() {
  thread th(catathing);
  bool n = false;
  bool t= false;
  bool m = false;
  bool z = false;
  bool l = false;
  bool r = false;
  bool rr = false;
  bool lr = false;
  bool inta = false;
  bool inta2 = false;
  bool tank = false;
  bool test=false;
  
  int toggle= 0;
  bool end=false;
  bool lifttog=false;
  bool side=false;
  bool enddone=false;
  if(select==5){
    driver_auto();
  }
  while(true) {
    if(Controller1.ButtonX.pressing()&&!lifttog) {
      lifttog=true;
      lift.set(!lift.value());
      bwing.set(true);
    }
    
    if(Controller1.ButtonB.pressing()&&!lifttog) {
      
      lift.set(!lift.value());
      lifttog=true;
      toggle=0;
    }

    if(!Controller1.ButtonX.pressing()&&!Controller1.ButtonB.pressing()){
      lifttog=false;
    }
    
    
    if(!tank){
    l1.spin(forward,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    l2.spin(forward,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    l3.spin(forward,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    r1.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    r2.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    r3.spin(forward,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    }
    else{
      l1.spin(forward,Controller1.Axis3.position(),pct);
      l2.spin(forward,Controller1.Axis3.position(),pct);
      l3.spin(forward,Controller1.Axis3.position(),pct);
      r1.spin(forward,Controller1.Axis2.position(),pct);
      r2.spin(forward,Controller1.Axis2.position(),pct);
      r3.spin(forward,Controller1.Axis2.position(),pct);
    }
    
    if(Controller1.ButtonL1.pressing()&&Controller1.ButtonL2.pressing()&&Controller1.ButtonR1.pressing()&&Controller1.ButtonR2.pressing()&&!end){
      
      wingL.set(false);
      wingR.set(false);
      enddone=true;
      end=true;
      
      
        lift.set(true);
        toggle=1;
      
      
    }
    if(!(Controller1.ButtonL1.pressing()&&Controller1.ButtonL2.pressing()&&Controller1.ButtonR1.pressing()&&Controller1.ButtonR2.pressing())){
      end=false;
    }
    if(Controller1.ButtonL1.pressing()&&Controller1.ButtonL2.pressing()&&toggle==1&&!end){
    if(lift.value()){
        lift.set(false);
         
        endgame.set(true);
        
          bwingl.set(true);
        }
        
        
      }

    if(Controller1.ButtonR1.pressing()&&Controller1.ButtonR2.pressing()&&toggle==1&&!end){
    if(lift.value()){
        lift.set(false);
         
        endgame.set(true);
        
          bwing.set(true);
        }
        
        
      }
    

    
    
    if(Controller1.ButtonRight.pressing()&&Controller1.ButtonLeft.pressing()&&Controller1.ButtonDown.pressing()&&Controller1.ButtonUp.pressing()&&Controller1.ButtonA.pressing()&&Controller1.ButtonB.pressing()&&Controller1.ButtonX.pressing()&&Controller1.ButtonY.pressing()){
      tank = true;
    }
    
      
    if(Controller1.ButtonA.pressing()&&Controller1.ButtonB.pressing()&&Controller1.ButtonX.pressing()&&Controller1.ButtonY.pressing()){
      test=true;
    }
      
    
    
    if(Controller1.ButtonL1.pressing()&&Controller1.ButtonR1.pressing()&&inta==false&&!(Controller1.ButtonL2.pressing()&&Controller1.ButtonR2.pressing())) {
        bwing.set(!bwing.value());
        
        inta=true;
      }
      else if(!Controller1.ButtonL1.pressing()&&!Controller1.ButtonR1.pressing()){
        inta=false;
      }
    
    
    else{
      inta2=false;
    }
    
    if(!toggle){
    if(Controller1.ButtonL1.pressing()&&!Controller1.ButtonR1.pressing()) {
      Intake.spin(forward,100,pct);
    }
    else if(Controller1.ButtonR1.pressing()&&!Controller1.ButtonL1.pressing()) {
      Intake.spin(reverse,100,pct);
    }
    else{
      Intake.stop(hold);
    }
    }
    

    

    

    if(Controller1.ButtonR2.pressing()&&!Controller1.ButtonR1.pressing()&&!Controller1.ButtonL1.pressing()&&!toggle) {
      
      if(t&&m==false) {
        t=false;
      }
      else if(!t&&m==false) {
        t=true;
      }
      if(m==false&&(wingL.value()||wingR.value())){
        t=false;
      }
      wingL.set(t);
      wingR.set(t);
      m=true;
      
    }
    if(!Controller1.ButtonR2.pressing()) {
      m=false;
    }

     if(Controller1.ButtonY.pressing()) {
      
      
      if(lr==false){
        wingL.set(!wingL.value());
      }
      
      
      lr=true;
    }
    if(!Controller1.ButtonY.pressing()) {
      lr=false;
    }
    if(Controller1.ButtonA.pressing()) {
      
      

      if(rr==false){
      wingR.set(!wingR.value());
      }
      
      rr=true;
    }
    if(!Controller1.ButtonA.pressing()) {
      rr=false;
    }
    
  }
}

void intin(){
  Intake.spin(forward,100,pct);
}
void inout() {
  Intake.spin(reverse,100,pct);
}
int distin() {
  while(li()<200){
    wait(10,msec);
  }
  intout();
  return 0;
}
void intstop() {
  Intake.stop(hold);
}
competition Comp;

int psel;
void pre() {
  inert.calibrate();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Defense awp");

  while(true){//!Comp.isAutonomous()) {

  if(Controller1.ButtonUp.pressing()){
    select++;
    while(Controller1.ButtonUp.pressing()){
      wait(.1,sec);
      Brain.Screen.clearScreen();
    }
  
  
  
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  
  if(select == 1) {
    Brain.Screen.print("Defense awp");
  }
  if(select == 2) {
    Brain.Screen.print("Defense Elims");
  }
  if(select == 3) {
    Brain.Screen.print("Offense");
  }
  if(select==4) {
    Brain.Screen.print("skills");
  }
  if(select==5) {
    Brain.Screen.print("skills driver");
  
  }
  
}}
}
void db(int degs){
  double ang= inert.rotation();
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r2.resetPosition();
  r3.resetPosition();
  
  while(li()+ri()>-degs*2) {
    float ap = ang-inert.rotation();
    sl(-70+ap*.05);
    sr(-70-ap*.05);
    wait(20,msec);
  }
  sl(0);
  sr(0);
}


void drive(int lspeed,int rspeed) {

}


int wingin() {
  wait(.4,sec);
  wingL.set(false);
  wingR.set(false);
  return 0;
}


void autodefensewp(){
  wingL.set(true);
  
  bwingl.set(true);
  wait(.3,sec);
  wingL.set(false);
  wait(.5,sec);
  pid(-80,800);
  bwingl.set(false);
  pidd(-1000,-80);
  pid(-90,400);
  pidd(-900,-80);
  pidd(100,-90);
}

void autooffenseawp(){
  intin();
  pidd(200,0);
  pidd(-1700,0);
  pid(-35,500);
  pidd(-700,-45);
  bwingl.set(true);
  pid(-90,600);
  bwingl.set(false);
  pid(-70,500);
  pidd(-400,500);
  pid(-90,500);
  pidd(-1000,-90);

}

void autooffenseelim(){
  intin();
  wingR.set(true);
  thread t(wingin);
  pidd(3000,0,4000);
  pid(120,600);
  inout();
  wingR.set(true);
  pidd(1600,120,900);
  wingR.set(false);

  pidd(-400,120,700);
  pid(265,700);
  intin();
  pidd(1500,270,1000);
  pid(160,500);
  pidd(1400,160,900);
  pid(120,400);
  inout();
  wait(.4,sec);
  pid(165,700);
  pidd(700,175,900);
  

  pidswingl(260);
  
  bwingl.set(true);
  pidd(-500,260);
  pid(240,500);
  bwingl.set(false);
  pid(260,400);
  pidd(-400,260);
  pid(240,400);
  
  inout();
  
  pidd(-10000,210,800);
  pidd(500,210);
}

void skills(){
  
  pidd(-600,-45);
  pid(-60,500);
  wait(2,sec);
  pid(40,400);
  pidd(-1000,45,700);
  pidd(400,45);
  pid(-45,500);
  pidd(1500,-45);
  pid(-135,500);
  intin();
  pidd(2300,-135);
  pid(-45,500);
  wings(3);
  pidd(2000,-45);
  pidd(2000,-45,1000);
  wingL.set(false);
  wingR.set(false);
  pid(-45,300);
  pidd(-1000,-45);
  pid(-135);
  pidd(-1100,-135);
  pid(-45);
  wings(3);
  pidd(1000,-45);
}

void disrupt(){
  intin();
  pidd(2300,0);
  pidd(-200,0);
  pid(80,600);
  wingR.set(true);
  inout();
  pidd(1000,80);
  wingR.set(false);
  pidd(-200,80);
  pid(30,500);
  pidd(-2800,30);
  pid(80,600);
  pidd(1600,80);
  pid(110);
  pidd(-2000,110);
  pid(56);
  bwing.set(true);
  // pid(50);
  // bwing.set(true);
}

int brainread(){
  while (true){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(inert.rotation());
    wait(.1,sec);
  }
  return 0;
}

void skills2(){
  //thread t(brainread);
  bwingl.set(true);
  pidd(-600,45);
  // pid(40,600);
  // pidd(-300,40);
  // pidd(300,45);
  bwingl.set(false);
  pid(-61,1500);
  pid(-61,200);
  
  bwing.set(true);
  cataauto();
  
  cata.stop();
  bwing.set(false);
  pidd(200,-60);
  pid(30,700);
  pidd(-1000,45,700);
  pidd(100,45);
  pid(0,700);
  pidd(1800,0);
  pid(-45,700);
  pidd(3600,-45);
  pid(-90,500);
  pidd(500,-90);
  pidd(-500,-90);
  pid(90,500);
  pidd(-800,90);
  pid(52,500);
  
  pidd(-1000,45,800);
  pid(45,200);
  pidd(500,45);
  pidd(-500,45);
  pidd(300,45);
  pid(135,700);
  pidd(2000,135);
  pid(225,700);
  pidd(700,225);
  pid(300,600);
  wingL.set(true);
  wingR.set(true);
  
  pidd(1200,270,1000);
  wingL.set(false);
  wingR.set(false);
  pid(315,500);
  pidd(-1000,315);
  pid(225,500);
  pidd(1000,225);
  pid(315,700);
  wingL.set(true);
  wingR.set(true);
  pidd(1600,315,1000);
  
  wingL.set(false);
  wingR.set(false);
  pid(340,500);
  pidd(-900,300);
  pid(315,300);
  wingL.set(true);
  wingR.set(true);
  pidd(1600,315,1000);
}



void autonomousprogram() {

  if(select==3){
    autodefensewp();
  }
  if(select==2){
    disrupt();
  }
  if(select==1){
    autooffenseelim();
    //pidswingl(-45);
    //pidd(500,-45);
  }
  if(select==4||select==5){
    skills2();
  }
}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
   Comp.autonomous(autonomousprogram);
   Comp.drivercontrol(driver);

  pre();
  
  
  
  

  while(1){
    wait(100,msec);
    
  }

}